#pragma once

#include "../../CrystalViewer/Scene/IScene.h"
#include "SparseVolume.h"
#include "SparseVolumePresenter.h"

#include <memory>

namespace Crystal {
	namespace Space {
		class SparseVolumePresenter;

class SparseVolumeScene : public Scene::IScene
{
public:
	SparseVolumeScene(const int id, const std::string& name, std::unique_ptr<SparseVolumed> shape);

	SparseVolumed* getShape() const { return shape.get(); }

	void resetShape(std::unique_ptr<SparseVolumed> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("SparseVolumeScene"); }

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3dd getBoundingBox() const override;

private:
	std::unique_ptr<SparseVolumed> shape;
	std::unique_ptr<SparseVolumePresenter> presenter;
};

	}
}