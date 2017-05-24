#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: setup.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import os
import io

from setuptools import setup, find_packages
from setuptools import Extension

long_descr = 'Python bindings for RapidXml, a C++ XML parsing library'
try:
    import pypandoc
    long_descr = pypandoc.convert('README.md', 'rst')
    long_descr = long_descr.replace("\r", "")
except (ImportError, OSError):
    if os.path.exists('README.md'):
        with io.open('README.md', encoding="utf-8") as f:
            long_descr = f.read()

VERSION = ("2", "1", "1")

rapidxml = Extension("rapidxml.c_ext",
                     define_macros=[('MAJOR_VERSION', VERSION[0]),
                                    ('MINOR_VERSION', VERSION[1])],
                     include_dirs=[
                         'rapidxml/c_ext/inc/',
                         'rapidxml/c_ext/inc/rapidxml-1.13/',
                     ],
                     sources=[
                         'rapidxml/c_ext/src/common.cpp',
                         'rapidxml/c_ext/src/rapidxml_module.cpp',
                         'rapidxml/c_ext/src/base_object.cpp',
                         'rapidxml/c_ext/src/node_object.cpp',
                         'rapidxml/c_ext/src/attribute_object.cpp',
                         'rapidxml/c_ext/src/document_object.cpp',
                         'rapidxml/c_ext/src/nodeiterator_object.cpp',
                         'rapidxml/c_ext/src/attributeiterator_object.cpp',
                     ],
)

setup(
    ext_modules=[rapidxml],
    name='RapidXml',
    version='.'.join(VERSION),
    license='MIT',

    url='https://github.com/Arzaroth/python_rapidxml',
    download_url='https://github.com/Arzaroth/python_rapidxml/tarball/%s' % ('.'.join(VERSION)),

    author='Marc-Etienne Barrut',
    author_email='lekva@arzaroth.com',

    description='Python RapidXml Library',
    long_description=long_descr,
    keywords='rapidxml xml parsing',

    packages=find_packages('.'),

    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Environment :: Console",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Operating System :: POSIX",
        "Operating System :: Microsoft :: Windows",
        "Operating System :: MacOS :: MacOS X",
        "Programming Language :: Python",
        "Programming Language :: Python :: 2",
        "Programming Language :: Python :: 2.6",
        "Programming Language :: Python :: 2.7",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.3",
        "Programming Language :: Python :: 3.4",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
    ],
)
