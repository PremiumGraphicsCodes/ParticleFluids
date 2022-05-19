#include "FileMenu.h"

#include "CrystalScene/AppBase/MenuItem.h"
#include "CrystalScene/AppBase/FileOpenMenu.h"
#include "CrystalScene/AppBase/FileSaveMenu.h"

#include "FSProjFileWriter.h"

using namespace PG::FS;
using namespace Crystal::Scene;
using namespace Crystal::UI;

FileMenu::FileMenu(const std::string& name, World* world, Canvas* canvas, MainModel* model) :
	IMenu(name, world, canvas),
	model(model)
{
	add(new MenuItem("Open", [=] { onOpen(); }));

	add(new MenuItem("Save", [=] { onSave(); }));
}

void FileMenu::onOpen()
{
	FileOpenMenu view("");
	view.addFilter("*.fsproj");
	view.show();
	const auto& filename = view.getFileName();
	if (!filename.empty()) {
		/*
		FileImportCommand command;
		command.setArg(Fil::FilePathLabel, std::string(filename));
		bool isOk = command.execute(model);
		if (!isOk) {
			std::cout << "import failed." << std::endl;
		}
		else {
			const int newId = std::any_cast<int>(command.getResult(FileImportLabels::NewIdLabel));
			auto scene = model->getScenes()->findSceneById<Crystal::Scene::IScene*>(newId);
			auto presenter = scene->getPresenter();
			presenter->createView(getWorld()->getRenderer(), *getWorld()->getGLFactory());
//					scene->getParent()->se
				}
				*/
	}

}

void FileMenu::onSave()
{
	FileSaveMenu view("");
	view.addFilter("*.fsproj");
	view.show();
	const auto filename = view.getFileName();
	if (!filename.empty()) {
		FSProjFileWriter writer;
		writer.write(model, filename);
	}
}