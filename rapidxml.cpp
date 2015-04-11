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

#define STR(x) #x
#define STRINGIFY(x) STR(x)
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

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
#define MODULE_NAME rapidxml
#define OBJ_NAME RapidXml

#define OBJ_TYPE CAT(MODULE_NAME, CAT(_, CAT(OBJ_NAME, Type)))
#define OBJ_OBJECT CAT(MODULE_NAME, CAT(_, CAT(OBJ_NAME, Object)))
#define MODULE_METHS CAT(MODULE_NAME, _methods)

typedef struct {
  PyObject_HEAD
} OBJ_OBJECT;

static PyTypeObject OBJ_TYPE = {
  #if PY_MAJOR_VERSION >= 3
  PyVarObject_HEAD_INIT(NULL, 0)
  #else
  PyObject_HEAD_INIT(NULL)
  0,                               /*ob_size*/
  #endif
  STRINGIFY(MODULE_NAME) "." STRINGIFY(OBJ_NAME), /*tp_name*/
  sizeof(OBJ_OBJECT), /*tp_basicsize*/
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

static PyMethodDef MODULE_METHS[] = {
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
  STRINGIFY(MODULE_NAME),
  MODULE_DESC,
  sizeof(struct module_state),
  MODULE_METHS,
  NULL,
  module_traverse,
  module_clear,
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

  struct module_state* st = GETSTATE(module);
  st->error = PyErr_NewException(STRINGIFY(MODULE_NAME) ".Error",
                                 NULL, NULL);
  if (st->error == NULL) {
    Py_DECREF(module);
    INITERROR;
  }

  Py_INCREF(&OBJ_TYPE);
  PyModule_AddObject(module,
                     STRINGIFY(OBJ_NAME),
                     (PyObject *)&OBJ_TYPE);

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
