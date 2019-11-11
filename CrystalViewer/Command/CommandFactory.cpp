#include "CommandFactory.h"

#include "MockCommand.h"
#include "FileImportCommand.h"
#include "FileExportCommand.h"
#include "ParticleSystemAddCommand.h"
#include "WireFrameCreateCommand.h"
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
#include "TrimCommand.h"

using namespace Crystal::Command;

std::unique_ptr<ICommand> CommandFactory::create(const std::string& name)
{
	if (name == MockCommand::getName()) {
		return std::make_unique<MockCommand>();
	}
	else if (name == FileImportCommand::getName()) {
		return std::make_unique<FileImportCommand>();
	}
	else if (name == FileExportCommand::getName()) {
		return std::make_unique<FileExportCommand>();
	}
	else if (name == ParticleSystemAddCommand::getName()) {
		return std::make_unique<ParticleSystemAddCommand>();
	}
	else if (name == WireFrameCreateCommand::getName()) {
		return std::make_unique<WireFrameCreateCommand>();
	}
	else if (name == PolygonMeshAddCommand::getName()) {
		return std::make_unique<PolygonMeshAddCommand>();
	}
	else if (name == CameraFitCommand::getName()) {
		return std::make_unique<CameraFitCommand>();
	}
	else if (name == CameraXYCommand::getName()) {
		return std::make_unique<CameraXYCommand>();
	}
	else if (name == CameraYZCommand::getName()) {
		return std::make_unique<CameraYZCommand>();
	}
	else if (name == CameraZXCommand::getName()) {
		return std::make_unique<CameraZXCommand>();
	}
	else if (name == CameraTranslateCommand::getName()) {
		return std::make_unique<CameraTranslateCommand>();
	}
	else if (name == CameraRotateCommand::getName()) {
		return std::make_unique<CameraRotateCommand>();
	}
	else if (name == CameraZoomCommand::getName()) {
		return std::make_unique<CameraZoomCommand>();
	}
	else if (name == PickCommand::getName()) {
		return std::make_unique<PickCommand>();
	}
	else if (name == TransformCommand::getName()) {
		return std::make_unique<TransformCommand>();
	}
	else if (name == TranslateCommand::getName()) {
		return std::make_unique<TranslateCommand>();
	}
	else if (name == RotateCommand::getName()) {
		return std::make_unique<RotateCommand>();
	}
	else if (name == ScaleCommand::getName()) {
		return std::make_unique<ScaleCommand>();
	}
	else if (name == TrimCommand::getName()) {
		return std::make_unique<TrimCommand>();
	}

	assert(false);
	return nullptr;
}