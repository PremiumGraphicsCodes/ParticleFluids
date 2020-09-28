#ifdef NDEBUG
#include "OpenVDBMenu.h"
#include "../../CrystalViewer/AppBase/imgui.h"

#include "../OpenVDBConverter/OpenVDBFileWriter.h"

#include <iostream>

using namespace openvdb;
using namespace Crystal::OpenVDB;
using namespace Crystal::UI;

void OpenVDBMenu::onShow()
{
	auto model = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("Import")) {
		}
		if (ImGui::MenuItem("Export")) {
			openvdb::initialize();
			OpenVDBFileWriter writer;
			writer.addPoint(openvdb::Vec3R(0, 1, 0));
			writer.addPoint(openvdb::Vec3R(1.5, 3.5, 1));
			writer.addPoint(openvdb::Vec3R(-1, 6, -2));
			writer.addPoint(openvdb::Vec3R(1.1, 1.25, 0.06));

			writer.setName("Points");
			writer.write("testWrite.vdb");
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}

#endif