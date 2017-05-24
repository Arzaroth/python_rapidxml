#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: test_utf8.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import sys
import rapidxml

def test_utf8():
    data = "<root>éè</root>"
    if sys.version_info[0] >= 3:
        data = data.encode('utf-8')
    r = rapidxml.RapidXml(data)
    assert str(r) == r.unparse(pretty=True)
    assert repr(r) == r.unparse()
    assert data == r.unparse(raw=True)
    r.first_node().value = b'\x85'
    assert r.unparse(raw=True).decode('cp1252').encode('utf-8') == b"<root>\xe2\x80\xa6</root>"

def test_utf8_cdata():
    data = "<root><![CDATA[\"Càrt\"]]></root>"
    if sys.version_info[0] >= 3:
        data = data.encode('utf-8')
    r = rapidxml.RapidXml(data, parse_cdata=True)
    assert str(r) == r.unparse(pretty=True)
    assert repr(r) == r.unparse()
    assert data == r.unparse(raw=True)
    r.first_node().first_node().value = b'\x85'
    assert r.unparse(raw=True).decode('cp1252').encode('utf-8') == b"<root><![CDATA[\xe2\x80\xa6]]></root>"
