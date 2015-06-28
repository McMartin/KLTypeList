#!/usr/bin/env python

# Copyright (c) 2014 Alain Martin


import argparse
import ast
import collections
import os
import re
import subprocess
import sys
import tempfile


FEATURE_EXT = '.feature'


def parse_args():
    def existing_dir_or_file(path):
        if not os.path.exists(path):
            message = 'No such file or directory {}'.format(
                os.path.abspath(path))
            raise argparse.ArgumentTypeError(message)
        return path

    def existing_file(path):
        if not os.path.isfile(path):
            message = 'No such file {}'.format(os.path.abspath(path))
            raise argparse.ArgumentTypeError(message)
        return path

    arg_parser = argparse.ArgumentParser()

    arg_parser.add_argument('-c', '--compiler',
                            required=True,
                            type=existing_file,
                            dest='compiler_file_path')

    arg_parser.add_argument('input_path',
                            type=existing_dir_or_file,
                            nargs='?',
                            default=os.path.curdir)

    return arg_parser.parse_args(sys.argv[1:])


class Compiler(object):
    @staticmethod
    def from_file(compiler_file_path):
        with open(compiler_file_path, 'r') as compiler_file:
            settings = ast.literal_eval(compiler_file.read())

            return Compiler(
                settings['exe'], settings['options'], settings['env'])

    def __init__(self, exe, options, env):
        self.exe = exe
        self.options = options
        self.env = env

    def call_env(self):
        call_env = os.environ.copy()

        for key in self.env:
            if key not in call_env:
                call_env[key] = ''
            for path in self.env[key]:
                call_env[key] += os.pathsep + path

        return call_env

    def compile(self, source_file_path):
        compiler_cmd = [self.exe, source_file_path] + self.options
        call_env = self.call_env()

        return_code = 0
        output = ''
        try:
            output = subprocess.check_output(
                compiler_cmd, env=call_env, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as error:
            return_code = error.returncode
            output = error.output

        return return_code, output


class Status(object):
    ERROR = 'ERROR'
    FAILED = 'FAILED'
    PASSED = 'PASSED'


def get_return_type(result):
    if result is None:
        return 'DNC'
    if result in ('true', 'false'):
        return 'Boolean'
    if result.isdigit():
        return 'Integer'
    if result.startswith('TypeList<'):
        return 'TypeList'
    if len(result) == 1:
        return 'Type'


class Feature(object):
    def __init__(self, line, name, has_arguments, return_type):
        self.line = line
        self.name = name
        self.has_arguments = has_arguments is not None
        self.return_type = return_type

    @staticmethod
    def from_declaration(line):
        feature_declaration_regex = re.compile(r'^(.+?)(?:<(.*)>)? -> (.+)$')
        match = feature_declaration_regex.search(line)

        if match:
            name, has_arguments, return_type = match.groups()
            return Feature(line, name, has_arguments, return_type)

    def run_test(self, feature_test, compiler):
        if (self.name != feature_test.feature_name
            or self.has_arguments != (feature_test.arguments is not None)
            or (self.return_type != get_return_type(feature_test.result)
                and feature_test.result is not None)):
                    print '[ {:<6} ] {}'.format('ERROR', feature_test.line)
                    print 'does not match {}'.format(self.line)
                    return Status.ERROR

        return feature_test.run(self, compiler)


test_code_skeleton = '''
#include "KL/TypeList.hpp"

#include <type_traits>

using A = {A};
using B = {B};
using C = {C};

using namespace KL;

class Test{feature_name}
{{
    void test()
    {{
        {result_type} Result = TypeList<{pack}>::{feature_name}{arguments};
        static_assert({assertion}, "!");
    }}
}};
'''


def get_result_type(return_type):
    if return_type in ('Boolean', 'Integer'):
        return 'const auto'
    if return_type in ('Type', 'TypeList'):
        return 'using'


def get_assertion(return_type, result):
    if result is None:
        return 'true'
    if return_type in ('Boolean', 'Integer'):
        return '{} == Result'.format(result)
    if return_type in ('TypeList', 'Type'):
        return 'std::is_same<{}, Result>::value'.format(result)


class FeatureTest(object):
    def __init__(self, line, feature_name, pack, arguments, result):
        self.line = line
        self.feature_name = feature_name
        self.pack = pack
        self.arguments = arguments
        self.result = result

    @staticmethod
    def from_declaration(line):
        feature_test_declaration_regex = re.compile(
            r'^TypeList<(.*)>::(.+?)(?:<(.*)>)?'
            r' (?:NOT COMPILE|== (.+))$')
        match = feature_test_declaration_regex.search(line)

        if match:
            pack, feature_name, arguments, result = match.groups()
            return FeatureTest(line, feature_name, pack, arguments, result)

    def run(self, feature, compiler):
        arguments = ''
        if feature.has_arguments:
            arguments += '<' + self.arguments + '>'
        if feature.return_type in ('Boolean', 'Integer'):
            arguments += '::value'

        test_code = test_code_skeleton.format(
            feature_name=feature.name,
            result_type=get_result_type(feature.return_type),
            pack=self.pack,
            arguments=arguments,
            assertion=get_assertion(feature.return_type, self.result),
            A='void',
            B='bool',
            C='char',
        )

        temp_file_descriptor = None
        temp_file_path = None
        temp_file = None
        return_code = None

        try:
            temp_file_descriptor, temp_file_path = tempfile.mkstemp(
                suffix='.cpp')
            temp_file = os.fdopen(temp_file_descriptor, 'w')
            temp_file.write(test_code)
            temp_file.close()

            return_code, output = compiler.compile(temp_file_path)
        finally:
            if temp_file:
                temp_file.close()
            elif temp_file_descriptor:
                os.close(temp_file_descriptor)
            if temp_file_path:
                os.remove(temp_file_path)

            if return_code is not None:
                if (return_code == 0) == (self.result is not None):
                    print '[ {:<6} ] {}'.format('PASS', self.line)
                    return Status.PASSED
                else:
                    print '[ {:<6} ] {}'.format('FAIL!', self.line)
                    print output
                    return Status.FAILED

        return Status.ERROR


def test_feature_file(feature_file_path, compiler):
    feature = None
    status_counts = collections.Counter()

    with open(feature_file_path, 'r') as feature_file:
        for line in feature_file:
            if not line.isspace():
                line = line.rstrip()

                if not feature:
                    feature = Feature.from_declaration(line)
                    if feature:
                        print '[--------] {}'.format(feature.line)
                    else:
                        print 'Failed to parse feature "{}" in {}'.format(
                            line, feature_file_path)
                        status_counts[Status.ERROR] = 1
                        return status_counts
                else:
                    test = FeatureTest.from_declaration(line)
                    if test:
                        status_counts[feature.run_test(test, compiler)] += 1
                    else:
                        print 'Failed to parse feature test "{}" in {}'.format(
                            line, feature_file_path)
                        status_counts[Status.ERROR] += 1

    print '[--------] {} passed, {} failed, {} errored'.format(
        status_counts[Status.PASSED],
        status_counts[Status.FAILED],
        status_counts[Status.ERROR])
    print ''

    return status_counts


def find_feature_files(path):
    if os.path.isfile(path) and os.path.splitext(path)[1] == FEATURE_EXT:
        yield path
        return

    for root, _, file_names in os.walk(path):
        for file_name in file_names:
            file_path = os.path.join(root, file_name)
            if os.path.splitext(file_path)[1] == FEATURE_EXT:
                yield file_path


def test_features(compiler_file_path, input_path):
    compiler = Compiler.from_file(compiler_file_path)

    feature_files = find_feature_files(input_path)

    status_counts = collections.Counter()

    for feature_file_path in feature_files:
        status_counts += test_feature_file(feature_file_path, compiler)

    print '[ TOTAL  ] {} error{}, {} failed test{}, {} passed test{}'.format(
        status_counts[Status.ERROR], 's'[status_counts[Status.ERROR] == 1:],
        status_counts[Status.FAILED], 's'[status_counts[Status.FAILED] == 1:],
        status_counts[Status.PASSED], 's'[status_counts[Status.PASSED] == 1:])

    return 1 if Status.ERROR in status_counts else status_counts[Status.FAILED]


if __name__ == '__main__':
    sys.exit(test_features(**vars(parse_args())))
