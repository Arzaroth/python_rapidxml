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
  "rapidxml",
  "python module for rapidxml bindings",
  -1,
  module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};

# define INITERROR return NULL

PyMODINIT_FUNC PyInit_rapidxml(void)

#else
# define INITERROR return

PyMODINIT_FUNC initrapidxml(void)
#endif
{
  PyObject* module;

  if (PyType_Ready(&rapidxml_BaseType) < 0)
    INITERROR;
  rapidxml_NodeType.tp_base = &rapidxml_BaseType;
  if (PyType_Ready(&rapidxml_NodeType) < 0)
    INITERROR;
  rapidxml_RapidXmlType.tp_base = &rapidxml_NodeType;
  if (PyType_Ready(&rapidxml_RapidXmlType) < 0)
    INITERROR;

#if PY_MAJOR_VERSION >= 3
  module = PyModule_Create(&moduledef);
#else
  module = Py_InitModule3("rapidxml",
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

  Py_INCREF(&rapidxml_RapidXmlType);
  PyModule_AddObject(module,
                     "RapidXml",
                     reinterpret_cast<PyObject *>(&rapidxml_RapidXmlType));

  rapidxml_RapidXmlError = PyErr_NewException("rapidxml.rapidxml_RapidXmlError",
                                     NULL, NULL);
  Py_INCREF(rapidxml_RapidXmlError);
  PyModule_AddObject(module,
                     "rapidxml_RapidXmlError",
                     rapidxml_RapidXmlError);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
