#pragma once

#include "IShapeScene.h"
#include "../Shape/TriangleMesh.h"

namespace Crystal {
	namespace Scene {

class TriangleMeshScene : public IShapeScene
{
public:
	explicit TriangleMeshScene(const int id)
		: IShapeScene(id, nullptr)
	{}

	TriangleMeshScene(const int id, const std::string& name) :
		IShapeScene(id, name, nullptr)
	{}

	void translate(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	Math::Vector3dd getPosition(const int index) const override;

private:
	std::vector<Shape::TriangleFace> faces;
};

	}
}