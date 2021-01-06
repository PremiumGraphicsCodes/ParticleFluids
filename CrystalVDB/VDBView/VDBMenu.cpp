#include "VDBMenu.h"

//#include "../../CrystalViewer/AppBase/"
#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

#include "../../CrystalViewer/AppBase/imgui.h"
#include "../../CrystalViewer/AppBase/FileOpenMenu.h"
#include "../../CrystalViewer/AppBase/FileSaveMenu.h"

#include "../VDBConverter/VDBFileReader.h"
#include "../VDBConverter/VDBFileWriter.h"

#include "VDBPSBoxView.h"
#include "VDBPMBoxView.h"
#include "VDBVolumeView.h"
#include "PSToVolumeView.h"
#include "VolumeToMeshView.h"
#include "MeshToVolumeView.h"
#include "VolumeToPSView.h"
#include "OBJFileImportView.h"
#include "OBJFileExportView.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBMenu::VDBMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void VDBMenu::onShow()
{
	auto world = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu(n)) {
		if (ImGui::MenuItem("Import")) {
			FileOpenMenu view("");
			view.addFilter("*.vdb");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				VDBFileReader reader;
				const auto isOk = reader.open(filename);
				if (isOk) {
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
						//						presenter->setBlend(false);
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
			FileSaveMenu fileSaveView("Export");
			fileSaveView.addFilter("*.vdb");
			fileSaveView.show();
			const auto& filename = fileSaveView.getFileName();
			if (!filename.empty()) {
				VDBFileWriter writer;
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
	if (ImGui::BeginMenu("VDBPS")) {
		if (ImGui::MenuItem("PSBox")) {
			control->setWindow(new VDBPSBox("PSBox", world, getCanvas()));
		}
		if (ImGui::MenuItem("PSToMesh")) {
			control->setWindow(new PSToVolumeView("PSToVolume", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("VDBPM")) {
		if (ImGui::MenuItem("PMBox")) {
			control->setWindow(new VDBPMBoxView("PMBox", world, getCanvas()));
		}
		if (ImGui::MenuItem("MeshToVolume")) {
			control->setWindow(new MeshToVolumeView("MeshToVolume", world, getCanvas()));
		}
		if (ImGui::MenuItem("OBJImport")) {
			control->setWindow(new OBJFileImportView("OBJImport", world, getCanvas()));
		}
		if (ImGui::MenuItem("OBJExport")) {
			control->setWindow(new OBJFileExportView("OBJExport", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
	if(ImGui::BeginMenu("VDBVolume")){
		if (ImGui::MenuItem("VolumeBox")) {
			control->setWindow(new VDBVolumeView("VDBVolume", world, getCanvas()));
		}
		if (ImGui::MenuItem("VolumeToMesh")) {
			control->setWindow(new VolumeToMeshView("VolumeToMesh", world, getCanvas()));
		}
		if (ImGui::MenuItem("VolumeToPS")) {
			control->setWindow(new VolumeToPSView("VolumeToPS", world, getCanvas()));
		}
		ImGui::EndMenu();
	}
}