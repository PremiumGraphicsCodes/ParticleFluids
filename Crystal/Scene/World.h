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

	void addScene(int layer, IScene* scene);

	SceneFactory* getSceneFactory() { return &sceneFactory; }

	//ViewModel toViewModel();

	void updateViewModel();

	ViewModel getViewModel() const { return viewModel; }

	Math::Box3d getBoundingBox() const;

	UI::Renderer* getRenderer() { return renderer.get(); }

private:
	std::array<std::unique_ptr<Scene>, 2> scenes;
	ViewModel viewModel;

	SceneFactory sceneFactory;

	std::unique_ptr<UI::Renderer> renderer;

};
	}
}