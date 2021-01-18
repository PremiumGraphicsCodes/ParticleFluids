#pragma once

#include "../../Crystal/Scene/IScene.h"

namespace Crystal {
	namespace Physics {
		class CSGBoundaryScenePresenter;

class CSGBoundaryScene : public Scene::IScene
{
public:
	CSGBoundaryScene(const int id, const std::string& name);

	~CSGBoundaryScene();

	void clear() { boxes.clear(); }

	static constexpr auto Type = "CSGBoundaryScene";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter();

	void add(const Math::Box3d& box) { boxes.push_back(box); }

	Math::Box3d getBoundingBox() const override;

	std::list<Math::Box3d> getBoxes() const { return boxes; }

private:
	std::list<Math::Box3d> boxes;
	std::unique_ptr<CSGBoundaryScenePresenter> controller;
};

	}
}
