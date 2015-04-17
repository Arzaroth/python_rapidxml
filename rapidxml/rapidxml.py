#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: rapidxml.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import rapidxml._rapidxml

class DictNode(rapidxml._rapidxml.Node):
    def get_nodes(self, name):
        node = self.first_node(name)
        if node is None:
            return None
        res = [DictNode().copy(node)]
        node = node.next_sibling(name)
        if node is None:
            return res[0]
        while node is not None:
            res.append(DictNode().copy(node))
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
        if name.startswith('@'):
            res = self.get_attributes(name[1:])
        else:
            res = self.get_nodes(name)
        if res is None:
            raise KeyError(name)
        return res

class RapidXml(DictNode, rapidxml._rapidxml.Document):
    pass
