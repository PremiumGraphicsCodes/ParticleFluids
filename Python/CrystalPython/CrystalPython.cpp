//References:
//http://pybind11.readthedocs.io/en/stable/classes.html
//https://qiita.com/ignis_fatuus/items/c7523c0fe2bc2f415d50
//https://qiita.com/exy81/items/e309df7e33d4ff20a91a#_reference-c8a52580111447fade09
//http://pybind11.readthedocs.io/en/stable/advanced/classes.html#operator-overloading
//http://pybind11.readthedocs.io/en/stable/classes.html#overloaded-methods

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // vector�p
#include <pybind11/operators.h>//operator
#include "CrystalPython.h"
#include "../../Crystal/Math/Vector3d.h"

#include "../../Crystal/Scene/World.h"
#include "../../CrystalViewer/Command/CommandFactory.h"
#include "../../CrystalSpace/CrystalSpaceCommand/SpaceCommandFactory.h"
#include "../../CrystalPhysics/CrystalPhysicsCommand/PhysicsCommandFactory.h"
#include "../../CrystalVDB/VDBCommand/VDBCommandFactory.h"

using namespace::std;
using namespace Crystal::Math;

class Vector3dfVector
{
public:
    std::vector<Vector3df> values;

    void add(Vector3df v) { this->values.push_back(v); }

    //    Vector3dd get(const int index) { return this->values[i]; }
};

class Vector3ddVector
{
public:
    std::vector<Vector3dd> values;

    void add(Vector3dd v) { this->values.push_back(v); }

//    Vector3dd get(const int index) { return this->values[i]; }
};

namespace {
    Crystal::Command::CommandFactory sceneCommandFactory;
    Crystal::Space::SpaceCommandFactory spaceCommandFactory;
    Crystal::Physics::PhysicsCommandFactory physicsCommandFactory;
    Crystal::VDB::VDBCommandFactory vdbCommandFactory;
    std::unique_ptr<Crystal::Command::ICommand> command;

    void createSceneCommand(const std::string& commandName) {
        command = sceneCommandFactory.createCommand(commandName);
    }

    void createSpaceCommand(const std::string& commandName) {
        command = spaceCommandFactory.create(commandName);
    }

    void createPhysicsCommand(const std::string& commandName) {
        command = physicsCommandFactory.create(commandName);
//        command->execute(&world);
    }

    void createVDBCommand(const std::string& commandName) {
        command = vdbCommandFactory.createCommand(commandName);
    }

    template<typename T>
    void setArg(const std::string& name, T value) {
        command->setArg(name, value);
    }

    void setArgVector3dfVector(const std::string& name, const Vector3dfVector& vv) {
        command->setArg(name, vv.values);
    }

    void setArgVector3ddVector(const std::string& name, const Vector3ddVector& vv) {
        command->setArg(name, vv.values);
    }

    /*
    template<typename T>
    void setArg<T>(const std::string& name, const T& value)
    {

    }
    */

    bool executeCommand(Crystal::Scene::World& world) {
        return command->execute(&world);
    }
    /*
    void setArg(const std::string& name, const std::string& value) {
        command->setArg(name, value);
    }
    */
    template<typename T>
    T getResult(const std::string& name)
    {
        return std::any_cast<T>( command->getResult(name));
    }

    std::vector<int> getResultIntVector(const std::string& name)
    {
        return std::any_cast<std::vector<int>>(command->getResult(name));
    }
}


int add(int x, int y);

class POINT {
private:
    int x;
    int y;
public:
    int sum;
    POINT(pair<int, int> xy) { this->x = xy.first; this->y = xy.second; this->sum = this->x + this->y; }
    POINT(int x, int y) { this->x = x; this->y = y; this->sum = x + y; }
    int X() { return x; }
    int Y() { return y; }
    POINT operator+(const POINT& v) const { return POINT(this->x + v.x, this->y + v.y); }
    std::string toString() const {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }
};

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

    py::class_<Crystal::Scene::World>(m, "World")
        .def(py::init());

    py::class_<Vector3df>(m, "Vector3df")
        .def(py::init<float, float, float>())
        .def_readwrite("x", &Vector3df::x)
        .def_readwrite("y", &Vector3df::y)
        .def_readwrite("z", &Vector3df::z);

    py::class_<Vector3dd>(m, "Vector3dd")
        .def(py::init<double, double, double>())
        .def_readwrite("x", &Vector3dd::x)
        .def_readwrite("y", &Vector3dd::y)
        .def_readwrite("z", &Vector3dd::z);

    py::class_<Box3df>(m, "Box3df")
        .def(py::init<Vector3df, Vector3df>())
        .def_property_readonly("min", &Box3df::getMin)
        .def_property_readonly("max", &Box3df::getMax);

    py::class_<Vector3dfVector>(m, "Vector3dfVector")
        .def(py::init<>())
        .def("add", &Vector3dfVector::add)
        .def_readwrite("values", &Vector3dfVector::values);

    py::class_<Vector3ddVector>(m, "Vector3ddVector")
        .def(py::init<>())
        .def("add", &Vector3ddVector::add)
        .def_readwrite("values", &Vector3ddVector::values);
    //    .def_readwrite("add", &std::vector<Vector3df>::push_back);

    m.def("create_scene_command", &createSceneCommand);
    m.def("create_physics_command", &createPhysicsCommand);
    m.def("create_vdb_command", &createVDBCommand);
    m.def("execute_command", &executeCommand);
    m.def("set_arg_bool", &setArg<bool>);
    m.def("set_arg_int", &setArg<int>);
    m.def("set_arg_int_vector", &setArg<std::vector<int>>);
    m.def("set_arg_float", &setArg<float>);
    m.def("set_arg_double", &setArg<double>);
    m.def("set_arg_string", &setArg<std::string>);
    m.def("set_arg_vector3df", &setArg<Vector3df>);
    m.def("set_arg_vector3dd", &setArg<Vector3dd>);
    m.def("set_arg_box3df", &setArg<Box3df>);
    m.def("set_arg_vector3df_vector", &setArgVector3dfVector);
    m.def("set_arg_vector3dd_vector", &setArgVector3ddVector);
    m.def("get_result_int", &getResult<int>);
    m.def("get_result_int_vector", &getResultIntVector);
    //py::class_<Crystal::Physics::PhysicsCommandFactory>(m, "PhysicsCommandFactory")
    //    .def("create", &Crystal::Physics::PhysicsCommandFactory::create);

    //m.def("call", &call);
}