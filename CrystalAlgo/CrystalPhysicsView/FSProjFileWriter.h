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
	nlohmann::json toJSON(const std::string& name, const int value);

	nlohmann::json toJSON(const std::string& name, const float value);

	nlohmann::json toJSON(const std::string& name, const double value);

	nlohmann::json toJSON(const std::string& name, const std::string& value);

	nlohmann::json toJSON(const std::string& name, const Math::Vector3dd& value);

	nlohmann::json toJSON(const std::string& name, const Math::Box3d& value);

	void fromJSON(const std::string& name, int& value);

	void fromJSON(const std::string& name, float& value);

	void fromJSON(const std::string& name, double& value);
};

class FSProjFileWriter
{
};
	}
}