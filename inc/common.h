/*
** -*- coding: utf-8 -*-
**
** File: common.h
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#ifndef COMMON_H_
# define COMMON_H_

# include <rapidxml.hpp>

typedef struct {
  PyObject_HEAD
  rapidxml::xml_base<>* underlying_obj;
  rapidxml::xml_document<>* document;
} rapidxml_BaseObject;

typedef struct {
  rapidxml_BaseObject base;
} rapidxml_NodeObject;

typedef struct {
  rapidxml_BaseObject base;
} rapidxml_AttributeObject;

typedef struct {
  rapidxml_NodeObject base;
} rapidxml_RapidXmlObject;

extern PyTypeObject rapidxml_BaseType;
extern PyTypeObject rapidxml_NodeType;
extern PyTypeObject rapidxml_AttributeType;
extern PyTypeObject rapidxml_RapidXmlType;

extern PyObject* rapidxml_RapidXmlError;

int _parse_args_for_name(PyObject*, PyObject*, const char**);
PyObject* _bind_result(rapidxml_BaseObject*, rapidxml::xml_base<>*, PyTypeObject*);

#endif /* !COMMON_H_ */
