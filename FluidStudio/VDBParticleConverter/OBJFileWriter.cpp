#include "OBJFileWriter.h"

#include <fstream>

using namespace Crystal::OpenVDB;

bool OBJFileWriter::write(const std::string& filePath, const PolygonMesh& mesh)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, mesh);
}

bool OBJFileWriter::write(std::ostream& stream, const PolygonMesh& mesh)
{
	stream << "g cube" << std::endl;
	// vertices
	const auto& vertices = mesh.points;
	for (const auto& v : vertices) {
		stream << "v " << v.x() << " " << v.y() << " " << v.z() << std::endl;
	}
	
	stream << "vn " << "1.0" << " " << "0.0" << " " << "0.0" << std::endl;

	const auto& triangles = mesh.triangles;
	for (const auto& t : triangles) {
		stream << "f" << " " << t[0] << "/" << t[1] << "/" << t[2] << std::endl;
	}

	const auto& quads = mesh.quads;
	for (const auto& q : quads) {
		const auto f1 = q[0] + 1;
		const auto f2 = q[1] + 1;
		const auto f3 = q[2] + 1;
		const auto f4 = q[3] + 1;
		stream << "f" << " " << f1 << "//1 " << f2 << "//1 " << f3 << "//1 " << f4 << "//1" << std::endl;
	}
	return true;
}