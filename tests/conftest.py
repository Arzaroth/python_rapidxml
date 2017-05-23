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
	
@pytest.fixture(scope="function")
def init_rapidxml_with_CDADA():
    datra_str = "<root><test attr1=\"one\" attr2=\"two\" attr3=\"three\"/><test2><node id=\"1\"/><node id=\"2\"/><node id=\"3\"/></test2><test>some text</test><ns2:AdditionalData><ns2:Data TID=\"AD_1\"><![CDATA[{\"Cart\":{\"expirationTime\":\"2017-04-22T09:40\",\"id\":\"b469df3b-f626-4fe3-898c-825373e546a2\",\"products\":[\"1223\"],\"creationTime\":\"2017-04-21T09:40\",\"totalPrice\":{\"currencyCode\":\"EUR\",\"amount\":\"138.000\"}}}]]></ns2:Data></ns2:AdditionalData></root>"
    r = rapidxml.RapidXml(datra_str,
                          from_file=False,
                          attribute_prefix='@',
                          cdata_key='#text',
                          always_aslist=False,
                          parse_cdata=True)
    return r
