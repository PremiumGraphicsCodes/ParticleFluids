#include "PCDFileImporter.h"

#include "../IO/PCDFileReader.h"
#include "Scene.h"
#include "SceneFactory.h"

using namespace Crystal::IO;
using namespace Crystal::Scene;

PCDFileImporter::PCDFileImporter(SceneFactory* factory) :
	factory(factory)
{}

bool PCDFileImporter::importPCD(const std::experimental::filesystem::path& filePath, IScene* parent)
{
	PCDFileReader reader;
	if (reader.read(filePath)) {
		const auto& positions = reader.getPCD().data.positions;
		ParticleAttribute attr;
		attr.color = glm::vec4(0, 0, 0, 0);
		attr.size = 1.0;
		parent->addScene( factory->createParticleSystemScene(positions, attr, "PCD") );
		return true;
	}
	return false;
}
