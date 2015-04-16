#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: setup.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

from setuptools import setup, Extension, find_packages

rapidxml = Extension("rapidxml._rapidxml",
                     define_macros=[('MAJOR_VERSION', '1'),
                                    ('MINOR_VERSION', '0')],
                     include_dirs=[
                         './rapidxml/c_ext/inc/',
                         './rapidxml/c_ext/inc/rapidxml-1.13/',
                     ],
                     sources=[
                         "./rapidxml/c_ext/src/common.cpp",
                         "./rapidxml/c_ext/src/rapidxml_module.cpp",
                         "./rapidxml/c_ext/src/base_object.cpp",
                         "./rapidxml/c_ext/src/node_object.cpp",
                         "./rapidxml/c_ext/src/attribute_object.cpp",
                         "./rapidxml/c_ext/src/document_object.cpp",
                         "./rapidxml/c_ext/src/nodeiterator_object.cpp",
                         "./rapidxml/c_ext/src/attributeiterator_object.cpp",
                     ],
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

    packages=['rapidxml'],
)
