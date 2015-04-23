#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: simple.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import os
import rapidxml

def test_init(init_rapidxml):
    assert init_rapidxml.unparse() == ('<root><test attr1="one" attr2="two" attr3="three"/>'
                                       '<test2><node id="1"/><node id="2"/><node id="3"/></test2>'
                                       '<test>some text</test></root>')
    assert init_rapidxml.unparse() == repr(init_rapidxml)
    assert init_rapidxml.unparse(True) == str(init_rapidxml)

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

def test_equals(init_rapidxml):
    assert init_rapidxml == init_rapidxml
    root = init_rapidxml.first_node()
    assert root == root
    assert root == init_rapidxml.first_node()
    assert root.first_node() != root.first_node("test2")
    assert (root != root) == (not (root == root))

def test_parent(init_rapidxml):
    assert init_rapidxml.parent is None
    assert init_rapidxml.first_node().parent == init_rapidxml

def test_assign(init_rapidxml):
    root = init_rapidxml.first_node()
    root.name = "new_root"
    assert root.name == "new_root"
    test = root.first_node()
    test.name = "new_test"
    test.first_attribute().name = "new_attr1"
    test.first_attribute().next_attribute().value = "new_two"
    test = root.first_node("test")
    test.value = "some new text"
    assert test.value == "some new text"
    assert init_rapidxml.unparse() == ('<new_root><new_test new_attr1="one" attr2="new_two" attr3="three"/>'
                                       '<test2><node id="1"/><node id="2"/><node id="3"/></test2>'
                                       '<test>some new text</test></new_root>')
