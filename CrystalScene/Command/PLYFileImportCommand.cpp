#include "PLYFileImportCommand.h"

#include "../../Crystal/IO/PLYFileReader.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace PLYFileImportLabels
{
	PublicLabel CommandNameLabel = "PLYFileImport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel ParticleSystemIdLabel = "ParticleSystemId";
}

using namespace Crystal::Shape;
using namespace Crystal::IO;
using namespace Crystal::Scene;
using namespace Crystal::Command;

PLYFileImportCommand::Args::Args() :
	filePath(PLYFileImportLabels::FilePathLabel, ""),
	particleSystemId(PLYFileImportLabels::ParticleSystemIdLabel, -1)
{
	add(&filePath);
	add(&particleSystemId);
}

PLYFileImportCommand::Results::Results()
{
}

std::string PLYFileImportCommand::getName()
{
	return PLYFileImportLabels::CommandNameLabel;
}

bool PLYFileImportCommand::execute(Crystal::Scene::World* scene)
{
	const auto id = args.particleSystemId.getValue();
	const auto filePath = args.filePath.getValue();
	const auto psScene = scene->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (psScene == nullptr) {
		return false;
	}

	PLYFileReader reader;
	const auto isOk = reader.readBinary(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto& positions = reader.getPositions();
	ParticleAttribute attr;
	attr.color = glm::vec4(0, 0, 0, 0);
	attr.size = 1.0;
	auto shape = std::make_unique<ParticleSystem<ParticleAttribute>>(positions, attr);
	psScene->resetShape(std::move(shape));
	return true;
}