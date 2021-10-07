#include "JSONConverter.h"

#include "../ThirdParty/nlohmnn/json.hpp"

#include "Crystal/Math/Vector3d.h"

using namespace Crystal;
using namespace Crystal::Command;
using namespace nlohmann;

namespace glm{
    void to_json(json& j, const Math::Vector3dd& p) {
        j = json{ {"x", p.x}, {"y", p.y}, {"z", p.z} };
    }

    template<typename T>
    void from_json(const json& j, Math::Vector3d<T>& p) {
        p.x = j.at("x").get<double>();       // get_to(T& arg) �� arg = get<T>() �Ɠ���
        p.y = j.at("y").get<double>();
        p.z = j.at("z").get<double>();
    }
} // namespace ns

json JSONConverter::toJSON(const std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(int)) {
        return std::any_cast<int>(value);
    }
    if (type == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    if (type == typeid(std::vector<int>)) {
        return std::any_cast<std::vector<int>>(value);
    }
    if (value.type() == typeid(Math::Vector3dd)) {
        return std::any_cast<Math::Vector3dd>(value);
    }
    assert(false);
    return {};
}

json JSONConverter::toJSON(const IArgs& args)
{
    json j;
    for (auto a : args.args) {
        j[a->name] = toJSON(a->value);
    }
    return j;
}

json JSONConverter::toJSON(const ICommand& command)
{
    json j;
    j["name"] = command.getCommandName();
    j["args"] = toJSON(*command.getArgs());
    return j;
}

void JSONConverter::fromJSON(const nlohmann::json& json, std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(int)) {
        const int v = json;
        value = v;
    }
    else if (type == typeid(std::string)) {
        const std::string v = json;
        value = v;
    }
    else if (type == typeid(std::vector<int>)) {
        std::vector<int> v = json;
        value = v;
    }
    else if (type == typeid(Math::Vector3dd)) {
        const Math::Vector3dd v = json;
        value = v;
    }
}

void JSONConverter::fromJSON(const nlohmann::json& json, Arg<int>& dest)
{
    fromJSON(json, dest.value);
}

void JSONConverter::fromJSON(const nlohmann::json& json, ICommand& command)
{
    auto args = command.getArgs();
    const auto jj = json["args"];
    for (auto a : args->args) {
        auto j = jj[a->name];
        /*
        auto& type = a->value.type();
        if (type == typeid(int)) {
            return;
        }
        */
//        command.getArgType(a->name);
        fromJSON(j, a->value);
    }
}


//JSONConverter::