/*
** -*- coding: utf-8 -*-
**
** File: common.h
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#ifndef         COMMON_H_
# define        COMMON_H_

# define        STR(x) #x
# define        STRINGIFY(x) STR(x)
# define        CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
# define        PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

# define        MODULE_DESC "rapidxml module for rapidxml bindings"
# define        MODULE_NAME rapidxml
# define        MODULE_METHS CAT(MODULE_NAME, _methods)

# define        OBJECT_NAME RapidXml
# define        OBJ_TYPE CAT(MODULE_NAME, CAT(_, CAT(OBJECT_NAME, Type)))
# define        OBJ_OBJECT CAT(MODULE_NAME, CAT(_, CAT(OBJECT_NAME, Object)))
# define        OBJ_METHS CAT(OBJECT_NAME, _methods)
# define        OBJ_MEMBERS CAT(OBJECT_NAME, _members)

# define        EXCEPT_NAME CAT(OBJECT_NAME, Error)

extern PyTypeObject OBJ_TYPE;
extern PyObject* EXCEPT_NAME;

#endif          /* !COMMON_H_ */
