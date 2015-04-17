python_rapidxml
===============

A library providing python bindings for rapidxml

Example
---------------

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


Project Current State
===============

This project is currently under *heavy* development.
