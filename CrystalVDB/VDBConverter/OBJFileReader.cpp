#include "OBJFileReader.h"

#include "../../Crystal/IO/Helper.h"

#include "PolygonMeshImpl.h"

#include <fstream>
#include <cassert>
#include <vector>

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::VDB;

namespace {
	openvdb::Vec3s readVertices(const std::string& str) {
		const auto& strs = Helper::split(str, ' ');
		//assert(strs.front() == "v");

		const float x = std::stof(strs[0].c_str());
		const float y = std::stof(strs[1].c_str());
		const float z = std::stof(strs[2].c_str());
		if (strs.size() == 4) {
			const float w = ::std::stof(strs[3].c_str());
			return openvdb::Vec3s(x, y, z);
		}
		else {
			return openvdb::Vec3s(x, y, z);
		}
	}

	openvdb::Vec3s readVector3d(const std::string& str) {
		const auto& strs = Helper::split(str, ' ');
		//assert(strs.front() == "vt");
		const float u = ::std::stof(strs[0]);
		const float v = ::std::stof(strs[1]);
		if (strs.size() == 3) {
			const float w = std::stof(strs[2]);
			return openvdb::Vec3s(u, v, w);
		}
		else {
			return openvdb::Vec3s(u, v, 0.0f);
		}
	}
}


bool OBJFileReader::read(const std::string& filePath, VDBPolygonMesh& mesh)
{
	std::ifstream stream;
	stream.open(filePath);

	if (!stream.is_open()) {
		return false;
	}

	return read(stream, mesh);
}

bool OBJFileReader::read(std::istream& stream, VDBPolygonMesh& mesh)
{
	std::string str;

	std::string header;

	PolygonMeshImpl impl;
	while (!stream.eof()) {
		if (header == "#") {
			std::getline(stream, str);
			//header = read< std::string >();
		}
		else if (header == "v") {
			std::getline(stream, str);
			//impl.points.push_back
			impl.points.push_back(readVertices(str));
		}
		else if (header == "vt") {
			std::getline(stream, str);
		}
		else if (header == "vn" || header == "-vn") {
			std::getline(stream, str);
			//impl.normals.push_back(readVector3d(str));
		}
		else if (header == "mtllib") {
			std::getline(stream, str);
		}
		else if (header == "usemtl") {
			std::getline(stream, str);
		}
		else if (header == "f") {
			std::getline(stream, str);

			std::vector< std::string >& strs = Helper::split(str, ' ');

			/*
			OBJFace face;

			//assert(strs.front() == "f");
			for (unsigned int i = 0; i < strs.size(); ++i) {
				if (strs[i].empty()) {
					continue;
				}
				std::string::size_type pos(strs[i].find("//"));
				if (pos != std::string::npos) {
					strs[i].replace(pos, 2, "/ /");
				}

				std::vector<std::string>& splitted = Helper::split(strs[i], '/');
				const int positionIndex = std::stoi(splitted[0]);
				face.positionIndices.push_back(positionIndex);

				if (splitted.size() >= 2 && splitted[1] != " ") {
					const int texIndex = std::stoi(splitted[1]);
					face.texCoordIndices.push_back(texIndex);
				}
				else {
					face.texCoordIndices.push_back(-1);
				}

				if (splitted.size() >= 3) {
					const int normalIndex = std::stoi(splitted[2]);
					face.normalIndices.push_back(normalIndex);
				}
				else {
					face.normalIndices.push_back(-1);
				}
			}

			currentGroup.faces.push_back(face);
			*/
		}
	}
	//obj.groups.push_back(currentGroup);
	return true;
}