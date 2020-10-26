#include "OpenVDBMenu.h"

//#include "../../CrystalViewer/AppBase/"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/AppBase/imgui.h"
#include "../../CrystalViewer/AppBase/FileOpenView.h"
#include "../../CrystalViewer/AppBase/FileSaveView.h"

#include "../VDBConverter/OpenVDBFileReader.h"
#include "../VDBConverter/OpenVDBFileWriter.h"

#include "../VDBConverter/OpenVDBAdapter.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
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
				const auto isOk = reader.open(filename);
				if(isOk) {
					const auto pointNames = reader.getPointGridNames();
					for (const auto& n : pointNames) {
						const auto positions = reader.readPositions(n);
						const auto id = getWorld()->getNextSceneId();
						auto ps = std::make_unique<ParticleSystem<ParticleAttribute>>();
						ParticleAttribute attr;
						attr.color = ColorRGBAf(1.0, 1.0, 1.0, 1.0);
						attr.size = 10.0f;
						for (const auto& p : positions) {
							ps->add(p, attr);
						}
						ParticleSystemScene* scene = new ParticleSystemScene(id, n, std::move(ps));
						world->getScenes()->addScene(scene);

						auto presenter = scene->getPresenter();
						presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
						presenter->setBlend(false);
					}

					std::cout << "import suceeded." << std::endl;
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
				OpenVDBFileWriter writer;
				const auto isOk = writer.open(filename);
				if (isOk) {
					const auto scenes = world->getScenes()->findScenes(SceneType::ParticleSystemScene);
					for (auto s : scenes) {
						auto ps = static_cast<ParticleSystemScene*>(s);
						const auto& particles = ps->getShape()->getParticles();
						std::vector<Vector3dd> positions;
						for (auto p : particles) {
							positions.push_back(p->getPosition());
						}
						writer.write(s->getName(), positions);
					}
					std::cout << "export succeded." << std::endl;
				}
				else {
					std::cout << "export failed." << std::endl;
				}
			}
		}

		ImGui::EndMenu();
	}
	//ImGui::EndMenuBar();

}