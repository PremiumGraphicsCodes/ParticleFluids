// TestPy.cpp : スタティック ライブラリ用の関数を定義します。
//

#include "pch.h"
#include "framework.h"

// TODO: これは、ライブラリ関数の例です
#include <Python.h>

static PyObject* c_helloworld(PyObject* self, PyObject* args)
{
    printf("Hello World\n");
    return Py_None;
}