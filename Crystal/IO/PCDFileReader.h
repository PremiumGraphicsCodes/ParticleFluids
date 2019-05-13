#pragma once

#include <string>
#include <filesystem>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

class PCDFileReader
{
public:
	bool read(std::istream& stream);

	bool read(const std::experimental::filesystem::path& filename);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	bool parseHeader(std::istream& stream);

	bool parseData(std::istream& stream);

private:
	std::string version;
	std::vector<Math::Vector3dd> positions;
};
	}
}