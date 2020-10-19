#include "OpenVDBFileReadCommand.h"

#include "../OpenVDBConverter/OpenVDBFileReader.h"

#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/Command/Public/PublicLabel.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::OpenVDB;

namespace 
{
	PublicLabel CommandNameLabel = "OpenVDBFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel NewIdLabel = "NewId";
}

OpenVDBFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

OpenVDBFileReadCommand::Results::Results() :
	newIds(::NewIdLabel, {})
{
	add(&newIds);
}

OpenVDBFileReadCommand::OpenVDBFileReadCommand() :
	ICommand(&args, &results)
{}

std::string OpenVDBFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool OpenVDBFileReadCommand::execute(World* world)
{
	OpenVDBFileReader reader;
	const auto isOk = reader.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	const auto& names = reader.getPointGridNames();

	std::vector<int> newIds;
	for (auto n : names) {
		const auto& positions = reader.readPositions(n);
		ParticleAttribute attr;
		auto ps = std::make_unique< ParticleSystem<ParticleAttribute> >(positions, attr);
		ParticleSystemScene* scene = new ParticleSystemScene(world->getNextSceneId(), "", std::move(ps));
		world->getScenes()->addScene(scene);
		const auto newId = scene->getId();
		newIds.push_back(newId);
	}
	results.newIds.setValue(newIds);
	//reader.get
	return true;
}

