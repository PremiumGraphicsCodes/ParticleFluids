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
	scene("Scene"),
	objectRenderer(new ShaderRepository("ObjectRenderer")),
	parentIdRenderer(new ScreenIdShader("ParentIdRenderer")),
	childIdRenderer(new ScreenIdShader("ChildIdRenderer")),
	target(RenderTarget::Shaded)
{
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
	objectRenderer->setBuffer(scene.screen);
	objectRenderer->render();
	parentIdRenderer->setBuffer(scene.parentId);
	parentIdRenderer->render();
	childIdRenderer->setBuffer(scene.childId);
	childIdRenderer->render();
}

void SceneShader::render(const int width, const int height)
{
	render();
	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (target) {
	case RenderTarget::Shaded:
	{
		auto texture = objectRenderer->getTextureScene()->getTextureObject();
		renderer.render(*texture);
		break;
	}
	case RenderTarget::ParentId:
	{
		auto texture = parentIdRenderer->getTextureScene()->getTextureObject();
		renderer.render(*texture);
		break;
	}
	case RenderTarget::ChildId:
	{
		auto texture = childIdRenderer->getTextureScene()->getTextureObject();
		renderer.render(*texture);
		break;
	}
	default:
		assert(false);
	}
}