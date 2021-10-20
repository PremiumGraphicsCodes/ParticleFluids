#include "TXTFileExportCommand.h"

#include "../../Crystal/IO/TXTFileWriter.h"
#include "../Scene/ParticleSystemScene.h"

#include "PublicLabel.h"

namespace TXTFileExportLabels
{
	PublicLabel CommandNameLabel = "TXTFileExport";
	PublicLabel FilePathLabel = "FilePath";
	PublicLabel IdLabel = "Id";
}

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

TXTFileExportCommand::Args::Args() :
	id(TXTFileExportLabels::IdLabel, -1),
	filePath(TXTFileExportLabels::FilePathLabel, "")
{
	add(&id);
	add(&filePath);
}

TXTFileExportCommand::Results::Results()
{
	//	add(&isOk);
}

std::string TXTFileExportCommand::getName()
{
	return TXTFileExportLabels::CommandNameLabel;
}

bool TXTFileExportCommand::execute(World* world)
{
	const auto id = args.id.getValue();

	auto scene = world->getScenes()->findSceneById<ParticleSystemScene*>(id);
	if (scene == nullptr) {
		return false;
	}
	const auto& ps = scene->getShape()->getPositions();

	TXTFileWriter writer;
	const auto isOk = writer.write(args.filePath.getValue(), ps);
	return isOk;
}
