#include "ShaderScene.h"

#include "../Graphics/Camera.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

ShaderScene::ShaderScene() :
	showOffScreen(false),
	camera(new Camera(
		Vector3df(0, 0, 0),
		Vector3df(0, 0, -10.0),
		Vector3df(0, 0, 1),
		1.0f, 10.0f))
{

}

bool ShaderScene::build(GLObjectFactory& factory)
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

void ShaderScene::render(const int width, const int height)
{
	objectRenderer.setBuffer(camera.get(), buffer.screen);
	objectRenderer.render();
	parentIdRenderer.render(camera.get(), buffer.parentId);
	childIdRenderer.render(camera.get(), buffer.childId);

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