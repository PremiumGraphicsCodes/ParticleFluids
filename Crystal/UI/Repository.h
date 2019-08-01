#pragma once

#include "../Scene/Scene.h"
#include "../Scene/SceneFactory.h"
#include "../Scene/ViewModel.h"
#include <filesystem>

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class RootScene : private UnCopyable
{
public:
	RootScene();

	~RootScene();

	void init();

	void clear();

	bool importFile(const std::experimental::filesystem::path& filename);

	bool exportFile(const std::experimental::filesystem::path& filePath);

	Scene::Scene* getObjects() { return &objects; }

	Scene::Scene* getItems() { return &items; }

	Scene::SceneFactory* getObjectFactory() { return &objectFactory; }
	
	Scene::SceneFactory* getItemFactory() { return &itemFactory; }

	Scene::ViewModel toViewModel();

	Math::Box3d getBoundingBox() const;

private:	
	Scene::Scene objects;
	Scene::Scene items;

	Scene::SceneFactory objectFactory;
	Scene::SceneFactory itemFactory;
};
	}
}