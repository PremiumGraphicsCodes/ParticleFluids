#include "OBJFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool OBJFileWriter::write(const std::experimental::filesystem::path& filename, const OBJFile& obj)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, obj);
}

bool OBJFileWriter::write(std::ostream& stream, const OBJFile& obj)
{
	return false;
}
