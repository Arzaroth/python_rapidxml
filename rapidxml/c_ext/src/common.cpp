/*
** -*- coding: utf-8 -*-
**
** File: common.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>

#include <common.h>

int _parse_args_for_name(PyObject* args,
                         PyObject* kwds,
                         Py_buffer* buf,
                         const char** name) {
  *name = NULL;
  if (buf != NULL) {
    buf->buf = NULL;
    buf->obj = NULL;
  }

  static char* kwlist[] = {"name", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s*", kwlist,
                                   buf)) {
    return false;
  }
  if (buf != NULL && buf->buf) {
    *name = static_cast<const char*>(buf->buf);
  }
  return true;
}

PyObject* _bind_result(rapidxml_BaseObject* self,
                       rapidxml::xml_base<>* base,
                       PyTypeObject* type) {
  rapidxml_BaseObject* new_base;

  new_base = reinterpret_cast<rapidxml_BaseObject*>
    (PyObject_CallObject(reinterpret_cast<PyObject*>(type),
                         NULL));
  new_base->underlying_obj = base;
  new_base->document = self->document;
  return reinterpret_cast<PyObject*>(new_base);
}
