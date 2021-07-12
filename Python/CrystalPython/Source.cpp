//References:
//http://pybind11.readthedocs.io/en/stable/classes.html
//https://qiita.com/ignis_fatuus/items/c7523c0fe2bc2f415d50
//https://qiita.com/exy81/items/e309df7e33d4ff20a91a#_reference-c8a52580111447fade09
//http://pybind11.readthedocs.io/en/stable/advanced/classes.html#operator-overloading
//http://pybind11.readthedocs.io/en/stable/classes.html#overloaded-methods

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // vector—p
#include <pybind11/operators.h>//operator
#include "Header.h"


using namespace::std;

int add(int x, int y) {
    return x + y;
}

namespace py = pybind11;
PYBIND11_MODULE(CrystalPython, m) {
    m.doc() = "pybind11 example plugin";
    m.def("add", &add);
    py::class_<POINT>(m, "POINT")
        .def(py::init<int, int>())
        .def(py::init<pair<int, int>>())
        .def_readwrite("sum", &POINT::sum)
        .def_property_readonly("x", &POINT::X)
        .def_property_readonly("y", &POINT::Y)
        .def(py::self + py::self)
        .def("__repr__", &POINT::toString);
}