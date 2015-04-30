#!/usr/bin/env python

# Copyright (c) 2014 Alain Martin


import argparse
import ast
import os
import re
import subprocess
import sys
import tempfile


REPO_ROOT = os.path.dirname(os.path.abspath(__file__))


def compiler_arg_choices():
    compilers_dir = os.path.join(REPO_ROOT, 'compilers')

    return [os.path.basename(file_name)
            for file_name in os.listdir(compilers_dir)]


def parse_args():
    arg_parser = argparse.ArgumentParser()

    arg_parser.add_argument('-c', '--compiler',
                            required=True,
                            choices=compiler_arg_choices())

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
    PASSED = 'PASSED'
    FAILED = 'FAILED'


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
                    print '[ %-6s ] %s\ndoes not match %s' % (
                        'ERROR', feature_test.line, self.line)
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
        return '%s == Result' % result
    if return_type in ('TypeList', 'Type'):
        return 'std::is_same<%s, Result>::value' % result


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
                    print '[ %-6s ] %s' % ('PASS', self.line)
                    return Status.PASSED
                else:
                    print '[ %-6s ] %s' % ('FAIL!', self.line)
                    print output
                    return Status.FAILED

        return Status.ERROR


def test_feature_file(feature_file_path, compiler):
    feature = None
    status = []

    with open(feature_file_path, 'r') as feature_file:
        for line in feature_file:
            if not line.isspace():
                line = line.rstrip()

                if not feature:
                    feature = Feature.from_declaration(line)
                    if feature:
                        print '[--------] %s' % feature.line
                    else:
                        print 'Failed to parse feature "%s" in %s' % (
                            line, feature_file_path)
                        return [Status.ERROR]
                else:
                    test = FeatureTest.from_declaration(line)
                    if test:
                        status.append(feature.run_test(test, compiler))
                    else:
                        print 'Failed to parse feature test "%s" in %s' % (
                            line, feature_file_path)
                        status.append(Status.ERROR)

    print ('[--------] %s passed' % status.count(Status.PASSED)
           + ', %s failed' % status.count(Status.FAILED)
           + ', %s errored\n' % status.count(Status.ERROR))

    return status


def test_features(compiler):
    compiler_file_path = os.path.join(REPO_ROOT, 'compilers', compiler)

    compiler = Compiler.from_file(compiler_file_path)

    features_dir = os.path.join(REPO_ROOT, 'features')

    feature_files = [os.path.join(features_dir, file_name)
                     for file_name in os.listdir(features_dir)
                     if file_name.endswith('.feature')]

    status = []
    for feature_file_path in feature_files:
        status += test_feature_file(feature_file_path, compiler)

    print '[ TOTAL  ] %s error%s, %s failed test%s, %s passed test%s' % (
        status.count(Status.ERROR), 's'[status.count(Status.ERROR) == 1:],
        status.count(Status.FAILED), 's'[status.count(Status.FAILED) == 1:],
        status.count(Status.PASSED), 's'[status.count(Status.PASSED) == 1:])

    return 1 if Status.ERROR in status else status.count(Status.FAILED)


if __name__ == '__main__':
    sys.exit(test_features(**vars(parse_args())))
