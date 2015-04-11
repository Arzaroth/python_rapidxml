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

PyObject* EXCEPT_NAME;

static PyMethodDef MODULE_METHS[] = {
  {NULL}
};

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  STRINGIFY(MODULE_NAME),
  MODULE_DESC,
  -1,
  MODULE_METHS,
  NULL,
  NULL,
  NULL,
  NULL
};

# define INITERROR return NULL

PyMODINIT_FUNC CAT(PyInit_, MODULE_NAME)(void)

#else
# define INITERROR return

PyMODINIT_FUNC CAT(init, MODULE_NAME)(void)
#endif
{
  PyObject* module;

  OBJ_TYPE.tp_new = PyType_GenericNew;
  if (PyType_Ready(&OBJ_TYPE) < 0)
    INITERROR;

#if PY_MAJOR_VERSION >= 3
  module = PyModule_Create(&moduledef);
#else
  module = Py_InitModule3(STRINGIFY(MODULE_NAME),
                          MODULE_METHS,
                          MODULE_DESC);
#endif
  if (module == NULL)
    INITERROR;

  Py_INCREF(&OBJ_TYPE);
  PyModule_AddObject(module,
                     STRINGIFY(OBJECT_NAME),
                     (PyObject *)&OBJ_TYPE);

  EXCEPT_NAME = PyErr_NewException(STRINGIFY(MODULE_NAME) "." STRINGIFY(EXCEPT_NAME),
                                   NULL, NULL);
  Py_INCREF(EXCEPT_NAME);
  PyModule_AddObject(module,
                     STRINGIFY(EXCEPT_NAME),
                     EXCEPT_NAME);
#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
