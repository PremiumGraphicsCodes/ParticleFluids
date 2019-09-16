#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "../Scene/World.h"
#include "Canvas.h"
#include "FileOpenView.h"
#include "FileSaveView.h"

using namespace Crystal::UI;

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
				/*
				if (model->importFile(filename)) {
					model->updateViewModel();
					getCanvas()->fitCamera(getModel()->getBoundingBox());
				}
				*/
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
			/*
			if (!filename.empty()) {
				model->exportFile(filename);
			}
			*/
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
