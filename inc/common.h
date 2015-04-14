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
# include <vector>

typedef struct {
  PyObject_HEAD
  rapidxml::xml_base<>* underlying_obj;
} rapidxml_BaseObject;

typedef struct {
  rapidxml_BaseObject base;
  std::vector<char> text;
} rapidxml_RapidXmlObject;

extern PyTypeObject rapidxml_BaseType;
extern PyTypeObject rapidxml_RapidXmlType;

extern PyObject* RapidXmlError;

#endif /* !COMMON_H_ */
