#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "Canvas.h"
#include "FileOpenMenu.h"
#include "FileSaveMenu.h"
#include "../Scene/World.h"
#include "../Command/CameraFitCommand.h"
#include "../Command/Command.h"
#include "../Command/Public/FileImportLabels.h"
#include "../Command/Public/FileExportLabels.h"
#include "../Command/Public/NewLabels.h"
#include "../Command/NewCommand.h"

#include <iostream>

using namespace Crystal::UI;
using namespace Crystal::Command;

void FileMenu::onShow()
{
	auto model = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("New")) {
			Crystal::Command::Command command(NewLabels::CommandNameLabel);
			command.execute(model);
		}
		if (ImGui::MenuItem("Import")) {
			FileOpenMenu view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.mtl");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				Crystal::Command::Command command("FileImport");
				command.setArg(FileImportLabels::FilePathLabel, std::string(filename));
				bool isOk = command.execute(model);
				/*
				bool isOk = std::any_cast<bool>(command.getResult(FileImportLabels::IsOkLabel));
				*/
				if (!isOk) {
					std::cout << "import failed." << std::endl;
				}
				else {
					const int newId = std::any_cast<int>(command.getResult(FileImportLabels::NewIdLabel));
					auto scene = model->getScenes()->findSceneById<Crystal::Scene::IScene*>(newId);
					auto presenter = scene->getPresenter();
					presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
//					scene->getParent()->se
				}
			}
			//canvas->update();
		}
		if (ImGui::MenuItem("Export")) {
			FileSaveMenu view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.mtl");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				Crystal::Command::Command command(FileExportLabels::FileExportCommandLabel);
				command.setArg(FileExportLabels::FilePathLabel, filename);
				const auto isOk = command.execute(model);
				if (!isOk) {
					std::cout << "export failed." << std::endl;
				}
			}
			//model->write(filename);
		}
		if (ImGui::MenuItem("ScreenShot")) {
			FileOpenMenu view("");
			view.addFilter("*.png");
			view.addFilter("*.bmp");
			view.show();
			const auto filename = view.getFileName();
			const auto& image = getCanvas()->getImage();

		}
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
