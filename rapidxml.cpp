/*
** -*- coding: utf-8 -*-
**
** File: rapidxml.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>

#define STR(x) #x
#define STRINGIFY(x) STR(x)
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

struct module_state {
  PyObject *error;
};

#define MODULE_DESC "rapidxml module for rapidxml bindings"
#define MODULE_NAME rapidxml
#define MODULE_METHS CAT(MODULE_NAME, _methods)

#define OBJECT_NAME RapidXml
#define OBJ_TYPE CAT(MODULE_NAME, CAT(_, CAT(OBJECT_NAME, Type)))
#define OBJ_OBJECT CAT(MODULE_NAME, CAT(_, CAT(OBJECT_NAME, Object)))
#define OBJ_METHS CAT(OBJECT_NAME, _methods)
#define OBJ_MEMBERS CAT(OBJECT_NAME, _members)

#define EXCEPT_NAME CAT(OBJECT_NAME, Error)

static PyObject* EXCEPT_NAME;

typedef struct {
  PyObject_HEAD
  rapidxml::xml_document<> doc;
} OBJ_OBJECT;

static void CAT(OBJECT_NAME, _dealloc)(OBJ_OBJECT* self) {
  #if PY_MAJOR_VERSION >= 3
  Py_TYPE(self)->tp_free((PyObject*)self);
  #else
  self->ob_type->tp_free((PyObject*)self);
  #endif
}

static PyObject* CAT(OBJECT_NAME, _new)(PyTypeObject* type,
                                        PyObject* args,
                                        PyObject* kwds) {
  OBJ_OBJECT* self;

  self = (OBJ_OBJECT*)type->tp_alloc(type, 0);
  return (PyObject*)self;
}

static int CAT(OBJECT_NAME, _init)(OBJ_OBJECT* self,
                                   PyObject* args,
                                   PyObject* kwds) {
  char* text;

  static char* kwlist[] = {"text", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s", kwlist,
                                   &text)) {
    return -1;
  }
  try {
    self->doc.parse<0>(text);
  } catch (rapidxml::parse_error &e) {
    PyErr_SetString(EXCEPT_NAME, e.what());
    return -1;
  }
  return 0;
}

static PyMemberDef OBJ_MEMBERS[] = {
  {NULL}
};

static PyMethodDef OBJ_METHS[] = {
  {NULL}
};

static PyTypeObject OBJ_TYPE = {
  #if PY_MAJOR_VERSION >= 3
  PyVarObject_HEAD_INIT(NULL, 0)
  #else
  PyObject_HEAD_INIT(NULL)
  0,                               /* ob_size */
  #endif
  STRINGIFY(MODULE_NAME) "." STRINGIFY(OBJECT_NAME), /* tp_name */
  sizeof(OBJ_OBJECT),              /* tp_basicsize */
  0,                               /* tp_itemsize */
  (destructor)CAT(OBJECT_NAME, _dealloc), /* tp_dealloc */
  0,                               /* tp_print */
  0,                               /* tp_getattr */
  0,                               /* tp_setattr */
  0,                               /* tp_reserved */
  0,                               /* tp_repr */
  0,                               /* tp_as_number */
  0,                               /* tp_as_sequence */
  0,                               /* tp_as_mapping */
  0,                               /* tp_hash  */
  0,                               /* tp_call */
  0,                               /* tp_str */
  0,                               /* tp_getattro */
  0,                               /* tp_setattro */
  0,                               /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
  "RapidXml objects",              /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  OBJ_METHS,                       /* tp_methods */
  OBJ_MEMBERS,                     /* tp_members */
  0,                               /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  (initproc)CAT(OBJECT_NAME, _init), /* tp_init */
  0,                               /* tp_alloc */
  CAT(OBJECT_NAME, _new),          /* tp_new */
};

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
