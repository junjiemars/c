#include <Python.h>

/*
 *
 * References:
 * 1. https://docs.python.org/3/extending/extending.html
 * 2. https://setuptools.pypa.io/en/latest/userguide/quickstart.html
 *
 */

PyObject *
c_system (PyObject *self, PyObject *args)
{
  const char *command;
  int rval;
  if (!PyArg_ParseTuple (args, "s", &command))
    return NULL;
  rval = system (command);
  if (rval < 0)
    {
      return NULL;
    }
  return PyLong_FromLong (rval);
}

PyObject *
c_multiply (PyObject *self, PyObject *args)
{
  int a, b;
  if (!PyArg_ParseTuple (args, "ii", &a, &b))
    return NULL;
  return PyLong_FromLong (a * b);
}

static PyMethodDef nore_methods[] = {
  {
      .ml_name = "c_system",
      .ml_meth = c_system,
      .ml_flags = METH_VARARGS,
      .ml_doc = "c_system call system(3).",
  },
  {
      .ml_name = "c_multiply",
      .ml_meth = c_multiply,
      .ml_flags = METH_VARARGS,
      .ml_doc = "c_multiply multiply two integers.",
  },
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
  return PyModule_Create (&nore_module);
}
