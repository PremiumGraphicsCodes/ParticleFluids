// #include "Python.h"
#include "Python.h"

// Pure C/C++ function 'c_add'
int c_add(int a, int b)
{
    return a + b;
}

// Wrapped C/C++ function 'pyadd'
static PyObject* pyadd(PyObject* self, PyObject* args)
{
    int a, b, c;

    // Decide variable type (int, int)
    if (!PyArg_ParseTuple(args, "ii", &a, &b)){
        return NULL;
    }

    c = c_add(a, b);

    // return c_add computed add number
    return Py_BuildValue("i", c);
}

// addModule definition(python's name)
static PyMethodDef addMethods[] = {
    { "c_add", pyadd, METH_VARARGS},
    { NULL }
};

// addModule definition struct
static struct PyModuleDef addModule = {
    PyModuleDef_HEAD_INIT,
    "addModule",
    "Python3 C API Module(Sample 2)",
    -1,
    addMethods
};

// Initializes addModule
PyMODINIT_FUNC PyInit_addModule(void)
{
    return PyModule_Create(&addModule);
}