/*
** -*- coding: utf-8 -*-
**
** File: rapidxml.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <rapidxml.hpp>

struct module_state {
  PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
# define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
# define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

#define MODULE_DESC "rapidxml module for rapidxml bindings"

typedef struct {
  PyObject_HEAD
} rapidxml_RapidXmlObject;

static PyTypeObject rapidxml_RapidXmlType = {
  #if PY_MAJOR_VERSION >= 3
  PyVarObject_HEAD_INIT(NULL, 0)
  #else
  PyObject_HEAD_INIT(NULL)
  0,                               /*ob_size*/
  #endif
  "rapidxml.RapidXml",             /*tp_name*/
  sizeof(rapidxml_RapidXmlObject), /*tp_basicsize*/
  0,                               /*tp_itemsize*/
  0,                               /*tp_dealloc*/
  0,                               /*tp_print*/
  0,                               /*tp_getattr*/
  0,                               /*tp_setattr*/
  0,                               /*tp_reserved*/
  0,                               /*tp_repr*/
  0,                               /*tp_as_number*/
  0,                               /*tp_as_sequence*/
  0,                               /*tp_as_mapping*/
  0,                               /*tp_hash */
  0,                               /*tp_call*/
  0,                               /*tp_str*/
  0,                               /*tp_getattro*/
  0,                               /*tp_setattro*/
  0,                               /*tp_as_buffer*/
  Py_TPFLAGS_DEFAULT,              /*tp_flags*/
  "RapidXml objects",              /* tp_doc */
};

static PyMethodDef rapidxml_methods[] = {
  {NULL}
};

#if PY_MAJOR_VERSION >= 3

static int module_traverse(PyObject* m, visitproc visit, void* arg) {
  Py_VISIT(GETSTATE(m)->error);
  return 0;
}

static int module_clear(PyObject* m) {
  Py_CLEAR(GETSTATE(m)->error);
  return 0;
}

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "rapidxml",
  MODULE_DESC,
  sizeof(struct module_state),
  rapidxml_methods,
  NULL,
  module_traverse,
  module_clear,
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

  rapidxml_RapidXmlType.tp_new = PyType_GenericNew;
  if (PyType_Ready(&rapidxml_RapidXmlType) < 0)
    INITERROR;

#if PY_MAJOR_VERSION >= 3
  module = PyModule_Create(&moduledef);
#else
  module = Py_InitModule3("rapidxml", rapidxml_methods, MODULE_DESC);
#endif
  if (module == NULL)
    INITERROR;

  struct module_state* st = GETSTATE(module);
  st->error = PyErr_NewException("rapidxml.Error", NULL, NULL);
  if (st->error == NULL) {
    Py_DECREF(module);
    INITERROR;
  }

  Py_INCREF(&rapidxml_RapidXmlType);
  PyModule_AddObject(module, "RapidXml", (PyObject *)&rapidxml_RapidXmlType);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
