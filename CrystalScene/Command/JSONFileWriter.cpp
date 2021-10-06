#include "JSONFileWriter.h"

#include "../ThirdParty/nlohmnn/json.hpp"

#include "Crystal/Math/Vector3d.h"

using namespace Crystal;
using namespace Crystal::Command;
using namespace nlohmann;

/*
namespace Crystal {
    namespace Math {
        template<typename T>
        void to_json(json& j, const Math::Vector3d<T>& p) {
            j = json{ {"x", p.x}, {"y", p.y}, {"z", p.z} };
        }

        template<typename T>
        void from_json(const json& j, Math::Vector3d<T>& p) {
            p.x = j.at("x").get<double>();       // get_to(T& arg) ‚Í arg = get<T>() ‚Æ“¯‚¶
            p.y = j.at("y").get<double>();
            p.z = j.at("z").get<double>();
        }
    }
} // namespace ns
*/
/*
void JSONFileWriter::write(const std::any& value)
{
    if (value.type() == typeid(Math::Vector3dd)) {
        
    }
}
*/

json JSONFileWriter::to_json(const Math::Vector3dd& v)
{
    return json{ {"x", v.x}, {"y", v.y}, {"z", v.z} };
}
