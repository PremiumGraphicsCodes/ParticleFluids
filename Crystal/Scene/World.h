#pragma once

#include "../Util/UnCopyable.h"

#include "Scene.h"
#include "SceneFactory.h"
#include "ViewModel.h"

#include "Renderer.h"

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

	Scene* getObjects() { return scenes[1].get(); }

	Scene* getItems() { return scenes[0].get(); }

	SceneFactory* getObjectFactory() { return &objectFactory; }

	SceneFactory* getItemFactory() { return &itemFactory; }

	//ViewModel toViewModel();

	void updateViewModel();

	ViewModel getViewModel() const { return viewModel; }

	Math::Box3d getBoundingBox() const;

	UI::Renderer* getRenderer() { return renderer.get(); }

private:
	std::array<std::unique_ptr<Scene>, 2> scenes;
	ViewModel viewModel;

	SceneFactory objectFactory;
	SceneFactory itemFactory;

	std::unique_ptr<UI::Renderer> renderer;

};
	}
}