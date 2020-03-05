#include "STLFileReader.h"

#include <fstream>

using namespace Crystal::IO;

namespace {
	size_t getStreamSize(std::istream& stream)
	{
		stream.seekg(0, std::ios::end);
		std::fstream::pos_type pos_end = stream.tellg();

		stream.seekg(0, std::ios::beg);
		std::fstream::pos_type pos_beg = stream.tellg();

		return pos_end - pos_beg;
	}
}

bool STLFileReader::isBinary(std::istream& in)
{
	size_t fileSize = getStreamSize(in);

	char head[80];
	in.read(head, 80);

	unsigned int NumFaces;
	in.read((char*)&NumFaces, sizeof(unsigned int));

	const size_t expectedBinaryFileSize = NumFaces * 50 + 84;
	in.seekg(0, std::ios::beg);

	if (expectedBinaryFileSize != fileSize)
		return false;

	return true;
}