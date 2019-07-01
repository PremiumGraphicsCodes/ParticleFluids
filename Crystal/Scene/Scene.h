#pragma once

#include "../Util/UnCopyable.h"
#include "IScene.h"
#include "SceneFactory.h"

namespace Crystal {
	namespace Model {

class Scene : public IScene
{
public:
	Scene();

	~Scene();

	SceneFactory* getFactory() { return &factory; }

	Math::Box3d getBoundingBox() const;

	virtual bool isNull() const override { return false; }

	virtual SceneType getType() const { return SceneType::Root; }

	virtual void onClear() override;

	void addViewModel(UI::SceneViewModel& viewModel) override;

	void addViewModel(UI::SceneIdViewModel& viewModel) override;

private:
	SceneFactory factory;
};
	}
}