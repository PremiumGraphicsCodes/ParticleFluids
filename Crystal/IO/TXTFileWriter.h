#pragma once

#include <filesystem>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

class TXTFileWriter
{
public:
	bool write(const std::filesystem::path& filePath, const std::vector<Math::Vector3dd>& positions);
};

	}
}