#include "SceneShader.h"

#include "../Graphics/Camera.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShader::SceneShader() :
	showOffScreen(false),
	camera(new Camera(
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		Vector3df(0, 0, 1),
		1.0f, 10.0f)),
	scene("Scene"),
	IShaderScene("SceneShader"),
	objectRenderer("ObjectRenderer")
{
	//addChild(&renderer);
	addChild(&objectRenderer);
	//addChild(&parentIdRenderer);
	//addChild(&childIdRenderer);
}

bool SceneShader::build(GLObjectFactory& factory)
{
	if (!objectRenderer.build(factory)) {
		return false;
	}
	if (!parentIdRenderer.build(factory)) {
		return false;
	}
	if (!childIdRenderer.build(factory)) {
		return false;
	}

	if (!renderer.build(factory)) {
		return false;
	}

	return true;
}

void SceneShader::render()
{
	objectRenderer.setBuffer(camera.get(), scene.screen);
	objectRenderer.render();
	parentIdRenderer.render(camera.get(), scene.parentId);
	childIdRenderer.render(camera.get(), scene.childId);
}


void SceneShader::render(const int width, const int height)
{
	render();
	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	if (showOffScreen) {
		renderer.render(*objectIdRenderer.getTexture());// *tex);
	}
	else {
		renderer.render(*tex);
	}
	*/
	auto texture = objectRenderer.getTexture();
	renderer.render(texture);
}