#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: rapidxml.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#

import _rapidxml

class DictNodeIterator(object):
    def __init__(self,
                 iterable,
                 attribute_prefix,
                 cdata_key,
                 always_aslist):
        self._iter = iterable
        self.attribute_prefix = attribute_prefix
        self.cdata_key = cdata_key
        self.always_aslist = always_aslist

    def __next__(self):
        return self.next()

    def next(self):
        return DictNode(self.attribute_prefix,
                        self.cdata_key,
                        self.always_aslist).copy(next(self._iter))

    def __iter__(self):
        return self


class DictNode(_rapidxml.Node):
    def __init__(self, attribute_prefix='@', cdata_key='#text', always_aslist=False):
        _rapidxml.Node.__init__(self)
        self.attribute_prefix = attribute_prefix
        self.cdata_key = cdata_key
        self.always_aslist = always_aslist

    def get_nodes(self, name):
        node = self.first_node(name)
        if node is None:
            return None
        res = [DictNode(self.attribute_prefix,
                        self.cdata_key,
                        self.always_aslist).copy(node)]
        node = node.next_sibling(name)
        if node is None and not self.always_aslist:
            return res[0]
        while node is not None:
            res.append(DictNode(self.attribute_prefix,
                                self.cdata_key,
                                self.always_aslist).copy(node))
            node = node.next_sibling(name)
        return res

    def get_attributes(self, name):
        attribute = self.first_attribute(name)
        if attribute is None:
            return None
        res = [attribute]
        attribute = attribute.next_attribute(name)
        if attribute is None and not self.always_aslist:
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

    def __contains__(self, name):
        try:
            self[name]
        except:
            return False
        return True

    def __iter__(self):
        return DictNodeIterator(self.children,
                                self.attribute_prefix,
                                self.cdata_key,
                                self.always_aslist)


class RapidXml(DictNode, _rapidxml.Document):
    def __init__(self,
                 text="",
                 from_file=False,
                 attribute_prefix='@',
                 cdata_key='#text',
                 always_aslist=False):
        DictNode.__init__(self, attribute_prefix, cdata_key, always_aslist)
        _rapidxml.Document.__init__(self, text, from_file)

    def allocate_node(self, *args):
        return DictNode(self.attribute_prefix,
                        self.cdata_key,
                        self.always_aslist).copy(super(RapidXml, self).allocate_node(*args))
