#pragma once

//#include "../Shape/Volume.h"

//#include "VolumePresenter.h"

#include "../../Crystal/Scene/IScene.h"

#include "../../Crystal/Shape/IParticle.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Space {
		//class VolumePresenter;

class SparseVolumeNode : public Shape::IParticle
{
public:
	explicit SparseVolumeNode(const Math::Vector3dd& position) :
		position(position)
	{}

	Math::Vector3dd getPosition() const override { return position; }

private:
	Math::Vector3dd position;
	//std::array<int,3> index;
};

class SparseVolumeScene : public Scene::IScene
{
public:
	SparseVolumeScene(const int id, const std::string& name, const Math::Box3d& bb);


	//virtual IShapeScene* clone() const = 0;

	//Math::Box3d getBoundingBox() const { return shape->getBoundingBox(); }

	//Shape::Volume<float>* getShape() const { return shape.get(); }

	Scene::SceneType getType() const { return Scene::SceneType("SparseVolumeScene"); }

	//IPresenter* getPresenter() { return presenter.get(); }

	//std::vector<Shape::Particle<double>> toParticles() const;

	//void createNode(const std::array<int, 3>& index);

private:
	std::map< std::array<int,3>, SparseVolumeNode*> nodes;
	Math::Box3d boundingBox;
	//std::unique_ptr<Shape::Volume<float>> shape;
	//std::unique_ptr<VolumePresenter> presenter;
};

	}
}