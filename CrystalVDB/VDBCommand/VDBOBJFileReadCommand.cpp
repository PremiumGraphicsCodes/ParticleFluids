#include "VDBOBJFileReadCommand.h"

#include "../../Crystal/IO/OBJFileReader.h"

#include "../CrystalVDB/VDBPolygonMeshScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBOBJFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel VDBMeshIdLabel = "VDBMeshId";
}

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBOBJFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

VDBOBJFileReadCommand::Results::Results() :
	vdbMeshId(::VDBMeshIdLabel, {})
{
	add(&vdbMeshId);
}

VDBOBJFileReadCommand::VDBOBJFileReadCommand() :
	ICommand(&args, &results)
{}

VDBOBJFileReadCommand::VDBOBJFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBOBJFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBOBJFileReadCommand::execute(World* world)
{
	const auto filePath = args.filePath.getValue();
	Crystal::IO::OBJFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	const auto obj = reader.getOBJ();
	auto mesh = new VDBPolygonMeshScene(world->getNextSceneId(), "OBJImport");
	for (const auto& p : obj.positions) {
		mesh->addVertex(p);
	}
	for (const auto& g : obj.groups) {
		for (const auto& f : g.faces) {
			const auto i = f.positionIndices;
			//const auto n = obj.normals[f.normalIndices[0]];
			if (i.size() == 3) {
				mesh->addTriangle({ i[0]-1, i[1]-1, i[2]-1 });
			}
			else if (i.size() == 4) {
				mesh->addQuad({ i[0]-1, i[1]-1, i[2]-1, i[3]-1 });
			}
		}
	}
	mesh->updateNormals();
	world->getScenes()->addScene(mesh);

	results.vdbMeshId.setValue(mesh->getId());
	return true;
}
