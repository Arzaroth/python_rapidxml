#!/usr/bin/env python
# -*- encoding: cdata -*-
#
# File: test_cdata.py
# by Amedeo Bussi
# amedeobussi@live.it
#

import sys
import rapidxml
import json

def test_utf8():
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
	
    print("Expected cdata object: " + str(object))

    r = rapidxml.RapidXml(data)

    object_received = json.load(r.first_node().first_node().first_node().value)

    print("Expected cdata object: " + str(object_received))

    assert object_received == object