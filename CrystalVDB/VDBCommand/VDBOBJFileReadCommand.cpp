#include "VDBOBJFileReadCommand.h"

#include "../../Crystal/IO/OBJFileReader.h"

#include "../VDBConverter/VDBPolygonMesh.h"
#include "PublicLabels/VDBOBJFileWriteLabels.h"

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
}

VDBOBJFileReadCommand::VDBOBJFileReadCommand() :
	ICommand(&args, &results)
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
	auto mesh = new VDBPolygonMesh(world->getNextSceneId(), "OBJImport");
	for (const auto& p : obj.positions) {
		mesh->addVertex(p);
	}
	for (const auto& g : obj.groups) {
		for (const auto& f : g.faces) {
			const auto i = f.positionIndices;
			const auto n = obj.normals[f.normalIndices[0]];
			if (i.size() == 3) {
				mesh->addTriangle({ i[0], i[1], i[2] });
			}
			else if (i.size() == 4) {
				mesh->addQuad({ i[0], i[1], i[2], i[3] });
			}
		}
	}
	mesh->updateNormals();
	world->getScenes()->addScene(mesh);
	return false;
}
