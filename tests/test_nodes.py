#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: test_nodes.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import ast

def test_first_node(init_rapidxml):
    root = init_rapidxml.first_node()
    assert root.name == "root"
    assert root.value == ""
    assert root.unparse() == init_rapidxml.unparse()
    assert root.first_node() == root.first_node("test")
    assert root.first_node() != root.first_node("test2")

def test_last_node(init_rapidxml):
    root = init_rapidxml.first_node()
    assert root.first_node() != root.last_node()
    assert root.first_node("test2") == root.last_node("test2")
    assert root.last_node().value == "some text"

def test_nested_node(init_rapidxml):
    test = init_rapidxml.first_node().first_node("test")
    assert test.name == "test"
    assert test.value == ""
    test2 = init_rapidxml.first_node().first_node("test2")
    assert test2.name == "test2"
    assert test2.value == ""

def test_first_node_cdata(init_rapidxml_with_CDADA):
    root = init_rapidxml_with_CDADA.first_node()
    assert root.name == "root"
    assert root.value == ""
    assert root.unparse() == init_rapidxml_with_CDADA.unparse()
    assert root.first_node() == root.first_node("test")
    assert root.first_node() != root.first_node("test2")

def test_last_node_cdata(init_rapidxml_with_CDADA):
    root = init_rapidxml_with_CDADA.first_node()
    assert root.first_node() != root.last_node()
    assert root.first_node("test2") == root.last_node("test2")
    object = \
        {
            "Cart":
                {
                    "expirationTime":"2017-04-22T09:40",
                    "id":"b469df3b-f626-4fe3-898c-825373e546a2",
                    "products":["1223"],
                    "creationTime":"2017-04-21T09:40",
                    "totalPrice":
                        {
                            "currencyCode":"EUR",
                            "amount":"138.000"
                        }
                }
        }
    assert ast.literal_eval(root.last_node().first_node().first_node().value) == object

def test_nested_node_cdata(init_rapidxml_with_CDADA):
    test = init_rapidxml_with_CDADA.first_node().first_node("test")
    assert test.name == "test"
    assert test.value == ""
    test2 = init_rapidxml_with_CDADA.first_node().first_node("test2")
    assert test2.name == "test2"
    assert test2.value == ""
