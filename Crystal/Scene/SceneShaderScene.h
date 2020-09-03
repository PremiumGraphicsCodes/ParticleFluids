#pragma once

#include "IShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneShaderScene
{
public:
	void addScene(IShaderScene* scene);

	void addParentIdScene(IShaderScene* scene);

	void addChildIdScene(IShaderScene* scene);

	std::vector<IShaderScene*> getScreenScenes() const { return screenScenes; }

	std::vector<IShaderScene*> getParentIdScenes() const { return parentIdScenes; }

	std::vector<IShaderScene*> getChildIdScenes() const { return childIdScenes; }

private:
	std::vector<IShaderScene*> screenScenes;
	std::vector<IShaderScene*> parentIdScenes;
	std::vector<IShaderScene*> childIdScenes;

};

	}
}