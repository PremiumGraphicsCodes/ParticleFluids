#pragma once

#include "IScene.h"

namespace Crystal {
	namespace Model {

class IShapeScene : public IScene
{
public:
	explicit IShapeScene(const int id) :
		IScene(id)
	{}

	IShapeScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	virtual ~IShapeScene() {};

	virtual void move(const Math::Vector3dd& v) = 0;

	virtual void transform(const Math::Matrix3dd& m) = 0;

	virtual void transform(const Math::Matrix4dd& m) = 0;

};
	}
}