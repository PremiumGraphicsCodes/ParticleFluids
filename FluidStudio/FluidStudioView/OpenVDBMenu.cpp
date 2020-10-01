#ifdef NDEBUG
#include "OpenVDBMenu.h"

//#include "../../CrystalViewer/AppBase/"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/AppBase/imgui.h"
#include "../../CrystalViewer/AppBase/FileOpenView.h"

#include "../OpenVDBConverter/OpenVDBFileReader.h"
#include "../OpenVDBConverter/OpenVDBFileWriter.h"

#include "../OpenVDBConverter/OpenVDBAdapter.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::UI;
using namespace Crystal::OpenVDB;

OpenVDBMenu::OpenVDBMenu(const std::string& name, Scene::World* model, Canvas* canvas) :
	IMenu(name, model, canvas)
{
	OpenVDBAdapter::init();
}

void OpenVDBMenu::onShow()
{
	auto model = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("Import")) {
			FileOpenView view("");
			view.addFilter("*.vdb");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				OpenVDBFileReader reader;
				const auto isOk = reader.read(filename);
				if (!isOk) {
					std::cout << "import failed." << std::endl;
				}
				else {
					const auto id = getWorld()->getNextSceneId();
					ParticleSystem<ParticleAttribute> ps;
//					ps.add(V)
					//Crystal::Scene::ParticleSystemScene ps(id, "VDB", ;
//					getWorld()->getScenes()->addScene();
				}
			}
//			reader.read()
		}
		if (ImGui::MenuItem("Export")) {
			OpenVDBFileWriter writer;
			writer.addPoint(Vector3dd(0, 1, 0));
			writer.addPoint(Vector3dd(1.5, 3.5, 1));
			writer.addPoint(Vector3dd(-1, 6, -2));
			writer.addPoint(Vector3dd(1.1, 1.25, 0.06));

			writer.setName("Points");
			writer.write("testWrite.vdb");
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}

#endif