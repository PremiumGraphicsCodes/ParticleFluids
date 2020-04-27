#include "SceneShader.h"

#include "../Graphics/Camera.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShader::SceneShader() :
	IShaderScene("SceneShader"),
	showOffScreen(false),
	camera(new Camera(
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		Vector3df(0, 0, 1),
		1.0f, 10.0f)),
	scene("Scene"),
	objectRenderer(new ScreenShader("ObjectRenderer")),
	parentIdRenderer(new ScreenIdShader("ParentIdRenderer")),
	childIdRenderer(new ScreenIdShader("ChildIdRenderer"))
{
	//addChild(&renderer);
	addChild(objectRenderer);
	addChild(&scene);
	addChild(parentIdRenderer);
	addChild(childIdRenderer);
}

bool SceneShader::build(GLObjectFactory& factory)
{
	if (!objectRenderer->build(factory)) {
		return false;
	}
	if (!parentIdRenderer->build(factory)) {
		return false;
	}
	if (!childIdRenderer->build(factory)) {
		return false;
	}

	if (!renderer.build(factory)) {
		return false;
	}

	return true;
}

void SceneShader::render()
{
	objectRenderer->setBuffer(camera.get(), scene.screen);
	objectRenderer->render();
	parentIdRenderer->render(camera.get(), scene.parentId);
	childIdRenderer->render(camera.get(), scene.childId);
}

void SceneShader::render(const int width, const int height)
{
	render();
	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (showOffScreen) {
		auto texture = parentIdRenderer->getTextureScene()->getTextureObject();
		renderer.render(*texture);
	}
	else {
		auto texture = objectRenderer->getTextureScene()->getTextureObject();
		renderer.render(*texture);
	}
}