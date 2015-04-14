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
  rapidxml::memory_pool<> memory_pool;
} rapidxml_BaseObject;

typedef struct {
  rapidxml_BaseObject base;
} rapidxml_NodeObject;

typedef struct {
  rapidxml_NodeObject base;
} rapidxml_RapidXmlObject;

extern PyTypeObject rapidxml_BaseType;
extern PyTypeObject rapidxml_NodeType;
extern PyTypeObject rapidxml_RapidXmlType;

extern PyObject* RapidXmlError;

#endif /* !COMMON_H_ */
