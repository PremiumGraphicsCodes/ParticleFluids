#pragma once

#include "../Util/UnCopyable.h"
#include "IScene.h"

namespace Crystal {
	namespace Scene {

class Scene : public IScene
{
public:
	Scene(const int id, const std::string& name);

	~Scene();

	Math::Box3d getBoundingBox() const;

	virtual SceneType getType() const { return SceneType::Root; }

	IPresenter* getPresenter() override { return nullptr; }
private:
};
	}
}