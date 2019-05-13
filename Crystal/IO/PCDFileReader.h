#pragma once

#include <string>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

class PCDFileReader
{
public:
	bool read(std::istream& stream);

	bool read(const std::string& filename);

private:
	bool parseHeader(std::istream& stream);

	bool parseData(std::istream& stream);

private:
	std::string version;
	std::vector<Math::Vector3dd> positions;
};
	}
}