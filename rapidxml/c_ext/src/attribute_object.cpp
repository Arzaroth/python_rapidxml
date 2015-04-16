/*
** -*- coding: utf-8 -*-
**
** File: attribute_object.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>
#include <string>

#include <common.h>

static int rapidxml_AttributeObject_init(rapidxml_AttributeObject* self,
                                         PyObject* args,
                                         PyObject* kwds) {
  return rapidxml_BaseType.tp_init(reinterpret_cast<PyObject*>(self), args, kwds);
}

static PyObject* rapidxml_AttributeObject_previous_attribute(rapidxml_AttributeObject* self,
                                                             PyObject* args,
                                                             PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_attribute<>* attribute;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  attribute = static_cast<rapidxml::xml_attribute<>*>(self->base.underlying_obj)->previous_attribute(name);
  if (attribute == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      attribute, &rapidxml_AttributeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_AttributeObject_next_attribute(rapidxml_AttributeObject* self,
                                                         PyObject* args,
                                                         PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_attribute<>* attribute;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  attribute = static_cast<rapidxml::xml_attribute<>*>(self->base.underlying_obj)->next_attribute(name);
  if (attribute == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      attribute, &rapidxml_AttributeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyMemberDef rapidxml_AttributeObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_AttributeObject_methods[] = {
  {"previous_attribute", reinterpret_cast<PyCFunction>(rapidxml_AttributeObject_previous_attribute),
   METH_VARARGS | METH_KEYWORDS, "gets previous attribute, optionally matching attribute name"},
  {"next_attribute", reinterpret_cast<PyCFunction>(rapidxml_AttributeObject_next_attribute),
   METH_VARARGS | METH_KEYWORDS, "gets next attribute, optionally matching attribute name"},
  {NULL}
};

PyTypeObject rapidxml_AttributeType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "rapidxml._rapidxml.Attribute",  /* tp_name */
  sizeof(rapidxml_AttributeObject), /* tp_basicsize */
  0,                               /* tp_itemsize */
  0,                               /* tp_dealloc */
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
  0,                               /* tp_repr */
  0,                               /* tp_getattro */
  0,                               /* tp_setattro */
  0,                               /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT,              /* tp_flags */
  "class representing a rapidxml::xml_attribute", /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  rapidxml_AttributeObject_methods, /* tp_methods */
  rapidxml_AttributeObject_members, /* tp_members */
  0,                               /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  reinterpret_cast<initproc>(rapidxml_AttributeObject_init), /* tp_init */
  0,                               /* tp_alloc */
  0,                               /* tp_new */
  0,                               /* tp_free */
  0,                               /* tp_is_gc */
  0,                               /* tp_bases */
  0,                               /* tp_mro */
  0,                               /* tp_cache */
  0,                               /* tp_subclasses */
  0,                               /* tp_weaklist */
};
