#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: test_iterations.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

def test_children(init_rapidxml):
    test2 = init_rapidxml.first_node().first_node("test2")
    i_node = test2.first_node()
    for node in test2.children:
        assert i_node == node
        assert node.name == "node"
        assert node.value == ""
        i_node = i_node.next_sibling()
        if i_node:
            assert i_node.previous_sibling() == node

def test_attributes(init_rapidxml):
    test = init_rapidxml.first_node().first_node()
    i_attr = test.first_attribute()
    for attr, expected_attr in zip(test.attributes, [('attr1', 'one'),
                                                     ('attr2', 'two'),
                                                     ('attr3', 'three')]):
        assert i_attr == attr
        assert (attr.name, attr.value) == expected_attr
        assert (i_attr.name, i_attr.value) == expected_attr
        i_attr = i_attr.next_attribute()
        if i_attr:
            assert i_attr.previous_attribute() == attr
