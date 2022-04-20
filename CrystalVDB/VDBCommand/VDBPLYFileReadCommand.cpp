#include "VDBPLYFileReadCommand.h"

#include "../../Crystal/IO/PLYFileReader.h"

#include "../CrystalVDB/VDBParticleSystemScene.h"
#include "../CrystalVDB/VDBVolumeScene.h"
#include "CrystalScene/Command/Public/PublicLabel.h"

namespace
{
	PublicLabel CommandNameLabel = "VDBPLYFileRead";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IsVolumeLabel = "IsVolume";
	PublicLabel VDBPSIdLabel = "VDBPSId";
}

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPLYFileReadCommand::Args::Args() :
	filePath(::FilePathLabel, ""),
	isVolume(::IsVolumeLabel, false),
	vdbSceneId(::VDBPSIdLabel, -1)
{
	add(&filePath);
	add(&isVolume);
	add(&vdbSceneId);
}

VDBPLYFileReadCommand::Results::Results()
{
}

VDBPLYFileReadCommand::VDBPLYFileReadCommand() :
	ICommand(&args, &results)
{}

VDBPLYFileReadCommand::VDBPLYFileReadCommand(const Args& args) :
	args(args),
	ICommand(&this->args, &results)
{}

std::string VDBPLYFileReadCommand::getName()
{
	return ::CommandNameLabel;
}

bool VDBPLYFileReadCommand::execute(World* world)
{
	if (args.isVolume.getValue()) {
		return readVolume(world);
	}
	else {
		return readPoints(world);
	}
}

#include <iostream>

bool VDBPLYFileReadCommand::readPoints(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBParticleSystemScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto filePath = args.filePath.getValue();
	Crystal::IO::PLYFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	scene->resetImpl();
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
				std::cout << t;
			}
			scene->setFloatAttribute(ply.properties[i].name, values);
			const auto vs = scene->getFloatAttribute(ply.properties[i].name);
		}

	}

	return true;
}

bool VDBPLYFileReadCommand::readVolume(World* world)
{
	auto scene = world->getScenes()->findSceneById<VDBVolumeScene*>(args.vdbSceneId.getValue());
	if (scene == nullptr) {
		return false;
	}

	const auto filePath = args.filePath.getValue();
	Crystal::IO::PLYFileReader reader;
	const auto isOk = reader.read(filePath);
	if (!isOk) {
		return false;
	}
	scene->resetImpl();
	const auto ply = reader.getPLY();
	for (const auto& v : ply.vertices) {
		const auto x = static_cast<int>( v.getValueAs<float>(0));
		const auto y = static_cast<int>( v.getValueAs<float>(1));
		const auto z = static_cast<int>( v.getValueAs<float>(2));
		const auto value = v.getValueAs<float>(3);
		scene->setValue({ x,y,z }, value);
	}

	//scene->reset
	return true;
}