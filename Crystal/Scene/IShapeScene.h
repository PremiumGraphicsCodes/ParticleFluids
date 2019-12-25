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
		shape(shape),
		matrix(Math::Identity())
	{}

	IShapeScene(const int id, const std::string& name, Shape::IShape* shape) :
		IScene(id, name),
		shape(shape),
		matrix(Math::Identity())
	{}

	virtual ~IShapeScene() {};

	virtual void translate(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;

	virtual Math::Vector3dd getPosition(const int index) const = 0;

	virtual IShapeScene* clone() const = 0;

	Shape::IShape* getShape() { return shape; }

	void setMatrix(const Math::Matrix4dd& matrix) { this->matrix = matrix; }

	Math::Matrix4dd getMatrix() const { return matrix; }

	/*
	virtual Math::Box3d getBoundingBox() const = 0;

	virtual std::list<Math::Vector3dd> getAllVertices() const = 0;
	*/
private:
	Shape::IShape* shape;
	Math::Matrix4dd matrix;
};
	}
}