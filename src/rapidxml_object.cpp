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
#include <rapidxml_print.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <cstring>
#include <cerrno>

#include <common.h>

typedef struct {
  PyObject_HEAD
  rapidxml::xml_document<> doc;
  std::vector<char> text;
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
  const char* text;
  int size;
  int from_file = 0;
  PyObject* from_file_obj = NULL;

  static char* kwlist[] = {"text", "from_file", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s#|O", kwlist,
                                   &text, &size, &from_file_obj)) {
    return -1;
  }
  if (from_file_obj) {
    from_file = PyObject_IsTrue(from_file_obj);
  }

  if (!from_file) {
    self->text = std::vector<char>(text, text + size);
  } else {
    std::ifstream f(text, std::ios::binary);
    if (f.fail()) {
      PyErr_SetString(EXCEPT_NAME, strerror(errno));
      return -1;
    }
    self->text = std::vector<char>((std::istreambuf_iterator<char>(f)),
                                   std::istreambuf_iterator<char>());
  }
  self->text.push_back('\0');
  try {
    self->doc.parse<rapidxml::parse_no_utf8>(&self->text[0]);
  } catch (rapidxml::parse_error &e) {
    PyErr_SetString(EXCEPT_NAME, e.what());
    return -1;
  }
  return 0;
}

static PyObject* CAT(OBJECT_NAME, _unparse)(OBJ_OBJECT* self,
                                            PyObject* args,
                                            PyObject* kwds) {
  int pretty = 0;
  PyObject* pretty_obj = NULL;

  static char* kwlist[] = {"pretty", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, &pretty_obj)) {
    pretty = 0;
  } else if (pretty_obj) {
    pretty = PyObject_IsTrue(pretty_obj);
  }
  std::string xml;
  rapidxml::print(std::back_inserter(xml), self->doc,
                  !pretty ? rapidxml::print_no_indenting : 0);
  return Py_BuildValue("s", xml.c_str());
}

static PyObject* CAT(OBJECT_NAME, ___str__)(OBJ_OBJECT* self) {
  return CAT(OBJECT_NAME, _unparse)(self, Py_BuildValue("(O)", Py_True), NULL);
}

static PyObject* CAT(OBJECT_NAME, ___repr__)(OBJ_OBJECT* self) {
  return CAT(OBJECT_NAME, _unparse)(self, Py_BuildValue("(O)", Py_False), NULL);
}

static PyMemberDef OBJ_MEMBERS[] = {
  {NULL}
};

static PyMethodDef OBJ_METHS[] = {
  {"unparse", (PyCFunction)CAT(OBJECT_NAME, _unparse),
   METH_VARARGS | METH_KEYWORDS, "return xml string"},
  {NULL}
};

PyTypeObject OBJ_TYPE = {
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
  (reprfunc)CAT(OBJECT_NAME, ___repr__), /* tp_repr */
  0,                               /* tp_as_number */
  0,                               /* tp_as_sequence */
  0,                               /* tp_as_mapping */
  0,                               /* tp_hash  */
  0,                               /* tp_call */
  (reprfunc)CAT(OBJECT_NAME, ___str__), /* tp_str */
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
