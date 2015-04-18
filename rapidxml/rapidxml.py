#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: rapidxml.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import rapidxml._rapidxml

class DictNode(rapidxml._rapidxml.Node):
    def __init__(self, attribute_prefix='@', cdata_key='#text'):
        rapidxml._rapidxml.Node.__init__(self)
        self.attribute_prefix = attribute_prefix
        self.cdata_key = cdata_key

    def get_nodes(self, name):
        node = self.first_node(name)
        if node is None:
            return None
        res = [DictNode(self.attribute_prefix, self.cdata_key).copy(node)]
        node = node.next_sibling(name)
        if node is None:
            return res[0]
        while node is not None:
            res.append(DictNode(self.attribute_prefix, self.cdata_key).copy(node))
            node = node.next_sibling(name)
        return res

    def get_attributes(self, name):
        attribute = self.first_attribute(name)
        if attribute is None:
            return None
        res = [attribute]
        attribute = attribute.next_attribute(name)
        if attribute is None:
            return res[0]
        while attribute is not None:
            res.append(attribute)
            attribute = attribute.next_attribute(name)
        return res

    def __getitem__(self, name):
        res = None
        if name == self.cdata_key:
            res = self.value
        elif name.startswith(self.attribute_prefix):
            res = self.get_attributes(name[len(self.attribute_prefix):])
        else:
            res = self.get_nodes(name)
        if res is None:
            raise KeyError(name)
        return res

class RapidXml(DictNode, rapidxml._rapidxml.Document):
    def __init__(self,
                 text="",
                 from_file=False,
                 attribute_prefix='@',
                 cdata_key='#text'):
        DictNode.__init__(self, attribute_prefix, cdata_key)
        rapidxml._rapidxml.Document.__init__(self, text, from_file)
