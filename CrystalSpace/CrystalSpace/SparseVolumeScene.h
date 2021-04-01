#pragma once

#include "../../Crystal/Scene/IScene.h"
#include "SparseVolume.h"
#include "SparseVolumePresenter.h"

#include <memory>

namespace Crystal {
	namespace Space {
		class SparseVolumePresenter;

class SparseVolumeScene : public Scene::IScene
{
public:
	SparseVolumeScene(const int id, const std::string& name, std::unique_ptr<SparseVolume> shape);

	SparseVolume* getShape() const { return shape.get(); }

	Scene::SceneType getType() const { return Scene::SceneType("SparseVolumeScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3d getBoundingBox() const override;


private:
	std::unique_ptr<SparseVolume> shape;
	std::unique_ptr<SparseVolumePresenter> presenter;
};

	}
}