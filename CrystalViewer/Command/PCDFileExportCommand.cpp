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
	const auto& ps = particles->getShape()->getParticles();
	for (auto p : ps) {
		file.data.positions.push_back( p->getPosition() );
	}
	PCDFileWriter writer;
	std::filesystem::path filePath(args.filePath.getValue());
	bool isOk = writer.write(filePath, file);
	this->results.isOk.setValue( isOk );
}
