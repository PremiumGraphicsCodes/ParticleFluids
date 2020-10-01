#ifdef NDEBUG
#include "OpenVDBMenu.h"

//#include "../../CrystalViewer/AppBase/"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/AppBase/imgui.h"
#include "../../CrystalViewer/AppBase/FileOpenView.h"
#include "../../CrystalViewer/AppBase/FileSaveView.h"

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
	auto world = getWorld();

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
				if (isOk) {
					const auto id = getWorld()->getNextSceneId();
					ParticleSystem<ParticleAttribute> ps;
					//					ps.add(V)
										//Crystal::Scene::ParticleSystemScene ps(id, "VDB", ;
					//					getWorld()->getScenes()->addScene();
				}
				else {
					std::cout << "import failed." << std::endl;
				}
			}
//			reader.read()
		}
		if (ImGui::MenuItem("Export")) {
			FileSaveView fileSaveView("Export");
			fileSaveView.addFilter("*.vdb");
			fileSaveView.show();
			const auto& filename = fileSaveView.getFileName();
			if (!filename.empty()) {
				const auto scenes = world->getScenes()->findScenes(SceneType::ParticleSystemScene);
				OpenVDBFileWriter writer;
				writer.addPoint(Vector3dd(0, 1, 0));
				writer.addPoint(Vector3dd(1.5, 3.5, 1));
				writer.addPoint(Vector3dd(-1, 6, -2));
				writer.addPoint(Vector3dd(1.1, 1.25, 0.06));

				writer.setName("Points");
				std::cout << filename << std::endl;
				const auto isOk = writer.write(filename);
				if (!isOk) {
					std::cout << "export failed." << std::endl;
				}
			}
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}

#endif