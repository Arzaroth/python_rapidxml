/*
** -*- coding: utf-8 -*-
**
** File: node_object.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <structmember.h>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <string>

#include <common.h>

static int rapidxml_NodeObject_init(rapidxml_NodeObject* self,
                                    PyObject* args,
                                    PyObject* kwds) {
  return rapidxml_BaseType.tp_init(reinterpret_cast<PyObject*>(self), args, kwds);
}

static PyObject* rapidxml_NodeObject_first_node(rapidxml_NodeObject* self,
                                                PyObject* args,
                                                PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_node<>* node;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  node = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->first_node(name);
  if (node == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      node, &rapidxml_NodeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_last_node(rapidxml_NodeObject* self,
                                               PyObject* args,
                                               PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_node<>* node;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  node = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->last_node(name);
  if (node == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      node, &rapidxml_NodeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_previous_sibling(rapidxml_NodeObject* self,
                                                      PyObject* args,
                                                      PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_node<>* node;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  node = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->previous_sibling(name);
  if (node == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      node, &rapidxml_NodeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_next_sibling(rapidxml_NodeObject* self,
                                                  PyObject* args,
                                                  PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_node<>* node;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  node = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->next_sibling(name);
  if (node == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      node, &rapidxml_NodeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_first_attribute(rapidxml_NodeObject* self,
                                                     PyObject* args,
                                                     PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_attribute<>* attribute;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  attribute = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->first_attribute(name);
  if (attribute == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      attribute, &rapidxml_AttributeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_last_attribute(rapidxml_NodeObject* self,
                                                     PyObject* args,
                                                     PyObject* kwds) {
  const char* name = NULL;
  rapidxml::xml_attribute<>* attribute;

  if (!_parse_args_for_name(args, kwds, &name)) {
    goto err;
  }
  attribute = static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)->last_attribute(name);
  if (attribute == NULL) {
    goto err;
  }
  return _bind_result(reinterpret_cast<rapidxml_BaseObject*>(self),
                      attribute, &rapidxml_AttributeType);
 err:
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject_unparse(rapidxml_NodeObject* self,
                                             PyObject* args,
                                             PyObject* kwds) {
  int pretty = 0;
  PyObject* pretty_obj = NULL;
  std::string xml;
  char kw_pretty[] = "pretty";

  static char* kwlist[] = {kw_pretty, NULL};
  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, &pretty_obj)) {
    pretty = 0;
  } else if (pretty_obj) {
    pretty = PyObject_IsTrue(pretty_obj);
  }
  rapidxml::print(std::back_inserter(xml),
                  *(static_cast<rapidxml::xml_node<>*>(self->base.underlying_obj)),
                  !pretty ? rapidxml::print_no_indenting : 0);
  return Py_BuildValue("s", xml.c_str());
}

static PyObject* rapidxml_NodeObject_prepend_node(rapidxml_NodeObject* self,
                                                  PyObject* args,
                                                  PyObject* kwds) {
  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* rapidxml_NodeObject___str__(rapidxml_NodeObject* self) {
  PyObject* args;
  PyObject* res;

  args = Py_BuildValue("(O)", Py_True);
  res = rapidxml_NodeObject_unparse(self, args, NULL);
  Py_DECREF(args);
  return res;
}

static PyObject* rapidxml_NodeObject___repr__(rapidxml_NodeObject* self) {
  PyObject* args;
  PyObject* res;

  args = Py_BuildValue("(O)", Py_False);
  res = rapidxml_NodeObject_unparse(self, args, NULL);
  Py_DECREF(args);
  return res;
}

static PyObject* rapidxml_NodeObject_children(rapidxml_NodeObject* self,
                                              void* closure) {
  rapidxml_NodeIteratorObject* iterator;
  PyObject* args;

  args = Py_BuildValue("(O)", self);
  iterator = reinterpret_cast<rapidxml_NodeIteratorObject*>
    (PyObject_CallObject(reinterpret_cast<PyObject*>(&rapidxml_NodeIteratorType),
                         args));
  Py_DECREF(args);
  return reinterpret_cast<PyObject*>(iterator);
}

static PyObject* rapidxml_NodeObject_attributes(rapidxml_NodeObject* self,
                                                void* closure) {
  rapidxml_AttributeIteratorObject* iterator;
  PyObject* args;

  args = Py_BuildValue("(O)", self);
  iterator = reinterpret_cast<rapidxml_AttributeIteratorObject*>
    (PyObject_CallObject(reinterpret_cast<PyObject*>(&rapidxml_AttributeIteratorType),
                         args));
  Py_DECREF(args);
  return reinterpret_cast<PyObject*>(iterator);
}

static PyGetSetDef rapidxml_NodeObject_getseters[] = {
  {"children",
   (getter)rapidxml_NodeObject_children, NULL,
   "return an NodeIteratorObject to iterate over a node's children"},
  {"attributes",
   (getter)rapidxml_NodeObject_attributes, NULL,
   "return an AttributeIteratorObject to iterate over a node's attributes"},
  {NULL}
};

static PyMemberDef rapidxml_NodeObject_members[] = {
  {NULL}
};

static PyMethodDef rapidxml_NodeObject_methods[] = {
  {"first_node", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_first_node),
   METH_VARARGS | METH_KEYWORDS, "gets first child node, optionally matching node name"},
  {"last_node", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_last_node),
   METH_VARARGS | METH_KEYWORDS, "gets last child node, optionally matching node name"},
  {"previous_sibling", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_previous_sibling),
   METH_VARARGS | METH_KEYWORDS, "gets previous sibling node, optionally matching node name"},
  {"next_sibling", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_next_sibling),
   METH_VARARGS | METH_KEYWORDS, "gets next sibling node, optionally matching node name"},
  {"first_attribute", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_first_attribute),
   METH_VARARGS | METH_KEYWORDS, "gets first attribute of node, optionally matching node name"},
  {"last_attribute", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_last_attribute),
   METH_VARARGS | METH_KEYWORDS, "gets last attribute of node, optionally matching node name"},
  {"unparse", reinterpret_cast<PyCFunction>(rapidxml_NodeObject_unparse),
   METH_VARARGS | METH_KEYWORDS, "return xml string"},
  {NULL}
};

PyTypeObject rapidxml_NodeType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "rapidxml.Node",                 /* tp_name */
  sizeof(rapidxml_NodeObject),     /* tp_basicsize */
  0,                               /* tp_itemsize */
  0,                               /* tp_dealloc */
  0,                               /* tp_print */
  0,                               /* tp_getattr */
  0,                               /* tp_setattr */
  0,                               /* tp_reserved */
  reinterpret_cast<reprfunc>(rapidxml_NodeObject___repr__), /* tp_repr */
  0,                               /* tp_as_number */
  0,                               /* tp_as_sequence */
  0,                               /* tp_as_mapping */
  0,                               /* tp_hash  */
  0,                               /* tp_call */
  reinterpret_cast<reprfunc>(rapidxml_NodeObject___str__), /* tp_repr */
  0,                               /* tp_getattro */
  0,                               /* tp_setattro */
  0,                               /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
  "class representing a rapidxml::xml_node", /* tp_doc */
  0,                               /* tp_traverse */
  0,                               /* tp_clear */
  0,                               /* tp_richcompare */
  0,                               /* tp_weaklistoffset */
  0,                               /* tp_iter */
  0,                               /* tp_iternext */
  rapidxml_NodeObject_methods,     /* tp_methods */
  rapidxml_NodeObject_members,     /* tp_members */
  rapidxml_NodeObject_getseters,   /* tp_getset */
  0,                               /* tp_base */
  0,                               /* tp_dict */
  0,                               /* tp_descr_get */
  0,                               /* tp_descr_set */
  0,                               /* tp_dictoffset */
  reinterpret_cast<initproc>(rapidxml_NodeObject_init), /* tp_init */
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
