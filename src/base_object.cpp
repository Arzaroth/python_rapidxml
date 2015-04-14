/*
** -*- coding: utf-8 -*-
**
** File: base_object.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>

#include <common.h>

static void rapidxml_BaseObject_dealloc(rapidxml_BaseObject* self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* rapidxml_BaseObject_new(PyTypeObject* type,
                                         PyObject* args,
                                         PyObject* kwds) {
  rapidxml_BaseObject* self;

  self = (rapidxml_BaseObject*)type->tp_alloc(type, 0);
  if (self != NULL) {
    self->underlying_obj = NULL;
  }
  return (PyObject*)self;
}

static int rapidxml_BaseObject_init(rapidxml_BaseObject* self,
                                    PyObject* args,
                                    PyObject* kwds) {
  return 0;
}

static PyObject* rapidxml_BaseObject_getname(rapidxml_BaseObject* self,
                                             void* closure) {
  if (self->underlying_obj == NULL) {
    return Py_BuildValue("s", "");
  }
  return Py_BuildValue("s", self->underlying_obj->name());
}

static int rapidxml_BaseObject_setname(rapidxml_BaseObject* self,
                                       PyObject* arg,
                                       void* closure) {
  const char* name;

  if (self->underlying_obj == NULL || arg == NULL) {
    return -1;
  }
  if (!
#if PY_MAJOR_VERSION >= 3
      PyUnicode_Check(arg)
#else
      PyString_Check(arg)
#endif
      ) {
    PyErr_SetString(PyExc_TypeError,
                    "name attribute must be a string");
    return -1;
  }
  if (!PyArg_Parse(arg, "s", &name)) {
    return -1;
  }
  self->underlying_obj->name(self->memory_pool.allocate_string(name));
  return 0;
}

static PyObject* rapidxml_BaseObject_getvalue(rapidxml_BaseObject* self,
                                              void* closure) {
  if (self->underlying_obj == NULL) {
    return Py_BuildValue("s", "");
  }
  return Py_BuildValue("s", self->underlying_obj->value());
}

static int rapidxml_BaseObject_setvalue(rapidxml_BaseObject* self,
                                        PyObject* arg,
                                        void* closure) {
  const char* value;

  if (self->underlying_obj == NULL || arg == NULL) {
    return -1;
  }
  if (!
#if PY_MAJOR_VERSION >= 3
      PyUnicode_Check(arg)
#else
      PyString_Check(arg)
#endif
      ) {
    PyErr_SetString(PyExc_TypeError,
                    "value attribute must be a string");
    return -1;
  }
  if (!PyArg_Parse(arg, "s", &value)) {
    return -1;
  }
  self->underlying_obj->value(self->memory_pool.allocate_string(value));
  return 0;
}

static PyGetSetDef rapidxml_BaseObject_getseters[] = {
  {"name",
   (getter)rapidxml_BaseObject_getname, (setter)rapidxml_BaseObject_setname,
   "name of xml entity"},
  {"value",
   (getter)rapidxml_BaseObject_getvalue, (setter)rapidxml_BaseObject_setvalue,
   "value of xml entity"},
  {NULL}
};

static PyMemberDef rapidxml_BaseObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_BaseObject_methods[] = {
  {NULL}
};

PyTypeObject rapidxml_BaseType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "rapidxml.Base",                 /* tp_name */
  sizeof(rapidxml_BaseObject),     /* tp_basicsize */
  0,                               /* tp_itemsize */
  (destructor)rapidxml_BaseObject_dealloc, /* tp_dealloc */
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
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
  "class representing a rapidxml::xml_base", /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  rapidxml_BaseObject_methods,     /* tp_methods */
  rapidxml_BaseObject_members,     /* tp_members */
  rapidxml_BaseObject_getseters,   /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  (initproc)rapidxml_BaseObject_init, /* tp_init */
  0,                               /* tp_alloc */
  (newfunc)rapidxml_BaseObject_new, /* tp_new */
  0,                               /* tp_free */
  0,                               /* tp_is_gc */
  0,                               /* tp_bases */
  0,                               /* tp_mro */
  0,                               /* tp_cache */
  0,                               /* tp_subclasses */
  0,                               /* tp_weaklist */
};
