#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"

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
			char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
			const auto filename = tinyfd_openFileDialog("Open", "", 2, lFilterPatterns, nullptr, 0);
			if (filename != nullptr) {
				model->read(filename);
			}
			//canvas->update();
		}
		if (ImGui::MenuItem("Save")) {
			char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
			const auto filename = tinyfd_saveFileDialog("Save", "", 2, lFilterPatterns, nullptr);
			if (filename != nullptr) {
				model->write(filename);
			}
			//model->write(filename);
		}
		if (ImGui::MenuItem("ScreenShot")) {
			char const * lFilterPatterns[2] = { "*.png", "*.bmp" };
			const auto filename = tinyfd_openFileDialog("Open", "", 2, lFilterPatterns, nullptr, 0);
			const auto& image = getCanvas()->getImage();

		}
		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
