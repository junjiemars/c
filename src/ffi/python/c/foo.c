#define PY_SSIZE_T_CLEAN
#include <Python.h>

/*
 *
 * References:
 * 1. https://docs.python.org/3/extending/extending.html
 * 2. https://setuptools.pypa.io/en/latest/userguide/ext_modules.html
 */

static PyObject *NoreError;

PyObject *
nore_system (PyObject *self, PyObject *args)
{
  const char *command;
  int rc;
  if (!PyArg_ParseTuple (args, "s", &command))
    return NULL;
  if ((rc = system (command)) != 0)
    {
      PyErr_SetFromErrno (NoreError);
      return NULL;
    }
  return PyLong_FromLong (rc);
}

PyObject *
nore_multiply (PyObject *self, PyObject *args)
{
  int a, b;
  if (!PyArg_ParseTuple (args, "ii", &a, &b))
    return NULL;
  return PyLong_FromLong (a * b);
}

static PyMethodDef nore_methods[] = {
  {
      .ml_name = "system",
      .ml_meth = nore_system,
      .ml_flags = METH_VARARGS,
      .ml_doc = "call system(3).",
  },
  {
      .ml_name = "multiply",
      .ml_meth = nore_multiply,
      .ml_flags = METH_VARARGS,
      .ml_doc = "multiply two integers.",
  },
  { NULL, NULL, 0, NULL },
};

static struct PyModuleDef nore_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "nore",
  .m_doc = "Illustrate extending Python in C.",
  .m_size = -1,
  .m_methods = nore_methods,
};

PyMODINIT_FUNC
PyInit_nore (void)
{
  PyObject *m;
  m = PyModule_Create (&nore_module);
  if (m == NULL)
    return NULL;
  NoreError = PyErr_NewException ("nore.error", NULL, NULL);
  if (PyModule_AddObjectRef (m, "error", NoreError) < 0)
    {
      Py_CLEAR (NoreError);
      Py_DECREF (m);
      return NULL;
    }
  PyModule_AddStringConstant (
      m, "NORE_DESC",
      "No More than a C build system for clang, gcc and msvc.");
  PyModule_AddIntConstant (m, "NORE", 1);
  return m;
}
