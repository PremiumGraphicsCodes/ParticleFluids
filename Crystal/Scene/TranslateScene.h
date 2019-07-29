#pragma once

#include "ITransformScene.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Scene {

class TranslateScene : public ITransformScene
{
public:
	TranslateScene(const int id, const std::string& name) :
		ITransformScene(id, name)
	{}

	void setTranslate(const Math::Vector3dd& t) { this->translate = t; }

	Math::Vector3dd getTranslate() const { return translate; }

private:
	Math::Vector3dd translate;
};
	}
}