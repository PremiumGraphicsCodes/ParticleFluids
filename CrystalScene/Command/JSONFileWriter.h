#pragma once

#include <any>

#include "Crystal/Math/Vector3d.h"

#include "../ThirdParty/nlohmnn/json.hpp"

namespace Crystal {
	namespace Command {

class JSONFileWriter
{
public:
	//void write(const std::any& value);

	nlohmann::json to_json(const Math::Vector3dd& v);

	//nlohmann::json write(const Math::)

private:
	//std::string toJsonText();
};
	}
}