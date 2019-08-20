#pragma once

#include "../Shader/TextureObject.h"
#include "../Shader/OnScreenRenderer.h"

#include "SceneRenderer.h"
#include "SceneIdRenderer.h"

#include "../Scene/ViewModel.h"

#include "../Util/UnCopyable.h"
#include "../Scene/IShaderScene.h"
#include "TextureScene.h"

namespace Crystal {
	namespace UI {

class Renderer : private UnCopyable
{
public:
	explicit Renderer(Graphics::ICamera* camera);

	~Renderer() {}

	bool build(Scene::IScene* scene, Scene::SceneFactory* factory, Scene::IShaderScene* sscene);

	void render(const int width, const int height, Scene::IShaderScene* scene, const Scene::ViewModel& vm);

	SceneRenderer* getObjectRenderer() { return &objectRenderer; }

	SceneIdRenderer* getObjectIdRenderer() { return &objectIdRenderer; }

	void setShowOffScreen(const bool b) { this->showOffScreen = b; }

private:
	Shader::TextureObject texture;
	Shader::OnScreenRenderer renderer;
	SceneRenderer objectRenderer;
	SceneIdRenderer objectIdRenderer;
	Scene::TextureScene smoothTex;
	Scene::TextureScene onScreenTex;
	Scene::TextureScene idTex;

	bool showOffScreen;
};

	}
}