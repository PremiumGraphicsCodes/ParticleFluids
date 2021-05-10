#pragma once

#include "../../Crystal/Scene/IScene.h"
#include "Voxel.h"
#include "SparseVolumePresenter.h"

#include <memory>

namespace Crystal {
	namespace Space {
		//class SparseVolumePresenter;

class VoxelScene : public Scene::IScene
{
public:
	VoxelScene(const int id, const std::string& name, std::unique_ptr<Voxel> shape);

	Voxel* getShape() const { return shape.get(); }

	void resetShape(std::unique_ptr<Voxel> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("VoxelScene"); }

	Scene::IPresenter* getPresenter() {
		return nullptr;
	}//presenter.get(); }

	Math::Box3d getBoundingBox() const override;

private:
	std::unique_ptr<Voxel> shape;
	//std::unique_ptr<SparseVolumePresenter> presenter;
};

	}
}