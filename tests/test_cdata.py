#!/usr/bin/env python
# -*- encoding: utf-8 -*-
#
# File: test_cdata.py
# by Amedeo Bussi
# amedeobussi@live.it
#

import sys
import rapidxml
import ast

def test_cdata():
    data = "<ns2:AdditionalData><ns2:Data TID=\"AD_1\"><![CDATA[{\"Cart\":{\"expirationTime\":\"2017-04-22T09:40\",\"id\":\"b469df3b-f626-4fe3-898c-825373e546a2\",\"products\":[\"1223\"],\"creationTime\":\"2017-04-21T09:40\",\"totalPrice\":{\"currencyCode\":\"EUR\",\"amount\":\"138.000\"}}}]]></ns2:Data></ns2:AdditionalData>"

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

    r = rapidxml.RapidXml(data,
                          from_file=False,
                          attribute_prefix='@',
                          cdata_key='#text',
                          always_aslist=False,
                          parse_cdata=True)

    object_received = ast.literal_eval(r.first_node().first_node().first_node().value)

    assert object_received == object



