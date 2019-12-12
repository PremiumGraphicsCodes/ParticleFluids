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
#include "ShapeSelectCommand.h"
#include "DeleteCommand.h"
#include "ClearCommand.h"
#include "OBJFileImportCommand.h"
#include "STLFileImportCommand.h"
#include "PCDFileImportCommand.h"
#include "OBJFileExportCommand.h"
#include "STLFileExportCommand.h"
#include "PCDFileExportCommand.h"

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
	else if (name == ShapeSelectCommand::getName()) {
		return std::make_unique<ShapeSelectCommand>();
	}
	else if (name == DeleteCommand::getName()) {
		return std::make_unique<DeleteCommand>();
	}
	else if (name == ClearCommand::getName()) {
		return std::make_unique<ClearCommand>();
	}
	else if (name == OBJFileImportCommand::getName()) {
		return std::make_unique<OBJFileImportCommand>();
	}
	else if (name == STLFileImportCommand::getName()) {
		return std::make_unique<STLFileImportCommand>();
	}
	else if (name == PCDFileImportCommand::getName()) {
		return std::make_unique<PCDFileImportCommand>();
	}
	else if (name == OBJFileExportCommand::getName()) {
		return std::make_unique<OBJFileExportCommand>();
	}
	else if (name == STLFileExportCommand::getName()) {
		return std::make_unique<STLFileExportCommand>();
	}
	else if (name == PCDFileExportCommand::getName()) {
		return std::make_unique<PCDFileExportCommand>();
	}

	assert(false);
	return nullptr;
}