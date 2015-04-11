#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: setup.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

from setuptools import setup, Extension

rapidxml = Extension("rapidxml",
                     define_macros=[('MAJOR_VERSION', '1',
                                     'MINOR_VERSION', '0')],
                     include_dirs=['./rapidxml-1.13/'],
                     sources=["rapidxml.cpp"],
)

setup(
    ext_modules=[rapidxml],
    name='RapidXml',
    version='1.0',
    license='MIT',

    author='Marc-Etienne Barrut',
    author_email='lekva@arzaroth.com',

    description='python bindings for RapidXml, a C++ XML parsing library',
    keywords='rapidxml xml parsing',
)
