/*
** -*- coding: utf-8 -*-
**
** File: rapidxml.cpp
** by Arzaroth Lekva
** arzaroth@arzaroth.com
**
*/

#include <Python.h>
#include <rapidxml.hpp>

struct module_state {
  PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
# define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
# define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyMethodDef module_funcs[] = {
  {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3

static int module_traverse(PyObject* m, visitproc visit, void* arg) {
  Py_VISIT(GETSTATE(m)->error);
  return 0;
}

static int module_clear(PyObject* m) {
  Py_CLEAR(GETSTATE(m)->error);
  return 0;
}

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "rapidxml",
  NULL,
  sizeof(struct module_state),
  module_funcs,
  NULL,
  module_traverse,
  module_clear,
  NULL
};

# define INITERROR return NULL

PyMODINIT_FUNC PyInit_rapidxml(void)

#else
# define INITERROR return

PyMODINIT_FUNC initrapidxml(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
  PyObject* module = PyModule_Create(&moduledef);
#else
  PyObject* module = Py_InitModule("rapidxml", module_funcs);
#endif

  if (module == NULL)
    INITERROR;
  struct module_state* st = GETSTATE(module);

  st->error = PyErr_NewException("rapidxml.Error", NULL, NULL);
  if (st->error == NULL) {
    Py_DECREF(module);
    INITERROR;
  }

#if PY_MAJOR_VERSION >= 3
  return module;
#endif
}
