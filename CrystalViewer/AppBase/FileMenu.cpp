#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "Canvas.h"
#include "FileOpenView.h"
#include "FileSaveView.h"
#include "../../Crystal/Scene/World.h"
#include "../Command/CameraFitCommand.h"
#include "../Command/Command.h"
//#include "../Command/Public/FileImportLabels.h"
#include "../Command/Public/FileExportLabels.h"

#include <iostream>

using namespace Crystal::UI;
using namespace Crystal::Command;

void FileMenu::onShow()
{
	auto model = getModel();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("New")) {
			model->clear();
			model->init();
			model->updateViewModel();
		}
		if (ImGui::MenuItem("Import")) {
			FileOpenView view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.mtl");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				Crystal::Command::Command command("FileImport");
				command.setArg(::FilePathLabel, std::filesystem::path(filename));
				command.execute(model);
				bool isOk = std::any_cast<bool>(command.getResult(::IsOkLabel));
				if (!isOk) {
					std::cout << "import failed." << std::endl;
				}
			}
			//canvas->update();
		}
		if (ImGui::MenuItem("Export")) {
			FileSaveView view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.mtl");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				Crystal::Command::Command command(::FileExportCommandLabel);
				command.setArg(::FilePathLabel, std::filesystem::path(filename));
				command.execute(model);
				bool isOk = std::any_cast<bool>( command.getResult(::IsOkLabel) );
				if (!isOk) {
					std::cout << "export failed." << std::endl;
				}
			}
			//model->write(filename);
		}
		if (ImGui::MenuItem("ScreenShot")) {
			FileOpenView view("");
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
