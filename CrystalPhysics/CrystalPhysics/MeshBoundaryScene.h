#pragma once

#include "../../Crystal/Scene/IScene.h"
#include "../../Crystal/Shape/PolygonMesh.h"

namespace Crystal {
	namespace Physics {
		class MeshBoundaryScenePresenter;

class MeshBoundaryScene : public Scene::IScene
{
public:
	MeshBoundaryScene(const int id, const std::string& name);

	~MeshBoundaryScene();

	void clear() { delete mesh; }

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
	std::unique_ptr<MeshBoundaryScenePresenter> controller;
};

	}
}
