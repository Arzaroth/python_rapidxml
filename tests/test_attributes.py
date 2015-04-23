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
