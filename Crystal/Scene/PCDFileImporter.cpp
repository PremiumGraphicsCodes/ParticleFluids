#include "PCDFileImporter.h"

#include "../IO/PCDFileReader.h"
#include "Scene.h"

using namespace Crystal::IO;
using namespace Crystal::Model;

bool PCDFileImporter::importPCD(const std::experimental::filesystem::path& filePath, Scene& repository)
{
	PCDFileReader reader;
	if (reader.read(filePath)) {
		const auto& positions = reader.getPCD().data.positions;
		ParticleAttribute attr;
		attr.color = glm::vec4(0, 0, 0, 0);
		attr.size = 1.0;
		repository.getParticleSystems()->addObject(positions, attr, "PCD");
		return true;
	}
	return false;
}
