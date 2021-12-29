#include "VDBFileMenu.h"

#include "../CrystalVDB/VDBFileReader.h"
#include "../CrystalVDB/VDBFileWriter.h"
#include "../CrystalVDB/VDBParticleSystemScene.h"

#include "CrystalScene/AppBase/imgui.h"

#include "CrystalScene/AppBase/FileOpenMenu.h"
#include "CrystalScene/AppBase/FileSaveMenu.h"

#include "../VDBCommand/VDBFileReadCommand.h"
//#include "../VDBCommand/PublicLabels/VDBFileReadLabels.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBFileMenu::VDBFileMenu(const std::string& name, Scene::World* model, Canvas* canvas, ControlPanel* control) :
	IMenu(name, model, canvas),
	control(control)
{
}

void VDBFileMenu::onShow()
{
	auto world = getWorld();

	const auto& n = name.c_str();
	if (ImGui::BeginMenu("VDBFile")) {
		if (ImGui::MenuItem("Import")) {
			FileOpenMenu view("");
			view.addFilter("*.vdb");
			view.show();
			const auto& filename = view.getFileName();
			if (!filename.empty()) {
				VDBFileReader reader;
				const auto isOk = reader.open(filename);
				if (isOk) {
					VDBFileReadCommand::Args args;
					args.filePath.setValue(filename);
					VDBFileReadCommand command(args);
					const auto isOk = command.execute(world);
					if (isOk) {
						const auto results = command.getResults();
						const auto newIds = std::any_cast<std::vector<int>>(results.newIds.value);
						for (const auto& id : newIds) {
							auto ps = world->getScenes()->findSceneById(id);
							auto presenter = ps->getPresenter();
							presenter->createView(getWorld()->getRenderer());
						}
						std::cout << "import suceeded." << std::endl;
					}
					else {
						std::cout << "import failed." << std::endl;
					}
				}
			}
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
					const auto pointType = SceneType(VDBParticleSystemScene::Type);
					const auto pointScenes = world->getScenes()->findScenes(pointType);
					for (auto s : pointScenes) {
						auto ps = static_cast<VDBParticleSystemScene*>(s);
						const auto& particles = ps->getPositions();
						writer.writePoints(s->getName(), particles);
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
}