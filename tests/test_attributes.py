#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: test_attributes.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

def test_first_attribute(init_rapidxml):
    test = init_rapidxml.first_node().first_node("test")
    assert test.first_attribute().name == "attr1"
    assert test.first_attribute().value == "one"
    attr2 = test.first_attribute("attr2")
    assert attr2.name == "attr2"
    assert attr2.value == "two"

def test_last_attribute(init_rapidxml):
    test = init_rapidxml.first_node().first_node("test")
    assert test.last_attribute().name == "attr3"
    assert test.last_attribute().value == "three"
    attr2 = test.last_attribute("attr2")
    assert attr2.name == "attr2"
    assert attr2.value == "two"

def test_append_attribute(init_rapidxml):
    root = init_rapidxml.first_node()
    root.append_attribute(init_rapidxml.allocate_attribute())
    assert root.last_attribute().name == ""
    assert root.last_attribute().value == ""
    root.append_attribute(init_rapidxml.allocate_attribute("test"))
    assert root.last_attribute().name == "test"
    assert root.last_attribute().value == ""
    root.append_attribute(init_rapidxml.allocate_attribute(value="test"))
    assert root.last_attribute().name == ""
    assert root.last_attribute().value == "test"
    root.append_attribute(init_rapidxml.allocate_attribute("test", "test"))
    assert root.last_attribute().name == "test"
    assert root.last_attribute().value == "test"

def test_prepend_attribute(init_rapidxml):
    root = init_rapidxml.first_node()
    root.prepend_attribute(init_rapidxml.allocate_attribute("test", "test"))
    assert root.first_attribute().name == "test"
    assert root.first_attribute().value == "test"
    root.prepend_attribute(init_rapidxml.allocate_attribute("test2", "test2"))
    assert root.first_attribute().name == "test2"
    assert root.first_attribute().value == "test2"

def test_insert_attribute(init_rapidxml):
    test = init_rapidxml.first_node().first_node()
    attr2 = test.first_attribute("attr2")
    test.insert_attribute(attr2, init_rapidxml.allocate_attribute("test", "test"))
    test = attr2.previous_attribute()
    assert test.name == "test"
    assert test.value == "test"

def test_first_attribute_cdata(init_rapidxml_with_CDADA):
    test = init_rapidxml_with_CDADA.first_node().first_node("test")
    assert test.first_attribute().name == "attr1"
    assert test.first_attribute().value == "one"
    attr2 = test.first_attribute("attr2")
    assert attr2.name == "attr2"
    assert attr2.value == "two"

def test_last_attribute_cdata(init_rapidxml_with_CDADA):
    test = init_rapidxml_with_CDADA.first_node().first_node("test")
    assert test.last_attribute().name == "attr3"
    assert test.last_attribute().value == "three"
    attr2 = test.last_attribute("attr2")
    assert attr2.name == "attr2"
    assert attr2.value == "two"

def test_append_attribute_cdata(init_rapidxml_with_CDADA):
    root = init_rapidxml_with_CDADA.first_node()
    root.append_attribute(init_rapidxml_with_CDADA.allocate_attribute())
    assert root.last_attribute().name == ""
    assert root.last_attribute().value == ""
    root.append_attribute(init_rapidxml_with_CDADA.allocate_attribute("test"))
    assert root.last_attribute().name == "test"
    assert root.last_attribute().value == ""
    root.append_attribute(init_rapidxml_with_CDADA.allocate_attribute(value="test"))
    assert root.last_attribute().name == ""
    assert root.last_attribute().value == "test"
    root.append_attribute(init_rapidxml_with_CDADA.allocate_attribute("test", "test"))
    assert root.last_attribute().name == "test"
    assert root.last_attribute().value == "test"

def test_prepend_attribute_cdata(init_rapidxml_with_CDADA):
    root = init_rapidxml_with_CDADA.first_node()
    root.prepend_attribute(init_rapidxml_with_CDADA.allocate_attribute("test", "test"))
    assert root.first_attribute().name == "test"
    assert root.first_attribute().value == "test"
    root.prepend_attribute(init_rapidxml_with_CDADA.allocate_attribute("test2", "test2"))
    assert root.first_attribute().name == "test2"
    assert root.first_attribute().value == "test2"

def test_insert_attribute_cdata(init_rapidxml_with_CDADA):
    test = init_rapidxml_with_CDADA.first_node().first_node()
    attr2 = test.first_attribute("attr2")
    test.insert_attribute(attr2, init_rapidxml_with_CDADA.allocate_attribute("test", "test"))
    test = attr2.previous_attribute()
    assert test.name == "test"
    assert test.value == "test"
