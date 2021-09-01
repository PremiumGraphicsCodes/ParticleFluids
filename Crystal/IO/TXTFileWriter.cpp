#include "TXTFileWriter.h"

#include <fstream>

using namespace Crystal::IO;

bool TXTFileWriter::write(const std::filesystem::path& filePath, const std::vector<Math::Vector3dd>& positions)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}

	for(const auto& p : positions) {
		stream << p.x << " " << p.y << " " << p.z << std::endl;
	}

	stream.close();
}