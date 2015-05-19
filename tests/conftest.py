#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: conftest.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import pytest
import rapidxml

@pytest.fixture(scope="function")
def init_rapidxml():
    r = rapidxml.RapidXml(b"""
<root>
  <test attr1="one" attr2="two" attr3="three" />
  <test2>
    <node id="1"/>
    <node id="2"/>
    <node id="3"/>
  </test2>
  <test>some text</test>
</root>""")
    return r
