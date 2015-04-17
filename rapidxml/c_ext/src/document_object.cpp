/*
** -*- coding: utf-8 -*-
**
** File: document_object.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>
#include <vector>
#include <fstream>
#include <streambuf>
#include <cstring>
#include <cerrno>

#include <common.h>

static void rapidxml_DocumentObject_dealloc(rapidxml_DocumentObject* self) {
  delete self->base.base.underlying_obj;
  Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}

static PyObject* rapidxml_DocumentObject_parse(rapidxml_DocumentObject* self,
                                               PyObject* args,
                                               PyObject* kwds) {
  const char* text = NULL;
  int from_file = 0;
  PyObject* from_file_obj = NULL;
  char kw_text[] = "text";
  char kw_from_file[] = "from_file";
  std::vector<char> text_vector;
  PyObject* res;

  static char* kwlist[] = {kw_text, kw_from_file, NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "s|O", kwlist,
                                   &text, &from_file_obj)) {
    goto fail;
  }
  if (from_file_obj) {
    from_file = PyObject_IsTrue(from_file_obj);
  }

  if (from_file) {
    std::ifstream f(text, std::ios::binary);
    if (f.fail()) {
      PyErr_SetString(rapidxml_RapidXmlError, strerror(errno));
      goto fail;
    }
    text_vector = std::vector<char>((std::istreambuf_iterator<char>(f)),
                                    std::istreambuf_iterator<char>());
    text_vector.push_back(0);
    text = &text_vector[0];
  }
  try {
    self->base.base.document->clear();
    (self->base.base.document
     ->parse<rapidxml::parse_no_utf8 | rapidxml::parse_no_data_nodes>)
      (self->base.base.document->allocate_string(text));
  } catch (rapidxml::parse_error &e) {
    PyErr_SetString(rapidxml_RapidXmlError, e.what());
    goto fail;
  }
  res = Py_True;
  goto end;
 fail:
  res = Py_False;
 end:
  Py_INCREF(res);
  return res;
}

static int rapidxml_DocumentObject_init(rapidxml_DocumentObject* self,
                                        PyObject* args,
                                        PyObject* kwds) {
  const char* text = NULL;
  PyObject* from_file_obj = NULL;
  char kw_text[] = "text";
  char kw_from_file[] = "from_file";

  if (rapidxml_NodeType.tp_init(reinterpret_cast<PyObject*>(self), args, kwds) < 0) {
    return -1;
  }
  static char* kwlist[] = {kw_text, kw_from_file, NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|sO", kwlist,
                                   &text, &from_file_obj)) {
    return -1;
  }
  self->base.base.underlying_obj = new rapidxml::xml_document<>();
  self->base.base.document = static_cast<rapidxml::xml_document<>*>(self->base.base.underlying_obj);
  if (text && *text) {
    rapidxml_DocumentObject_parse(self, args, kwds);
  }
  return 0;
}

static PyObject* rapidxml_DocumentObject_allocate_node(rapidxml_DocumentObject* self,
                                                       PyObject* args,
                                                       PyObject* kwds) {
  const char* name = NULL;
  const char* value = NULL;
  char kw_name[] = "name";
  char kw_value[] = "value";
  rapidxml::xml_node<>* node;

  static char* kwlist[] = {kw_name, kw_value, NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ss", kwlist,
                                   &name, &value)) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  if (name) {
    name = self->base.base.document->allocate_string(name);
  }
  if (value) {
    value = self->base.base.document->allocate_string(value);
  }
  node = self->base.base.document->allocate_node(rapidxml::node_element, name, value);
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      node, &rapidxml_NodeType);
}

static PyObject* rapidxml_DocumentObject_allocate_attribute(rapidxml_DocumentObject* self,
                                                            PyObject* args,
                                                            PyObject* kwds) {
  const char* name = NULL;
  const char* value = NULL;
  char kw_name[] = "name";
  char kw_value[] = "value";
  rapidxml::xml_attribute<>* attribute;

  static char* kwlist[] = {kw_name, kw_value, NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ss", kwlist,
                                   &name, &value)) {
    Py_INCREF(Py_None);
    return Py_None;
  }
  if (name) {
    name = self->base.base.document->allocate_string(name);
  }
  if (value) {
    value = self->base.base.document->allocate_string(value);
  }
  attribute = self->base.base.document->allocate_attribute(name, value);
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      attribute, &rapidxml_AttributeType);
}

static PyMemberDef rapidxml_DocumentObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_DocumentObject_methods[] = {
  {"parse", reinterpret_cast<PyCFunction>(rapidxml_DocumentObject_parse),
   METH_VARARGS | METH_KEYWORDS, "parse given xml string, optionally from a file a from_file argument is True"},
  {"allocate_node", reinterpret_cast<PyCFunction>(rapidxml_DocumentObject_allocate_node),
   METH_VARARGS | METH_KEYWORDS, "allocates a new node from the pool, and optionally assigns name and value to it"},
  {"allocate_attribute", reinterpret_cast<PyCFunction>(rapidxml_DocumentObject_allocate_attribute),
   METH_VARARGS | METH_KEYWORDS, "allocates a new attribute from the pool, and optionally assigns name and value to it"},
  {NULL}
};

PyTypeObject rapidxml_DocumentType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "rapidxml._rapidxml.Document",   /* tp_name */
  sizeof(rapidxml_DocumentObject), /* tp_basicsize */
  0,                               /* tp_itemsize */
  reinterpret_cast<destructor>(rapidxml_DocumentObject_dealloc), /* tp_dealloc */
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
  "class representing a rapidxml::xml_document", /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  rapidxml_DocumentObject_methods, /* tp_methods */
  rapidxml_DocumentObject_members, /* tp_members */
  0,                               /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  reinterpret_cast<initproc>(rapidxml_DocumentObject_init), /* tp_init */
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
