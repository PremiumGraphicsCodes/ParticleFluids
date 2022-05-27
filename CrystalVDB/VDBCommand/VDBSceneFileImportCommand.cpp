#include "VDBSceneFileImportCommand.h"

#include "../../Crystal/IO/PLYFileReader.h"
#include "../../Crystal/IO/PCDFileReader.h"
#include "../../Crystal/IO/OBJFileReader.h"
#include "../../Crystal/IO/STLFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "../CrystalVDB/VDBScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

#include <iostream>

namespace
{
	PublicLabel CommandNameLabel = "VDBSceneFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel FileFormatLabel = "FileFormat";
	PublicLabel FileFormat_PLY_Label = "PLY";
	PublicLabel FileFormat_PCD_Label = "PCD";
	PublicLabel FileFormat_OBJ_Label = "OBJ";
	PublicLabel FileFormat_STL_Label = "STL";
	PublicLabel NewSceneIdLabel = "NewSceneId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBSceneFileImportCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	fileFormat(::FileFormatLabel, "")
{
	add(&filePath);
	add(&fileFormat);
}

VDBSceneFileImportCommand::Results::Results() :
	newSceneId(::NewSceneIdLabel, -1)
{
	add(&newSceneId);
}

VDBSceneFileImportCommand::VDBSceneFileImportCommand() :
	ICommand(&args, &results)
{}

VDBSceneFileImportCommand::VDBSceneFileImportCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBSceneFileImportCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBSceneFileImportCommand::execute(World* world)
{
	const auto format = args.fileFormat.getValue();
	VDBScene* scene = new VDBScene(world->getNextSceneId(), "Imported");
	if (format == FileFormat_PLY_Label) {
		auto points = readPLY();
		if (points != nullptr) {
			scene->addScene(points);
		}
	}
	else if (format == FileFormat_PCD_Label) {
		auto points = readPCD();
		if (points != nullptr) {
			scene->addScene(points);
		}
	}
	else if (format == FileFormat_OBJ_Label) {
		auto mesh = readOBJ();
		if (mesh != nullptr) {
			scene->addScene(mesh);
		}
	}
	else if (format == FileFormat_STL_Label) {
		auto mesh = readSTL();
		if (mesh != nullptr) {
			scene->add(mesh);
		}
	}
	else {
		assert(false);
		return false;
	}
	results.newSceneId.setValue(scene->getId());
	return true;
}

VDBParticleSystemScene* VDBSceneFileImportCommand::readPLY()
{
	auto scene = new VDBParticleSystemScene();

	const auto filePath = args.filePath.getValue();
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

VDBParticleSystemScene* VDBSceneFileImportCommand::readPCD()
{
	const auto filePath = args.filePath.getValue();
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

VDBPolygonMeshScene* VDBSceneFileImportCommand::readOBJ()
{
	const auto filePath = args.filePath.getValue();
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

VDBPolygonMeshScene* VDBSceneFileImportCommand::readSTL()
{
	Crystal::IO::STLFileReader reader;
	const auto isOk = reader.readBinary(args.filePath.getValue());
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