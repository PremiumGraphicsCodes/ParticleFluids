#include "VDBFileReadCommand.h"

#include "../CrystalVDB/VDBFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"

#include "PublicLabels/VDBFileReadLabels.h"

using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, "")
{
	add(&filePath);
}

VDBFileReadCommand::Results::Results() :
	newIds(::NewIdLabel, {})
{
	add(&newIds);
}

VDBFileReadCommand::VDBFileReadCommand() :
	ICommand(&args, &results)
{}

VDBFileReadCommand::VDBFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{
}

std::string VDBFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBFileReadCommand::execute(World* world)
{
	VDBFileReader reader;
	const auto isOk = reader.open(args.filePath.getValue());
	if (!isOk) {
		return false;
	}
	reader.readMetaData();
	const auto& pointNames = reader.getPointNames();
	std::vector<int> newIds;
	for (const auto& n : pointNames) {
		const auto scene = reader.readPositions(n);
		scene->setId(world->getNextSceneId());
		scene->setName(n);
		world->getScenes()->addScene(scene);
		const auto newId = scene->getId();
		newIds.push_back(newId);
	}

	const auto& volumeNames = reader.getGridNames();
	for (const auto& n : volumeNames) {
		const auto scene = reader.readVolume(n);
		scene->setId(world->getNextSceneId());
		scene->setName(n);
		//auto scene = new VDBVolumeScene(world->getNextSceneId(), n);
		world->getScenes()->addScene(scene);
		const auto newId = scene->getId();
		newIds.push_back(newId);
	}

	results.newIds.setValue(newIds);
	//reader.get
	return true;
}

