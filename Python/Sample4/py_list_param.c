#include <Python.h>

// C function "get list and return param"
static PyObject* c_list_param(PyObject* self, PyObject* args)
{
    int n;
    long a, sum = 0;
    PyObject* c_list, *item;

    // Decide variable type (list)
    if (!PyArg_ParseTuple(args, "O", &c_list)){
        return NULL;
    }

    // Check list
    if(PyList_Check(c_list)){
        // get length of the list
        n = PyList_Size(c_list);
    }else{
        return NULL;
    }

    // Calculate list sum
    for (int i = 0; i < n; i++){
        item = PyList_GetItem(c_list, i);
        a = PyLong_AsLong(item); // Increment the reference count
        sum = sum + a;
        Py_DECREF(item); // Decrement the reference count
    }

    Py_DECREF(c_list); // Decrement the reference count

    return Py_BuildValue("l", sum);
}

// Function Definition struct
static PyMethodDef listpMethods[] = {
    { "sum_list", c_list_param, METH_VARARGS, "Calculate list sum"},
    { NULL }
};

// Module Definition struct
static struct PyModuleDef listpModule = {
    PyModuleDef_HEAD_INIT,
    "listpModule",
    "Python3 C API Module(Sample 4)",
    -1,
    listpMethods
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_listpModule(void)
{
    return PyModule_Create(&listpModule);
}