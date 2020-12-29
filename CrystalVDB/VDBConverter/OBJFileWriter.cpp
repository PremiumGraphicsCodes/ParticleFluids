#include "OBJFileWriter.h"

#include "PolygonMeshImpl.h"

#include <fstream>

using namespace Crystal::VDB;

bool OBJFileWriter::write(const std::string& filePath, const VDBPolygonMesh& mesh)
{
	std::ofstream stream(filePath);
	if (!stream.is_open()) {
		return false;
	}
	return write(stream, mesh);
}

bool OBJFileWriter::write(std::ostream& stream, const VDBPolygonMesh& mesh_)
{
	auto mesh = mesh_.getImpl();
	stream << "g cube" << std::endl;
	// vertices
	const auto& vertices = mesh->points;
	for (const auto& v : vertices) {
		stream << "v " << v.x() << " " << v.y() << " " << v.z() << std::endl;
	}

	for (const auto& n : mesh->triangleNormals) {
		stream << "vn " << n.x() << " " << n.y() << " " << n.z() << std::endl;
	}

	for (const auto& n : mesh->quadNormals) {
		stream << "vn " << n.x() << " " << n.y() << " " << n.z() << std::endl;
	}

	int normalIndex = 1;
	// TODO : triangle normal.
	const auto& triangles = mesh->triangles;
	for (const auto& t : triangles) {
		const auto f1 = t[0] + 1;
		const auto f2 = t[1] + 1;
		const auto f3 = t[2] + 1;
		stream << "f"
			<< " " << f1 << "//" << normalIndex
			<< " " << f2 << "//" << normalIndex
			<< " " << f3 << "//" << normalIndex
			<< std::endl;
		normalIndex++;
	}

	const auto& quads = mesh->quads;
	for (const auto& q : quads) {
		const auto f1 = q[0] + 1;
		const auto f2 = q[1] + 1;
		const auto f3 = q[2] + 1;
		const auto f4 = q[3] + 1;
		stream << "f"
			<< " " << f1 << "//" << normalIndex
			<< " " << f2 << "//" << normalIndex
			<< " " << f3 << "//" << normalIndex
			<< " " << f4 << "//" << normalIndex
			<< std::endl;
		normalIndex++;
	}
	return true;
}