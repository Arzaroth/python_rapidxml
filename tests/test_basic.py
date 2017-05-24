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
    r.parse(data)
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

def test_init_cdata(init_rapidxml_with_CDADA):
    datra_str =('<root><test attr1="one" attr2="two" attr3="three"/>'
                '<test2><node id="1"/><node id="2"/><node id="3"/></test2>'
                '<test>some text</test>'
                "<ns2:AdditionalData><ns2:Data TID=\"AD_1\">"
                "<![CDATA[{\"Cart\":{\"expirationTime\":\"2017-04-22T09:40\","
                "\"id\":\"b469df3b-f626-4fe3-898c-825373e546a2\",\"products\":[\"1223\"],"
                "\"creationTime\":\"2017-04-21T09:40\",\"totalPrice\":"
                "{\"currencyCode\":\"EUR\",\"amount\":\"138.000\"}}}]]>"
                "</ns2:Data></ns2:AdditionalData></root>")
    assert init_rapidxml_with_CDADA.unparse() == rapidxml.RapidXml(datra_str,
                                                                   from_file=False,
                                                                   attribute_prefix='@',
                                                                   cdata_key='#text',
                                                                   always_aslist=False,
                                                                   parse_cdata=True).unparse()
    assert init_rapidxml_with_CDADA.unparse() == repr(init_rapidxml_with_CDADA)
    assert init_rapidxml_with_CDADA.unparse(True) == str(init_rapidxml_with_CDADA)

def test_parse_cdata(init_rapidxml_with_CDADA):
    r = rapidxml.RapidXml()
    try:
        data = init_rapidxml_with_CDADA.unparse().encode('utf-8')
    except UnicodeDecodeError:
        data = init_rapidxml_with_CDADA.unparse()
    r.parse(data, from_file=False, parse_cdata=True)
    assert str(r) == str(init_rapidxml_with_CDADA)

def test_parse_from_file_cdata(init_rapidxml_with_CDADA, tmpdir):
    f = tmpdir.join("dump.xml")
    f.write(init_rapidxml_with_CDADA.unparse())
    r = rapidxml.RapidXml(str(f), from_file=True, parse_cdata=True)
    assert str(r) == str(init_rapidxml_with_CDADA)

def test_equals_cdata(init_rapidxml_with_CDADA):
    assert init_rapidxml_with_CDADA == init_rapidxml_with_CDADA
    root = init_rapidxml_with_CDADA.first_node()
    assert root == root
    assert root == init_rapidxml_with_CDADA.first_node()
    assert root.first_node() != root.first_node("test2")
    assert (root != root) == (not (root == root))

def test_parent_cdata(init_rapidxml_with_CDADA):
    assert init_rapidxml_with_CDADA.parent is None
    assert init_rapidxml_with_CDADA.first_node().parent == init_rapidxml_with_CDADA

def test_assign_cdata(init_rapidxml_with_CDADA):
    root = init_rapidxml_with_CDADA.first_node()
    root.name = "new_root"
    assert root.name == "new_root"
    test = root.first_node()
    test.name = "new_test"
    test.first_attribute().name = "new_attr1"
    test.first_attribute().next_attribute().value = "new_two"
    test = root.first_node("test")
    test.value = "some new text"
    assert test.value == "some new text"

