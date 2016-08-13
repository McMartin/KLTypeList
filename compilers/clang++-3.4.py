# Copyright (c) 2014-2016 Alain Martin

{
    'exe': 'clang++',
    'options': [
        '-fsyntax-only',
        '-Iinclude',
        '-std=c++11',
        '-Werror',
        '-Weverything',
        '-Wno-c++98-compat',
    ],
    'env': {
    },
}
