#include "CommandFactory.h"

#include "MockCommand.h"
#include "NewCommand.h"
#include "FileImportCommand.h"
#include "FileExportCommand.h"
#include "ParticleSystemCreateCommand.h"
#include "WireFrameCreateCommand.h"
#include "PolygonMeshCreateCommand.h"
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
#include "LightCreateCommand.h"
#include "MaterialCreateCommand.h"
#include "TextureCreateCommand.h"

using namespace Crystal::Command;

std::unique_ptr<ICommand> CommandFactory::create(const std::string& name)
{
	if (name == MockCommand::getName()) {
		return std::make_unique<MockCommand>();
	}
	else if (name == NewCommand::getName()) {
		return std::make_unique<NewCommand>();
	}
	else if (name == FileImportCommand::getName()) {
		return std::make_unique<FileImportCommand>();
	}
	else if (name == FileExportCommand::getName()) {
		return std::make_unique<FileExportCommand>();
	}
	else if (name == ParticleSystemCreateCommand::getName()) {
		return std::make_unique<ParticleSystemCreateCommand>();
	}
	else if (name == WireFrameCreateCommand::getName()) {
		return std::make_unique<WireFrameCreateCommand>();
	}
	else if (name == PolygonMeshCreateCommand::getName()) {
		return std::make_unique<PolygonMeshCreateCommand>();
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
	else if (name == LightCreateCommand::getName()) {
		return std::make_unique<LightCreateCommand>();
	}
	else if (name == MaterialCreateCommand::getName()) {
		return std::make_unique<MaterialCreateCommand>();
	}
	else if (name == TextureCreateCommand::getName()) {
		return std::make_unique<TextureCreateCommand>();
	}

	assert(false);
	return nullptr;
}