#include "PLYFileWriter.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

bool PLYFileWriter::writeASCII(const std::filesystem::path& filename, const PLYFile& pcd)
{
	std::ofstream stream(filename);
	if (!stream.is_open()) {
		return false;
	}
	return writeASCII(stream, pcd);
}

bool PLYFileWriter::writeASCII(std::ostream& stream, const PLYFile& pcd)
{
	stream << "ply" << std::endl;
	stream << "format ascii 1.0" << std::endl;
	stream << "comment " << std::endl;
	stream << "comment " << std::endl;
	stream << "obj_info " << std::endl;
	stream << "element vertex " << pcd.vertices.size() << std::endl;
	stream << "property float x " << std::endl;
	stream << "property float y " << std::endl;
	stream << "property float z " << std::endl;
	//stream << "property uchar red " << std::endl;
	//stream << "property uchar green " << std::endl;
	//stream << "property uchar blue " << std::endl;
	stream << "end_header " << std::endl;

	const auto& positions = pcd.vertices;
	for (const auto& p : positions) {
		stream
			<< p.position.x << " "
			<< p.position.y << " "
			<< p.position.z << " " << std::endl;
	}
	return true;
}

bool PLYFileWriter::writeBinary(const std::filesystem::path& filename, const PLYFile& pcd)
{
	std::ofstream stream(filename, std::ios::out | std::ios::binary);
	if (!stream.is_open()) {
		return false;
	}
	return writeBinary(stream, pcd);
}

namespace {
	bool isLittleEndian()
	{
		int x = 1;   // 0x00000001

		if (*(char*)&x) {
			// yƒAzlittle endian. memory image 01 00 00 00
			return true;
		}
		else {
			// yƒCz   big endian. memory image 00 00 00 01
			return false;
		}
	}
}

#include <iostream>

bool PLYFileWriter::writeBinary(std::ostream& stream, const PLYFile& pcd)
{
	const auto isLittleEndian = ::isLittleEndian();

	stream << "ply" << std::endl;
	if (isLittleEndian) {
		stream << "format binary_little_endian 1.0" << std::endl;
	}
	else {
		stream << "format binary_big_endian 1.0" << std::endl;
	}
	stream << "comment " << std::endl;
	stream << "comment " << std::endl;
	stream << "obj_info " << std::endl;
	stream << "element vertex " << pcd.vertices.size() << std::endl;
	stream << "property float x " << std::endl;
	stream << "property float y " << std::endl;
	stream << "property float z " << std::endl;
	//stream << "property uchar red " << std::endl;
	//stream << "property uchar green " << std::endl;
	//stream << "property uchar blue " << std::endl;
	stream << "end_header " << std::endl;

	const auto& positions = pcd.vertices;
	for (const auto& p : positions) {
		stream.write((char*)&p.position.x, sizeof(p.position.x));
		stream.write((char*)&p.position.y, sizeof(p.position.y));
		stream.write((char*)&p.position.z, sizeof(p.position.z));
	}
	return true;

}
