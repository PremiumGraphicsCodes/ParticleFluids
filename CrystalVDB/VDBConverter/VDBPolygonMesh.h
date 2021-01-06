#pragma once

#include "../../Crystal/Math/Vector3d.h"

#include "../../Crystal/Scene/IShapeScene.h"

#include "VDBPolygonMeshPresenter.h"

#include <memory>

namespace Crystal {
	namespace VDB {
		class PolygonMeshImpl;

class VDBPolygonMesh : public Scene::IShapeScene
{
public:
	struct TriangleFace
	{
		std::array<unsigned int, 3> indices;
		Math::Vector3df normal;
	};

	struct QuadFace
	{
		std::array<unsigned int, 4> indices;
		Math::Vector3df normal;
	};

	VDBPolygonMesh();

	VDBPolygonMesh(const int id, const std::string& name);

	~VDBPolygonMesh();

	void addVertex(const Math::Vector3df& position);

	Math::Vector3df getVertex(const int index);

	std::vector<Math::Vector3df> getVerticesf() const;

	std::vector<Math::Vector3dd> getVerticesd() const;

	void addTriangle(const std::array<int, 3>& indices);

	std::vector<TriangleFace> getTriangles() const;

	void addQuad(const std::array<int, 4>& indices);

	std::vector<QuadFace> getQuads() const;

	void translate(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

	Scene::IPresenter* getPresenter() { return presenter.get(); }

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Math::Box3d getBoundingBox() const override;

	PolygonMeshImpl* getImpl() const { return impl.get(); }

private:
	std::unique_ptr<PolygonMeshImpl> impl;
	std::unique_ptr<VDBPolygonMeshPresenter> presenter;
};

	}
}