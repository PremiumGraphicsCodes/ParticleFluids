#pragma once

#include "IScene.h"

#include "../Shape/IShape.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Scene {

class IShapeScene : public IScene
{
public:
	explicit IShapeScene(const int id, Shape::IShape* shape) :
		IScene(id),
		shape(shape)
	{}

	IShapeScene(const int id, const std::string& name, Shape::IShape* shape) :
		IScene(id, name),
		shape(shape)
	{}

	virtual ~IShapeScene() {};

	virtual void translate(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;

	Shape::IShape* getShape() { return shape; }

private:
	Shape::IShape* shape;
};
	}
}