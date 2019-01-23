#include "FileReader.h"

#include <filesystem>

#include "../IO/OBJFileReader.h"
#include "../IO/DXFFileReader.h"
#include "../IO/STLAsciiFileReader.h"

using namespace Crystal::IO;
using namespace Crystal::UI;

bool FileReader::read(const std::experimental::filesystem::path& filePath)
{
	const auto& ext = filePath.extension();
	if (ext == ".obj") {
		OBJFileReader reader;
		if (reader.read(filePath)) {
			;
			return true;
		}
		return false;
	}
	else if (ext == ".dxf") {
		DXFFileReader reader;
		return reader.read(filePath);
	}
	else if (ext == ".stl") {
		STLAsciiFileReader reader;
		return reader.read(filePath);
	}
	return false;
}
