#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: simple.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import pytest
import os
import rapidxml

@pytest.fixture()
def init_rapidxml():
    r = rapidxml.RapidXml(bytearray(b"""
<root>
  <test attr1="one" attr2="two" attr3="three" />
  <test2>
    <node id="1"/>
    <node id="2"/>
    <node id="3"/>
  </test2>
  <test>some text</test>
</root>"""))
    return r

def test_init(init_rapidxml):
    assert init_rapidxml.unparse() == ('<root><test attr1="one" attr2="two" attr3="three"/>'
                                       '<test2><node id="1"/><node id="2"/><node id="3"/></test2>'
                                       '<test>some text</test></root>')

def test_parse(init_rapidxml):
    r = rapidxml.RapidXml()
    try:
        data = init_rapidxml.unparse().encode('utf-8')
    except UnicodeDecodeError:
        data = init_rapidxml.unparse()
    r.parse(bytearray(data))
    assert str(r) == str(init_rapidxml)

def test_parse_from_file(init_rapidxml, tmpdir):
    f = tmpdir.join("dump.xml")
    f.write(init_rapidxml.unparse())
    r = rapidxml.RapidXml(str(f), from_file=True)
    assert str(r) == str(init_rapidxml)

def test_first_node(init_rapidxml):
    root = init_rapidxml.first_node()
    assert root.name == "root"
    assert root.value == ""
    assert root.unparse() == init_rapidxml.unparse()

def test_nested_node(init_rapidxml):
    test = init_rapidxml.first_node().first_node("test")
    assert test.name == "test"
    assert test.value == ""
    test2 = init_rapidxml.first_node().first_node("test2")
    assert test2.name == "test2"
    assert test2.value == ""

def test_children(init_rapidxml):
    test2 = init_rapidxml.first_node().first_node("test2")
    for node in test2.children:
        assert node.name == "node"
        assert node.value == ""
