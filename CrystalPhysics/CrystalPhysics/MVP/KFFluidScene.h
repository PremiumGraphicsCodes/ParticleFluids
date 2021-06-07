#pragma once

#include "IKFFluidScene.h"

namespace Crystal {
	namespace Physics {

class KFFluidScene : public IKFFluidScene
{
public:
	KFFluidScene(const int id, const std::string& name);

	~KFFluidScene() = default;

	static constexpr auto Type = "KFFluid";

	Scene::SceneType getType() const { return Type; }

	bool isBoundary() const { return isBoundary_; }

	void setBoundary(const bool isBoundary_) { this->isBoundary_ = isBoundary_; }

private:
	bool isBoundary_;
};


	}
}
