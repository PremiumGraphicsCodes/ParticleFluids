#pragma once

#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Shape/PolygonMesh.h"

#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Scene/ParticleSystemScene.h"

namespace Crystal {
	namespace Physics {
		class MeshBoundaryScenePresenter;

		class BoundaryAttr : public Shape::IParticleAttribute
		{
		public:
			explicit BoundaryAttr(Math::Vector3dd normal) :
				normal(normal)
			{
			}

			Math::Vector3dd normal;
		};

		using BoundaryMeshParticle = Shape::Particle<BoundaryAttr>;

class MeshBoundaryScene : public Scene::IScene
{
public:
	MeshBoundaryScene(const int id, const std::string& name);

	~MeshBoundaryScene();

	void clear() { delete mesh; }

	void build(Shape::PolygonMesh* mesh, const double divideLength);

	static constexpr auto Type = "MeshBoundaryScene";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter();

	Math::Box3d getBoundingBox() const override;

	Shape::PolygonMesh* getMesh() { return mesh; }
	
	std::vector<Shape::Particle<BoundaryAttr>*> getParticles() const { return positionWithNormal; }

	double getRadius() const { return divideLength; }

private:
	Shape::PolygonMesh* mesh;
	double divideLength;
	std::vector<Shape::Particle<BoundaryAttr>*> positionWithNormal;
	std::unique_ptr<MeshBoundaryScenePresenter> controller;
};

	}
}
