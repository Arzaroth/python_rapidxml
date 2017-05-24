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
  Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}

static PyObject* rapidxml_BaseObject_new(PyTypeObject* type,
                                         PyObject* args,
                                         PyObject* kwds) {
  rapidxml_BaseObject* self;

  self = reinterpret_cast<rapidxml_BaseObject*>(type->tp_alloc(type, 0));
  if (self != NULL) {
    self->underlying_obj = NULL;
    self->document = NULL;
  }
  return reinterpret_cast<PyObject*>(self);
}

static int rapidxml_BaseObject_init(rapidxml_BaseObject* self,
                                    PyObject* args,
                                    PyObject* kwds) {
  return 0;
}

static PyObject* rapidxml_BaseObject_copy(rapidxml_BaseObject* self,
                                          PyObject* args,
                                          PyObject* kwds) {
  PyObject* other = NULL;

  static char* kwlist[] = {"other", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "O", kwlist,
                                   &other)) {
    return NULL;
  }
  if (!IS_BASE(other)) {
    PyErr_SetString(PyExc_TypeError, "Expected instance of rapidxml.c_ext.Base");
    return NULL;
  }
  self->underlying_obj = reinterpret_cast<rapidxml_BaseObject*>(other)->underlying_obj;
  self->document = reinterpret_cast<rapidxml_BaseObject*>(other)->document;
  Py_INCREF(self);
  return reinterpret_cast<PyObject*>(self);
}

static PyObject* rapidxml_BaseObject_richcmp(PyObject* obj1,
                                             PyObject* obj2,
                                             int op) {
  PyObject* res;
  bool c;

  if (!(IS_BASE(obj1) && IS_BASE(obj2))) {
    PyErr_SetString(PyExc_TypeError, "Expected instances of rapidxml.c_ext.Base");
    return NULL;
  }
  switch (op) {
  case Py_EQ:
    c = (reinterpret_cast<rapidxml_BaseObject*>(obj1)->underlying_obj ==
         reinterpret_cast<rapidxml_BaseObject*>(obj2)->underlying_obj);
    break;
  case Py_NE:
    c = (reinterpret_cast<rapidxml_BaseObject*>(obj1)->underlying_obj !=
         reinterpret_cast<rapidxml_BaseObject*>(obj2)->underlying_obj);
    break;
  default:
    PyErr_SetNone(PyExc_NotImplementedError);
    return NULL;
  }
  res = c ? Py_True : Py_False;
  Py_INCREF(res);
  return res;
}

static PyObject* rapidxml_BaseObject_getname(rapidxml_BaseObject* self,
                                              void* closure) {
  PyObject* res;

  if (self->underlying_obj == NULL) {
    res = Py_BuildValue("s", "");
  } else {
    res = Py_BuildValue("s", self->underlying_obj->name());
#if PY_MAJOR_VERSION >= 3
    if (res == NULL && PyErr_Occurred()) {
      res = Py_BuildValue("y",
                          self->underlying_obj->name(),
                          self->underlying_obj->name_size());
    }
#endif
  }
  return res;
}

static int rapidxml_BaseObject_setname(rapidxml_BaseObject* self,
                                       PyObject* arg,
                                       void* closure) {
  Py_buffer name;

  if (self->underlying_obj == NULL || self->document == NULL) {
    PyErr_SetString(rapidxml_RapidXmlError,
                    "underlying mechanism failed");
    return -1;
  }
  if (arg == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Cannot delete name");
    return -1;
  }
  if (!PyArg_Parse(arg, "s*", &name)) {
    return -1;
  }
  self->underlying_obj->name(self->document->allocate_string(static_cast<const char*>(name.buf)));
  return 0;
}

static PyObject* rapidxml_BaseObject_getvalue(rapidxml_BaseObject* self,
                                              void* closure) {
  PyObject* res;

  if (self->underlying_obj == NULL) {
    res = Py_BuildValue("s", "");
  } else {
    res = Py_BuildValue("s", self->underlying_obj->value());
#if PY_MAJOR_VERSION >= 3
    if (res == NULL && PyErr_Occurred()) {
      res = Py_BuildValue("y",
                          self->underlying_obj->value(),
                          self->underlying_obj->value_size());
    }
#endif
  }
  return res;
}

static int rapidxml_BaseObject_setvalue(rapidxml_BaseObject* self,
                                        PyObject* arg,
                                        void* closure) {
  Py_buffer value;

  if (self->underlying_obj == NULL || self->document == NULL) {
    PyErr_SetString(rapidxml_RapidXmlError,
                    "underlying mechanism failed");
    return -1;
  }
  if (arg == NULL) {
    PyErr_SetString(PyExc_TypeError,
                    "Cannot delete value");
    return -1;
  }
  if (!PyArg_Parse(arg, "s*", &value)) {
    return -1;
  }
  self->underlying_obj->value(self->document->allocate_string(static_cast<const char*>(value.buf)));
  return 0;
}

static PyObject* rapidxml_BaseObject_getparent(rapidxml_BaseObject* self,
                                               void* closure) {
  rapidxml::xml_node<>* parent;

  if (self->underlying_obj == NULL || self->document == NULL) {
    PyErr_SetString(rapidxml_RapidXmlError,
                    "underlying mechanism failed");
    return NULL;
  }
  parent = self->underlying_obj->parent();
  if (parent == NULL) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  return _bind_result(self, parent, &rapidxml_NodeType);
}

static PyGetSetDef rapidxml_BaseObject_getseters[] = {
  {"name",
   (getter)rapidxml_BaseObject_getname, (setter)rapidxml_BaseObject_setname,
   "name of xml entity"},
  {"value",
   (getter)rapidxml_BaseObject_getvalue, (setter)rapidxml_BaseObject_setvalue,
   "value of xml entity"},
  {"parent",
   (getter)rapidxml_BaseObject_getparent, NULL,
   "gets node parent"},
  {NULL}
};

static PyMemberDef rapidxml_BaseObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_BaseObject_methods[] = {
  {"copy", reinterpret_cast<PyCFunction>(rapidxml_BaseObject_copy),
   METH_VARARGS | METH_KEYWORDS, "copy another Base object, returning current instance"},
  {NULL}
};

PyTypeObject rapidxml_BaseType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "rapidxml.c_ext.Base",           /* tp_name */
  sizeof(rapidxml_BaseObject),     /* tp_basicsize */
  0,                               /* tp_itemsize */
  reinterpret_cast<destructor>(rapidxml_BaseObject_dealloc), /* tp_dealloc */
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
  reinterpret_cast<richcmpfunc>(rapidxml_BaseObject_richcmp), /* tp_richcompare */
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
  reinterpret_cast<initproc>(rapidxml_BaseObject_init), /* tp_init */
  0,                               /* tp_alloc */
  reinterpret_cast<newfunc>(rapidxml_BaseObject_new), /* tp_new */
  0,                               /* tp_free */
  0,                               /* tp_is_gc */
  0,                               /* tp_bases */
  0,                               /* tp_mro */
  0,                               /* tp_cache */
  0,                               /* tp_subclasses */
  0,                               /* tp_weaklist */
};
