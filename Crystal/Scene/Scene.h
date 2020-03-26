#pragma once

#include "../Util/UnCopyable.h"
#include "IScene.h"
#include "SceneFactory.h"

namespace Crystal {
	namespace Scene {

class Scene : public IScene
{
public:
	Scene(const int id, const std::string& name);

	~Scene();

	Math::Box3d getBoundingBox() const;

	virtual SceneType getType() const { return SceneType::Root; }

	void send(ScreenIdShaderBuffer& parentIdViewModel, ScreenIdShaderBuffer& childIdViewModel) const override;

private:
};
	}
}