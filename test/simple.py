#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# File: simple.py
# by Arzaroth Lekva
# arzaroth@arzaroth.com
#
import rapidxml

r = rapidxml.Document("<test/><test2>foo</test2><test></test>") # parsing from string
test = r.first_node("test") # get first node named test
assert(test.name == "test")
assert(test.value == "")
test.name = "foo" # changing node's name to foo
assert(test.name == "foo")

test2 = r.first_node("test2")
assert(test2.name == "test2")
assert(test2.value == "foo")
test2.value = "bar" # changing node's value to bar
assert(test2.value == "bar")

print(str(r)) # will output prettified string of the xml document
print(test) # also works for nodes

with open('dump.xml', 'w') as f:
    f.write(str(r))
r = rapidxml.RapidXml("dump.xml", True) # loading from file

assert(str(r) == r.unparse(True)) # is always True
assert(repr(r) == r.unparse()) # also always True, returns flat version
