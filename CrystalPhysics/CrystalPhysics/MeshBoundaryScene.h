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

class MeshBoundaryScene : public Scene::IScene
{
public:
	MeshBoundaryScene(const int id, const std::string& name);

	~MeshBoundaryScene();

	void clear() { delete mesh; }

	void build(const Shape::PolygonMesh& mesh, const double divideLength);

	static constexpr auto Type = "MeshBoundaryScene";

	Scene::SceneType getType() const { return Type; }

	Scene::IPresenter* getPresenter();

	//void add(const Math::Box3d& box) { boxes.push_back(box); }

	Math::Box3d getBoundingBox() const override;

	//std::list<Math::Box3d> getBoxes() const { return boxes; }

	void setMesh(Shape::PolygonMesh* mesh);

	Shape::PolygonMesh* getMesh() { return mesh; }

private:
	Shape::PolygonMesh* mesh;
	std::vector<Shape::Particle<BoundaryAttr>> positionWithNormal;
	std::unique_ptr<MeshBoundaryScenePresenter> controller;
};

	}
}
