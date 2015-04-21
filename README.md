## python_rapidxml

A library providing python bindings for rapidxml

### Example

    import rapidxml

    r = rapidxml.RapidXml("<test/><test2>foo</test2><test></test>") # parsing from string
    test = r.first_node("test") # get first node named test
    test.name = "foo" # changing node's name to foo
    r.first_node("test2").value = "bar" # changing node's value to bar

    print(str(r)) # will output prettified string of the xml document
    print(test) # also works for nodes

    with open('dump.xml', 'w') as f:
        f.write(str(r))
    r = rapidxml.RapidXml("dump.xml", True) # loading from file

    assert(str(r) == r.unparse(True)) # is always True
    assert(repr(r) == r.unparse()) # also always True, returns flat version


### Install

[![Latest Version](https://pypip.in/version/RapidXml/badge.svg)](https://pypi.python.org/pypi/RapidXml/)
[![Supported Python Versions](https://pypip.in/py_versions/RapidXml/badge.svg)](https://pypi.python.org/pypi/RapidXml/)

If you have downloaded the source code:

    python setup.py install

or if you want to obtain a copy from the Pypi repository:

    pip install rapidxml

Both commands will install the required package dependencies.

A distribution package can be obtained for manual installation at:

    http://pypi.python.org/pypi/RapidXml


### Source

python_rapidxml's git repo is available on GitHub, which can be browsed at [github](https://github.com/Arzaroth/python_rapidxml) and cloned like that:

    git clone https://github.com/Arzaroth/python_rapidxml.git


### License

MIT license. See the LICENSE file.


### Development status

[![Build Status](https://travis-ci.org/Arzaroth/python_rapidxml.svg?branch=1.0)](https://travis-ci.org/Arzaroth/python_rapidxml)

This project is currently under development.
