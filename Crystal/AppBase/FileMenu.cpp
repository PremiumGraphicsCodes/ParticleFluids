#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "FileOpenView.h"
#include "FileSaveView.h"

using namespace Crystal::UI;

void FileMenu::show()
{
	auto model = getModel();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("New")) {
			model->clear();
			getCanvas()->setViewModel(model->toViewModel());
		}
		if (ImGui::MenuItem("Open")) {
			FileOpenView view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				model->read(filename);
			}
			//canvas->update();
		}
		if (ImGui::MenuItem("Save")) {
			FileSaveView view("");
			view.addFilter("*.stl");
			view.addFilter("*.obj");
			view.addFilter("*.pcd");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				model->write(filename);
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
