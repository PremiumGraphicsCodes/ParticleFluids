#include "CommandFactory.h"

#include "MockCommand.h"
#include "FileImportCommand.h"
#include "FileExportCommand.h"
#include "ParticleSystemAddCommand.h"
#include "WireFrameAddCommand.h"
#include "PolygonMeshAddCommand.h"
#include "CameraFitCommand.h"
#include "CameraTranslateCommand.h"
#include "CameraRotateCommand.h"
#include "CameraZoomCommand.h"
#include "PickCommand.h"
#include "TransformCommand.h"
#include "TranslateCommand.h"
#include "RotateCommand.h"
#include "ScaleCommand.h"

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
	else if (name == CameraFitCommand::getName()) {
		return std::make_unique<CameraFitCommand>();
	}
	else if (name == CameraXYCommand::getName()) {
		return std::make_unique<CameraXYCommand>();
	}
	else if (name == "CameraYZ") {
		return std::make_unique<CameraYZCommand>();
	}
	else if (name == "CameraZX") {
		return std::make_unique<CameraZXCommand>();
	}
	else if (name == "CameraTranslate") {
		return std::make_unique<CameraTranslateCommand>();
	}
	else if (name == "CameraRotate") {
		return std::make_unique<CameraRotateCommand>();
	}
	else if (name == "CameraZoom") {
		return std::make_unique<CameraZoomCommand>();
	}
	else if (name == PickCommand::getName()) {
		return std::make_unique<PickCommand>();
	}
	else if (name == "Transform") {
		return std::make_unique<TransformCommand>();
	}
	else if (name == "Translate") {
		return std::make_unique<TranslateCommand>();
	}
	else if (name == "Rotate") {
		return std::make_unique<RotateCommand>();
	}
	else if (name == "Scale") {
		return std::make_unique<ScaleCommand>();
	}

	assert(false);
	return nullptr;
}