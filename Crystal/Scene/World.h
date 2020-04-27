#pragma once

#include "../Util/UnCopyable.h"

#include "Scene.h"
#include "ScreenIdShaderScene.h"
#include "SceneIdProvider.h"

#include "SceneShader.h"

#include "CameraScene.h"

#include "../Shader/GLObjectFactory.h"

#include <filesystem>

namespace Crystal {
	namespace Scene {

class World : private UnCopyable
{
public:
	World();

	~World();

	void init();

	void clear();

	void clear(int layer);

	Scene* getObjects() { return scenes[1].get(); }

	Scene* getItems() { return scenes[0].get(); }

	void addScene(int layer, IScene* scene);

	int getNextSceneId() { return sceneIdProvider.getNextId(); }

	Shader::GLObjectFactory* getGLFactory() { return &glFactory; }

	Math::Box3d getBoundingBox() const;

	SceneShader* getRenderer() { return renderer.get(); }

	CameraScene* getCamera() { return camera; }

private:
	std::array<std::unique_ptr<Scene>, 2> scenes;
	CameraScene* camera;

	SceneIdProvider sceneIdProvider;
	Shader::GLObjectFactory glFactory;
	
	std::unique_ptr<SceneShader> renderer;

};
	}
}