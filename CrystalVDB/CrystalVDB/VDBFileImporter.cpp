#include "VDBFileImporter.h"

#include "../../Crystal/IO/PLYFileReader.h"
#include "../../Crystal/IO/PCDFileReader.h"
#include "../../Crystal/IO/OBJFileReader.h"
#include "../../Crystal/IO/STLFileReader.h"

#include "VDBParticleSystemScene.h"
#include "VDBPolygonMeshScene.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::VDB;

VDBParticleSystemScene* VDBFileImporter::readPLY(const std::string& filePath)
{
	auto scene = new VDBParticleSystemScene();

	Crystal::IO::PLYFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return nullptr;
	}
	//scene->resetImpl();
	const auto ply = reader.getPLY();
	std::vector<Vector3dd> positions;
	for (const auto& v : ply.vertices) {
		const auto x = v.getValueAs<float>(0);
		const auto y = v.getValueAs<float>(1);
		const auto z = v.getValueAs<float>(2);
		positions.emplace_back(x, y, z);
	}
	scene->create(positions);
	for (int i = 3; i < ply.properties.size(); ++i) {
		if (ply.properties[i].type == Crystal::IO::PLYType::FLOAT) {
			scene->addFloatAttribute(ply.properties[i].name);
			std::vector<float> values;
			for (const auto& v : ply.vertices) {
				const auto t = v.getValueAs<float>(i);
				values.push_back(t);
				//std::cout << t;
			}
			scene->setFloatAttribute(ply.properties[i].name, values);
			//const auto vs = scene->getFloatAttribute(ply.properties[i].name);
		}

	}

	return scene;
}

VDBParticleSystemScene* VDBFileImporter::readPCD(const std::string& filePath)
{
	Crystal::IO::PCDFileReader reader;
	const auto isOk = reader.readBinary(filePath);
	if (!isOk) {
		return nullptr;
	}
	const auto pcd = reader.getPCD();
	auto scene = new VDBParticleSystemScene();
	scene->create(pcd.data.positions);

	return scene;
}

VDBPolygonMeshScene* VDBFileImporter::readOBJ(const std::string& filePath)
{
	Crystal::IO::OBJFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return nullptr;
	}
	const auto obj = reader.getOBJ();
	auto mesh = new VDBPolygonMeshScene();
	for (const auto& p : obj.positions) {
		mesh->addVertex(p);
	}
	for (const auto& g : obj.groups) {
		for (const auto& f : g.faces) {
			const auto i = f.positionIndices;
			//const auto n = obj.normals[f.normalIndices[0]];
			if (i.size() == 3) {
				mesh->addTriangle({ i[0] - 1, i[1] - 1, i[2] - 1 });
			}
			else if (i.size() == 4) {
				mesh->addQuad({ i[0] - 1, i[1] - 1, i[2] - 1, i[3] - 1 });
			}
		}
	}
	mesh->updateNormals();
	return mesh;
}

VDBPolygonMeshScene* VDBFileImporter::readSTL(const std::string& filePath)
{
	Crystal::IO::STLFileReader reader;
	const auto isOk = reader.readBinary(filePath);
	if (!isOk) {
		return nullptr;
	}
	auto mesh = new VDBPolygonMeshScene();
	const auto stl = reader.getSTL();
	unsigned int index = 0;
	for (const auto& f : stl.faces) {
		mesh->addVertex(f.triangle.getV0());
		mesh->addVertex(f.triangle.getV1());
		mesh->addVertex(f.triangle.getV2());
		mesh->addTriangle({ index, index + 1, index + 2 });
		index += 3;
	}
	return mesh;
}