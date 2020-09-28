#include "JSONConverter.h"

using namespace Crystal::Math;
using namespace Crystal::FS;

using json = nlohmann::json;

namespace glm {
	void to_json(json& j, const Vector3df& p) {
		j = json{ p.x, p.y, p.z };
	}

	void from_json(const json& j, Vector3df& v) {
		j[0].get_to(v[0]);
		j[1].get_to(v[1]);
		j[2].get_to(v[2]);
	}

	void to_json(json& j, const Vector3dd& p) {
		j = json{ p.x, p.y, p.z };
	}

	void from_json(const json& j, Vector3dd& v) {
		j[0].get_to(v[0]);
		j[1].get_to(v[1]);
		j[2].get_to(v[2]);
	}
}

namespace Crystal {
	namespace Math {
		void to_json(json& j, const Box3d& b) {
			j = json{
				{"min", b.getMin()},
				{"max", b.getMax()}
			};
		}

		void from_json(const json& j, Box3d& v) {
			Vector3dd min = j.at("min");
			Vector3dd max = j.at("max");
			v = Box3d(min, max);
		}

	}
}

nlohmann::json JSONConverter::toJSON(const int value)
{
	return value;
}

nlohmann::json JSONConverter::toJSON(const float value)
{
	return value;
}

nlohmann::json JSONConverter::toJSON(const double value)
{
	return value;
}

template<>
nlohmann::json JSONConverter::toJSON<std::string>(const std::string& value)
{
	return value;
}

template<>
nlohmann::json JSONConverter::toJSON<Vector3df>(const Vector3df& value)
{
	return value;
}

template<>
nlohmann::json JSONConverter::toJSON<Vector3dd>(const Vector3dd& value)
{
	return value;
}

template<>
nlohmann::json JSONConverter::toJSON<Box3d>(const Box3d& value)
{
	return value;
}

nlohmann::json JSONConverter::toJSON(const std::any& a)
{
	const auto& t = a.type();
	if (t == typeid(int)) {
		return std::any_cast<int>(a);
	}
	else if (t == typeid(float)) {
		return std::any_cast<float>(a);
	}
	else if (t == typeid(double)) {
		return std::any_cast<double>(a);
	}
	else if (t == typeid(std::string)) {
		return std::any_cast<std::string>(a);
	}
	else {
		assert(false);
	}
	return nlohmann::json();
}


template<>
int JSONConverter::fromJSON<int>(const nlohmann::json& j)
{
	return j.get<int>();
}

template<>
float JSONConverter::fromJSON<float>(const nlohmann::json& j)
{
	return j.get<float>();
}

template<>
double JSONConverter::fromJSON<double>(const nlohmann::json& j)
{
	return j.get<double>();
}

template<>
std::string JSONConverter::fromJSON<std::string>(const nlohmann::json& j)
{
	return j.get<std::string>();
}

template<>
Vector3df JSONConverter::fromJSON<Vector3df>(const nlohmann::json& j)
{
	return j.get<Vector3df>();
}

template<>
Vector3dd JSONConverter::fromJSON<Vector3dd>(const nlohmann::json& j)
{
	return j.get<Vector3dd>();
}

template<>
Box3d JSONConverter::fromJSON<Box3d>(const nlohmann::json& j)
{
	return j.get<Box3d>();
}

/*
void fromJSON(const std::string& name, std::string& value);

void fromJSON(const std::string& name, Math::Box3d& value);
*/