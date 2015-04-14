/*
** -*- coding: utf-8 -*-
**
** File: rapidxml_object.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <string>
#include <fstream>
#include <streambuf>
#include <cstring>
#include <cerrno>

#include <common.h>

static void rapidxml_RapidXmlObject_dealloc(rapidxml_BaseObject* self) {
  free(self->underlying_obj);
#if PY_MAJOR_VERSION >= 3
  Py_TYPE(self)->tp_free((PyObject*)self);
#else
  self->ob_type->tp_free((PyObject*)self);
#endif
}

static int rapidxml_RapidXmlObject_init(rapidxml_RapidXmlObject* self,
                                        PyObject* args,
                                        PyObject* kwds) {
  const char* text;
  int size;
  int from_file = 0;
  PyObject* from_file_obj = NULL;

  if (rapidxml_BaseType.tp_init((PyObject*)self, args, kwds) < 0) {
    return -1;
  }
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
      PyErr_SetString(RapidXmlError, strerror(errno));
      return -1;
    }
    self->text = std::vector<char>((std::istreambuf_iterator<char>(f)),
                                   std::istreambuf_iterator<char>());
  }
  self->text.push_back('\0');
  try {
    self->base.underlying_obj = new rapidxml::xml_document<>();
    ((rapidxml::xml_document<>*)self->base.underlying_obj)->parse<rapidxml::parse_no_utf8>(&self->text[0]);
  } catch (rapidxml::parse_error &e) {
    PyErr_SetString(RapidXmlError, e.what());
    return -1;
  }
  return 0;
}

static PyObject* rapidxml_RapidXmlObject_first_node(rapidxml_RapidXmlObject* self,
                                                    PyObject* args,
                                                    PyObject* kwds) {
  const char* name = NULL;

  static char* kwlist[] = {"name", NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|s", kwlist,
                                   &name)) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  rapidxml::xml_node<>* node = ((rapidxml::xml_document<>*)self->base.underlying_obj)->first_node(name);
  if (!node) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_RapidXmlObject_unparse(rapidxml_RapidXmlObject* self,
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
  rapidxml::print(std::back_inserter(xml),
                  *((rapidxml::xml_document<>*)self->base.underlying_obj),
                  !pretty ? rapidxml::print_no_indenting : 0);
  return Py_BuildValue("s", xml.c_str());
}

static PyObject* rapidxml_RapidXmlObject___str__(rapidxml_RapidXmlObject* self) {
  PyObject* args;
  PyObject* res;

  args = Py_BuildValue("(O)", Py_True);
  res = rapidxml_RapidXmlObject_unparse(self, args, NULL);
  Py_DECREF(args);
  return res;
}

static PyObject* rapidxml_RapidXmlObject___repr__(rapidxml_RapidXmlObject* self) {
  PyObject* args;
  PyObject* res;

  args = Py_BuildValue("(O)", Py_False);
  res = rapidxml_RapidXmlObject_unparse(self, args, NULL);
  Py_DECREF(args);
  return res;
}

static PyMemberDef rapidxml_RapidXmlObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_RapidXmlObject_methods[] = {
  {"unparse", (PyCFunction)rapidxml_RapidXmlObject_unparse,
   METH_VARARGS | METH_KEYWORDS, "return xml string"},
  {"first_node", (PyCFunction)rapidxml_RapidXmlObject_first_node,
   METH_VARARGS | METH_KEYWORDS, "gets first child node, optionally matching node name"},
  {NULL}
};

PyTypeObject rapidxml_RapidXmlType = {
  #if PY_MAJOR_VERSION >= 3
  PyVarObject_HEAD_INIT(NULL, 0)
  #else
  PyObject_HEAD_INIT(NULL)
  0,                               /* ob_size */
  #endif
  "rapidxml.RapidXml",             /* tp_name */
  sizeof(rapidxml_RapidXmlObject), /* tp_basicsize */
  0,                               /* tp_itemsize */
  (destructor)rapidxml_RapidXmlObject_dealloc, /* tp_dealloc */
  0,                               /* tp_print */
  0,                               /* tp_getattr */
  0,                               /* tp_setattr */
  0,                               /* tp_reserved */
  (reprfunc)rapidxml_RapidXmlObject___repr__, /* tp_repr */
  0,                               /* tp_as_number */
  0,                               /* tp_as_sequence */
  0,                               /* tp_as_mapping */
  0,                               /* tp_hash  */
  0,                               /* tp_call */
  (reprfunc)rapidxml_RapidXmlObject___str__, /* tp_str */
  0,                               /* tp_getattro */
  0,                               /* tp_setattro */
  0,                               /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT,              /*tp_flags*/
  "class representing a rapidxml::xml_document", /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  rapidxml_RapidXmlObject_methods, /* tp_methods */
  rapidxml_RapidXmlObject_members, /* tp_members */
  0,                               /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  (initproc)rapidxml_RapidXmlObject_init, /* tp_init */
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
