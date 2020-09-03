#pragma once

#include "ScreenShaderScene.h"
#include "ScreenIdShaderScene.h"

namespace Crystal {
	namespace Scene {

class SceneShaderScene
{
public:
	void setCamera(CameraShaderScene* camera);

	ScreenShaderScene screen;
	ScreenIdShaderScene parentId;
	ScreenIdShaderScene childId;

};

	}
}