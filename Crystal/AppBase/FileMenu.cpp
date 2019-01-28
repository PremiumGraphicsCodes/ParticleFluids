#include "FileMenu.h"
#include "imgui.h"
#include "tinyfiledialogs.h"
#include "../UI/Model.h"
#include "../UI/Canvas.h"

using namespace Crystal::UI;

void FileMenu::show()
{
	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("Open")) {
			char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
			const auto filename = tinyfd_openFileDialog("Open", "", 2, lFilterPatterns, nullptr, 0);
			model->read(filename);
			//canvas->update();

		}
		if (ImGui::MenuItem("Save")) {
			char const * lFilterPatterns[2] = { "*.stl", "*.obj" };
			//const auto filename = tinyfd_saveFileDialog("Save", "", 2, lFilterPatterns, nullptr, 0);
			//model->write(filename);
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}
