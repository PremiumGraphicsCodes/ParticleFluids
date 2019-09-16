#pragma once

#include "../Util/UnCopyable.h"

#include "Scene.h"
#include "SceneFactory.h"
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

	Scene* getObjects() { return &objects; }

	Scene* getItems() { return &items; }

	SceneFactory* getObjectFactory() { return &objectFactory; }

	SceneFactory* getItemFactory() { return &itemFactory; }

	//ViewModel toViewModel();

	void updateViewModel();

	ViewModel getViewModel() const { return viewModel; }

	Math::Box3d getBoundingBox() const;

private:
	Scene objects;
	Scene items;
	ViewModel viewModel;

	SceneFactory objectFactory;
	SceneFactory itemFactory;
};
	}
}