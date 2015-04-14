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

PyObject* RapidXmlError;

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
  rapidxml_RapidXmlType.tp_base = &rapidxml_BaseType;
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
                     (PyObject *)&rapidxml_BaseType);
  Py_INCREF(&rapidxml_RapidXmlType);

  PyModule_AddObject(module,
                     "RapidXml",
                     (PyObject *)&rapidxml_RapidXmlType);

  RapidXmlError = PyErr_NewException("rapidxml.RapidXmlError",
                                     NULL, NULL);
  Py_INCREF(RapidXmlError);
  PyModule_AddObject(module,
                     "RapidXmlError",
                     RapidXmlError);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
