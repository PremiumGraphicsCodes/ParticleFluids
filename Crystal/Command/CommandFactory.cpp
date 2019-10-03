#include "CommandFactory.h"

#include "MockCommand.h"
#include "FileImportCommand.h"
#include "FileExportCommand.h"
#include "ParticleSystemAddCommand.h"
#include "WireFrameAddCommand.h"
#include "PolygonMeshAddCommand.h"
#include "CameraFitCommand.h"
#include "CameraRotateCommand.h"

using namespace Crystal::Command;

std::unique_ptr<ICommand> CommandFactory::create(const std::string& name)
{
	if (name == "Mock") {
		return std::make_unique<MockCommand>();
	}
	else if (name == "FileImport") {
		return std::make_unique<FileImportCommand>();		
	}
	else if (name == "FileExport") {
		return std::make_unique<FileExportCommand>();
	}
	else if (name == "ParticleSystemAdd") {
		return std::make_unique<ParticleSystemAddCommand>();
	}
	else if (name == "WireFrameAdd") {
		return std::make_unique<WireFrameAddCommand>();
	}
	else if (name == "PolygonMeshAdd") {
		return std::make_unique<PolygonMeshAddCommand>();
	}
	else if (name == "CameraFit") {
		return std::make_unique<CameraFitCommand>();
	}
	else if (name == "CameraXY") {
		return std::make_unique<CameraXYCommand>();
	}
	else if (name == "CameraYZ") {
		return std::make_unique<CameraYZCommand>();
	}
	else if (name == "CameraZX") {
		return std::make_unique<CameraZXCommand>();
	}
	else if (name == "CameraRotate") {
		return std::make_unique<CameraRotateCommand>();
	}


	assert(false);
	return nullptr;
}