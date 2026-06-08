#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: test_issue6.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import rapidxml

def test_set_value_with_parse_cdata():
    r = rapidxml.RapidXml(b'<root><loc>old value</loc></root>',
                          parse_cdata=True)
    loc = r.first_node().first_node("loc")
    loc.value = "new value"
    assert loc.value == "new value"
    assert r.unparse() == '<root><loc>new value</loc></root>'

def test_set_value_with_cdata_node():
    r = rapidxml.RapidXml(b'<root><loc><![CDATA[old value]]></loc></root>',
                          parse_cdata=True)
    loc = r.first_node().first_node("loc")
    loc.value = "new value"
    assert loc.value == "new value"
    assert r.unparse() == '<root><loc><![CDATA[new value]]></loc></root>'

def test_set_value_without_parse_cdata():
    r = rapidxml.RapidXml(b'<root><loc>old value</loc></root>')
    loc = r.first_node().first_node("loc")
    loc.value = "new value"
    assert loc.value == "new value"
    assert r.unparse() == '<root><loc>new value</loc></root>'
