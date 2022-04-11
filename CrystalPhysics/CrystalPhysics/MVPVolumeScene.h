#pragma once

#include "CrystalSpace/CrystalSpace/SparseVolumeScene.h"


namespace Crystal {
	namespace Physics {
		//		class KFFluidScenePresenter;

class MVPVolumeScene : public Scene::IScene
{
public:
	MVPVolumeScene(const int id, const std::string& name, std::unique_ptr<Space::SparseVolumef> shape);

	virtual ~MVPVolumeScene();

	Space::SparseVolumef* getShape() const { return shape.get(); }

	void resetShape(std::unique_ptr<SparseVolumef> shape) { this->shape = std::move(shape); }

	Scene::SceneType getType() const { return Scene::SceneType("MVPVolumeScene"); }

	/*
	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Math::Box3dd getBoundingBox() const override;
	*/

	Scene::IPresenter* getPresenter() {
		return nullptr;
	}//controller.get(); }


private:
	//std::unique_ptr<MVPFluidScenePresenter> controller;
	std::unique_ptr<Space::SparseVolumef> shape;
	//float pressureCoe;
	//float viscosityCoe;
};


	}
}