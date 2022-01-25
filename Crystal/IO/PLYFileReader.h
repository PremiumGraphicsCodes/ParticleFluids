#pragma once

#include <string>
#include <filesystem>

#include "../Math/Vector3d.h"
//#include "PCDFile.h"

namespace Crystal {
	namespace IO {

class PLYFileReader
{
public:
	bool read(std::istream& stream);

	bool read(const std::filesystem::path& filename);

	std::vector<Math::Vector3dd> getPositions() const { return positions; }

private:
	//PCDFile::Header readHeader(std::istream& stream);

	//PCDFile::Data readData(std::istream& stream);

private:
	std::vector<Math::Vector3dd> positions;
	//PCDFile pcd;
};
	}
}