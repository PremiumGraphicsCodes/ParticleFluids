#pragma once

#include "../Util/UnCopyable.h"

#include "Scene.h"
#include "SceneFactory.h"
#include "RootShaderScene.h"
#include "ViewModel.h"

#include <filesystem>

namespace Crystal {
	namespace Scene {

class World : private UnCopyable
{
public:
	World();

	~World();

	void init();

	void clear();

	bool importFile(const std::experimental::filesystem::path& filename);

	bool exportFile(const std::experimental::filesystem::path& filePath);

	Scene* getObjects() { return &objects; }

	Scene* getItems() { return &items; }

	SceneFactory* getObjectFactory() { return &objectFactory; }

	SceneFactory* getItemFactory() { return &itemFactory; }

	RootShaderScene* getShaders() { return &shaders; }

	//ViewModel toViewModel();

	void updateViewModel();

	ViewModel getViewModel() const { return viewModel; }

	Math::Box3d getBoundingBox() const;

private:
	Scene objects;
	Scene items;
	RootShaderScene shaders;
	ViewModel viewModel;

	SceneFactory objectFactory;
	SceneFactory itemFactory;
};
	}
}