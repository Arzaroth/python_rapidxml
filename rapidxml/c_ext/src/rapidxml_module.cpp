/*
** -*- coding: utf-8 -*-
**
** File: rapidxml_module.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>

#include <common.h>

PyObject* rapidxml_RapidXmlError;

static PyMethodDef module_methods[] = {
  {NULL}
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "rapidxml._rapidxml",
  "python module for rapidxml bindings",
  -1,
  module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};

# define INITERROR return NULL

PyMODINIT_FUNC PyInit__rapidxml(void)

#else
# define INITERROR return

PyMODINIT_FUNC init_rapidxml(void)
#endif
{
  PyObject* module;

  if (PyType_Ready(&rapidxml_BaseType) < 0)
    INITERROR;
  rapidxml_NodeType.tp_base = &rapidxml_BaseType;
  if (PyType_Ready(&rapidxml_NodeType) < 0)
    INITERROR;
  rapidxml_AttributeType.tp_base = &rapidxml_BaseType;
  if (PyType_Ready(&rapidxml_AttributeType) < 0)
    INITERROR;
  rapidxml_DocumentType.tp_base = &rapidxml_NodeType;
  if (PyType_Ready(&rapidxml_DocumentType) < 0)
    INITERROR;

  if (PyType_Ready(&rapidxml_NodeIteratorType) < 0)
    INITERROR;
  if (PyType_Ready(&rapidxml_AttributeIteratorType) < 0)
    INITERROR;

#if PY_MAJOR_VERSION >= 3
  module = PyModule_Create(&moduledef);
#else
  module = Py_InitModule3("rapidxml._rapidxml",
                          module_methods,
                          "rapidxml module for rapidxml bindings");
#endif
  if (module == NULL)
    INITERROR;

  Py_INCREF(&rapidxml_BaseType);
  PyModule_AddObject(module,
                     "Base",
                     reinterpret_cast<PyObject *>(&rapidxml_BaseType));

  Py_INCREF(&rapidxml_NodeType);
  PyModule_AddObject(module,
                     "Node",
                     reinterpret_cast<PyObject *>(&rapidxml_NodeType));

  Py_INCREF(&rapidxml_AttributeType);
  PyModule_AddObject(module,
                     "Attribute",
                     reinterpret_cast<PyObject *>(&rapidxml_AttributeType));

  Py_INCREF(&rapidxml_DocumentType);
  PyModule_AddObject(module,
                     "Document",
                     reinterpret_cast<PyObject *>(&rapidxml_DocumentType));

  Py_INCREF(&rapidxml_NodeIteratorType);
  PyModule_AddObject(module,
                     "NodeIterator",
                     reinterpret_cast<PyObject *>(&rapidxml_NodeIteratorType));

  Py_INCREF(&rapidxml_AttributeIteratorType);
  PyModule_AddObject(module,
                     "AttributeIterator",
                     reinterpret_cast<PyObject *>(&rapidxml_AttributeIteratorType));

  rapidxml_RapidXmlError = PyErr_NewException("rapidxml._rapidxml.RapidXmlError",
                                              NULL, NULL);
  Py_INCREF(rapidxml_RapidXmlError);
  PyModule_AddObject(module,
                     "RapidXmlError",
                     rapidxml_RapidXmlError);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
