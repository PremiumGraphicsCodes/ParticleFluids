#pragma once

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct PCDFile
{
	struct Header
	{

	};
	struct Data
	{
		std::vector<Math::Vector3dd> positions;
	};
	Header header;
	Data data;
};

	}
}