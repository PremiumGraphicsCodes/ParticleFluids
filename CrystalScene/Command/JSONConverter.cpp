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
        p.x = j.at("x").get<double>();       // get_to(T& arg) ‚Í arg = get<T>() ‚Æ“¯‚¶
        p.y = j.at("y").get<double>();
        p.z = j.at("z").get<double>();
    }
} // namespace ns

json JSONConverter::toJson(const std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(int)) {
        return std::any_cast<int>(value);
    }
    if (value.type() == typeid(Math::Vector3dd)) {
        return std::any_cast<Math::Vector3dd>(value);
    }
    assert(false);
    return {};
}

json JSONConverter::toJson(const IArg& v)
{
    return json{ v.name, toJson(v.value) };
}
