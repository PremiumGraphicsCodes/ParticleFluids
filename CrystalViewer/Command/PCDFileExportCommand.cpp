#include "PCDFileExportCommand.h"

#include "../../Crystal/IO/PCDFileWriter.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "Public/FileExportLabels.h"

using namespace Crystal::Scene;
using namespace Crystal::Command;
using namespace Crystal::IO;

PCDFileExportCommand::Args::Args() :
	id(::IdLabel, -1),
	filePath(::FilePathLabel, "")
{
	add(&id);
	add(&filePath);
}

PCDFileExportCommand::Results::Results() :
	isOk(::IsOkLabel, false)
{
	add(&isOk);
}

std::string PCDFileExportCommand::getName()
{
	return ::PCDFileExportCommandLabel;
}

void PCDFileExportCommand::execute(World* scene)
{
	auto particles = scene->getObjects()->findSceneById<ParticleSystemScene*>(args.id.getValue());
	if (particles == nullptr) {
		results.isOk.setValue(false);
		return;
	}
	PCDFile file;
	//file.data.positions = particles->getShape()->get();
	PCDFileWriter writer;
	//writer.write(args.filePath.getValue(), )
}
