#pragma once

#include "IScene.h"

#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Scene {

class ITransformScene : public IScene
{
public:
	explicit ITransformScene(const int id) :
		IScene(id)
	{}

	ITransformScene(const int id, const std::string& name) :
		IScene(id, name)
	{}

	virtual ~ITransformScene() {};

	virtual Math::Matrix4dd getMatrix() const = 0;

private:
};
	}
}