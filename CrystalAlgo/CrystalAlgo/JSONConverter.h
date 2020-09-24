#pragma once

#include "../ThirdParty/nlohmann/include/json.hpp"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Math/Box3d.h"
#include <any>

namespace Crystal {
	namespace Algo {

class JSONConverter
{
public:
	static nlohmann::json toJSON(const std::string& name, const int value);

	static nlohmann::json toJSON(const std::string& name, const float value);

	static nlohmann::json toJSON(const std::string& name, const double value);

	static nlohmann::json toJSON(const std::string& name, const std::string& value);

	static nlohmann::json toJSON(const std::string& name, const Math::Vector3df& value);

	static nlohmann::json toJSON(const std::string& name, const Math::Vector3dd& value);

	static nlohmann::json toJSON(const std::string& name, const Math::Box3d& value);

	static void fromJSON(const std::string& name, int& value);

	static void fromJSON(const std::string& name, float& value);

	static void fromJSON(const std::string& name, double& value);

	static void fromJSON(const std::string& name, std::string& value);

	static void fromJSON(const std::string& name, Math::Vector3df& value);

	static void fromJSON(const std::string& name, Math::Vector3dd& value);

	static void fromJSON(const std::string& name, Math::Box3d& value);
};

	}
}