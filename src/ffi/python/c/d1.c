#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *NoreError;

int
main (void)
{
  NoreError = PyErr_NewException ("nore.error", NULL, NULL);

  return 0;
}
