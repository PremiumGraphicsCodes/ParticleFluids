#include "SceneShader.h"

#include "../Graphics/Camera.h"

#include "../Shader/GLObjectFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SceneShader::SceneShader() :
	objectRenderer(new ScreenShader("ObjectRenderer")),
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

void SceneShader::render(const Camera& camera)
{
	objectRenderer->render(camera);
	parentIdRenderer->render(camera);
	childIdRenderer->render(camera);
}

void SceneShader::render(const Graphics::Camera& camera, const int width, const int height)
{
	render(camera);
	glViewport(0, 0, width, height);
	//glClearColor(0.0, 0.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (target) {
	case RenderTarget::Shaded:
	{
		auto texture = objectRenderer->getTextureScene();
		renderer.render(*texture);
		break;
	}
	case RenderTarget::ParentId:
	{
		auto texture = parentIdRenderer->getTextureScene();
		renderer.render(*texture);
		break;
	}
	case RenderTarget::ChildId:
	{
		auto texture = childIdRenderer->getTextureScene();
		renderer.render(*texture);
		break;
	}
	default:
		assert(false);
	}
}