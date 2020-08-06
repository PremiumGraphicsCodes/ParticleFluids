#pragma once

#include "../Util/UnCopyable.h"

#include "Scene.h"
#include "ScreenIdShaderScene.h"
#include "SceneIdProvider.h"

#include "SceneShader.h"

#include "CameraScene.h"

#include "../Shader/GLObjectFactory.h"
#include "IAnimator.h"

#include <filesystem>

namespace Crystal {
	namespace Scene {
		class IAnimator;

class World : private UnCopyable
{
public:
	World();

	~World();

	void init();

	void clear();

	void clear(int layer);

	Scene* getScenes() { return scenes[1].get(); }

	Scene* getItems() { return scenes[0].get(); }

	void addScene(int layer, IScene* scene);

	int getNextSceneId() { return sceneIdProvider.getNextId(); }

	Shader::GLObjectFactory* getGLFactory() { return &glFactory; }

	Math::Box3d getBoundingBox() const;

	SceneShader* getRenderer() { return renderer.get(); }

	CameraScene* getCamera() { return camera; }

	std::list<IAnimator*> getAnimations() const { return animations; }

	void addAnimation(IAnimator* a) { this->animations.push_back(a); }

private:
	std::array<std::unique_ptr<Scene>, 2> scenes;
	std::list<IAnimator*> animations;
	CameraScene* camera;

	SceneIdProvider sceneIdProvider;
	Shader::GLObjectFactory glFactory;
	
	std::unique_ptr<SceneShader> renderer;

};
	}
}