#include "VDBFileReadCommand.h"

#include "../CrystalVDB/VDBFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"

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
	const auto& names = reader.getPointGridNames();
	if (names.empty()) {
		return false;
	}

	std::vector<int> newIds;
	for (auto n : names) {
		const auto& positions = reader.readPositions(n);
		//ParticleAttribute attr;
		//auto ps = std::make_unique< ParticleSystem<ParticleAttribute> >(positions, attr);
		auto scene = new VDBParticleSystemScene(world->getNextSceneId(), n);
		for (const auto& p : positions) {
			scene->add(p, 1.0);
		}
		world->getScenes()->addScene(scene);
		const auto newId = scene->getId();
		newIds.push_back(newId);
	}
	results.newIds.setValue(newIds);
	//reader.get
	return true;
}

