#pragma once

#include "../ThirdParty/nlohmann/include/json.hpp"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include <any>

namespace Crystal {
	namespace FS {

class JSONConverter
{
public:
	static nlohmann::json toJSON(const int value);

	static nlohmann::json toJSON(const float value);

	static nlohmann::json toJSON(const double value);

	template<typename T>
	static nlohmann::json toJSON(const T& value);

	static nlohmann::json toJSON(const std::any& a);

	template<typename T>
	static T fromJSON(const nlohmann::json& j, const std::string& name);

	/*
	static void fromJSON(const nlohmann::json& j, const std::string& name);

	static void fromJSON(const std::string& name, double& value);

	static void fromJSON(const std::string& name, std::string& value);

	static void fromJSON(const std::string& name, Math::Vector3df& value);

	static void fromJSON(const std::string& name, Math::Vector3dd& value);

	static void fromJSON(const std::string& name, Math::Box3d& value);
	*/
};

	}
}