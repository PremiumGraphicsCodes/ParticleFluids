#include "JSONConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Algo;

using json = nlohmann::json;

namespace glm {
//	namespace Math {
//		to_json
		void to_json(json& j, const Vector3df& p) {
			j = json{ p.x, p.y, p.z };
		}

		/*
		void from_json(const json& j, person& p) {
			j.at("name").get_to(p.name);       // get_to(T& arg) ‚Í arg = get<T>() ‚Æ“¯‚¶
			j.at("address").get_to(p.address);
			j.at("age").get_to(p.age);
		}
		*/

		void to_json(json& j, const Vector3dd& p) {
			j = json{ p.x, p.y, p.z };
		}


//	}
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const int value)
{
	return { name, value };
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const float value)
{
	return { name, value };
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const double value)
{
	return { name, value };
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const std::string& value)
{
	return { name,value };
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const Vector3df& value)
{
	return { name, value };
}

nlohmann::json JSONConverter::toJSON(const std::string& name, const Vector3dd& value)
{
	return { name, value };
}
/*
nlohmann::json toJSON(const std::string& name, const Math::Box3d& value);

void fromJSON(const std::string& name, int& value);

void fromJSON(const std::string& name, float& value);

void fromJSON(const std::string& name, double& value);

void fromJSON(const std::string& name, std::string& value);

void fromJSON(const std::string& name, Math::Vector3dd& value);

void fromJSON(const std::string& name, Math::Box3d& value);
*/