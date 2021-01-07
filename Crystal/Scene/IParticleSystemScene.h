#pragma once

#include "IShapeScene.h"

namespace Crystal {
	namespace Scene {

class IParticleSystemScene : public IShapeScene
{
public:
	IParticleSystemScene(const int id, const std::string& name);

	virtual ~IParticleSystemScene() {}

	virtual std::vector<Math::Vector3dd> getPositions() const = 0;
};
	}
}