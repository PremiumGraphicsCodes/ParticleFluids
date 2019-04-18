#include "FileWriter.h"

#include <filesystem>

#include "../IO/STLASCIIFileWriter.h"

using namespace Crystal::IO;
using namespace Crystal::Model;
using namespace Crystal::UI;

bool FileWriter::write(const std::experimental::filesystem::path& filePath, const ObjectRepository& objects)
{
	const auto& ext = filePath.extension();
	if (ext == ".obj") {
		return false;
	}
	else if (ext == ".dxf") {
		return false;
	}
	else if (ext == ".stl") {
		return false;
		//STLASCIIFileWriter writer(;
		//return writer.write(filePath);
	}
	return false;
}
