#include "OBJFileReader.h"

#include <fstream>
#include <cassert>
#include <vector>

#include "../Math/Vector3d.h"
#include "../Shape/Vertex.h"
#include "../Shape/Face.h"
//#include "../Scene/PolygonMesh.h"

#include "Helper.h"

#include <string>
#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shape;
using namespace Crystal::IO;

bool OBJFileReader::read(const std::filesystem::path& filePath)
{
	std::ifstream stream;
	stream.open(filePath);

	if (!stream.is_open()) {
		return false;
	}

	return read(stream);
}

bool OBJFileReader::read(std::istream& stream)
{
	std::string str;

	std::string header;
	std::string currentMtllibName;

	auto currentGroup = OBJGroup();

	while (!stream.eof()) {
		if (header == "#") {
			std::getline(stream, str);
			//header = read< std::string >();
		}
		else if (header == "v") {
			std::getline(stream, str);
			obj.positions.push_back(readVertices(str));
		}
		else if (header == "vt") {
			std::getline(stream, str);
			obj.texCoords.push_back(readVector2d(str));
		}
		else if (header == "vn" || header == "-vn") {
			std::getline(stream, str);
			obj.normals.push_back(readVector3d(str));
		}
		else if (header == "mtllib") {
			currentMtllibName = Helper::read<std::string>(stream);
			obj.mtllibs.push_back(currentMtllibName);
		}
		else if (header == "usemtl") {
			currentGroup.usemtl = Helper::read<std::string>(stream);
			//mtllibMap.insert(std::make_pair(currentMtllibName, currentUseMtlName));
		}
		else if (header == "f") {
			std::getline(stream, str);

			std::vector< std::string >& strs = Helper::split(str, ' ');

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
		}
		else if (header == "g") {
			currentGroup.name = Helper::read<std::string>(stream);
			if (!currentGroup.faces.empty()) {
				obj.groups.push_back(currentGroup);
				currentGroup = OBJGroup();
//				currentGroup.name = name;
			}
		}

		header = Helper::read< std::string >(stream);
	}
	obj.groups.push_back(currentGroup);

	return true;
}


Vector3df OBJFileReader::readVertices(const std::string& str)
{
	const auto& strs = Helper::split(str, ' ');
	//assert(strs.front() == "v");

	const float x = std::stof(strs[0].c_str());
	const float y = std::stof(strs[1].c_str());
	const float z = std::stof(strs[2].c_str());
	if (strs.size() == 4) {
		const float w = ::std::stof(strs[3].c_str());
		return Vector3df(x, y, z);
	}
	else {
		return Vector3df(x, y, z);
	}
}

Vector3df OBJFileReader::readVector3d(const std::string& str)
{
	const auto& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	if (strs.size() == 3) {
		const float w = std::stof(strs[2]);
		return Vector3df(u, v, w);
	}
	else {
		return Vector3df(u, v, 0.0f);
	}
}

Vector2df OBJFileReader::readVector2d(const std::string& str)
{
	const auto& strs = Helper::split(str, ' ');
	//assert(strs.front() == "vt");
	const float u = ::std::stof(strs[0]);
	const float v = ::std::stof(strs[1]);
	return Vector2df(u, v);
}