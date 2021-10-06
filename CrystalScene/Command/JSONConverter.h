#pragma once

#include <any>

#include "Crystal/Math/Vector3d.h"
#include "IArgs.h"

#include "../ThirdParty/nlohmnn/json.hpp"

namespace Crystal {
	namespace Command {

class JSONConverter
{
public:
	static nlohmann::json toJson(const std::any& value);

	static nlohmann::json toJson(const IArg& v);

	//nlohmann::json write(const Math::)

private:
	//std::string toJsonText();
};
	}
}