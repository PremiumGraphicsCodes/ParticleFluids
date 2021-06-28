#include <Python.h>

// C function "get list and Multiply 2 and item of list"
static PyObject* c_multiply_list(PyObject* c_list, int n)
{
    long a;
    PyObject* result_list, *item;

    // make python list	(length n)
    result_list = PyList_New(n);

    for (int i = 0; i < n; i++){
        item = PyList_GetItem(c_list, i);
        a = PyLong_AsLong(item);    // PyObject -> long
        a = 2 * a;
        item = Py_BuildValue("l", a);  // long -> PyObject
        PyList_SET_ITEM(result_list, i, item);
        Py_DECREF(item);
    }

    Py_DECREF(c_list);

    return result_list;
}

// C function "get list and return list"
static PyObject* py_list(PyObject* self, PyObject* args)
{
    int n;
    PyObject* c_list;

    // decide type (list)
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

    return c_multiply_list(c_list, n);
}

// Function Definition struct
static PyMethodDef MultiplyList[] = {
    { "c_multiply_list", py_list, METH_VARARGS, "Multiply 2 and item of list "},
    { NULL }
};

// Module Definition struct
static struct PyModuleDef multiplyList = {
    PyModuleDef_HEAD_INIT,
    "multiplyList",
    "Python3 C API Module(Sample 5)",
    -1,
    MultiplyList
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_multiplyList(void)
{
    return PyModule_Create(&multiplyList);
}