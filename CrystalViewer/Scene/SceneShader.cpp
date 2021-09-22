#include "SceneShader.h"

#include "Crystal/Graphics/Camera.h"

#include "Crystal/Shader/GLObjectFactory.h"

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

ShaderBuildStatus SceneShader::build(GLObjectFactory& factory)
{
	ShaderBuildStatus status;

	const auto prStatus = objectRenderer->build(factory);
	parentIdRenderer->build(factory);
	childIdRenderer->build(factory);
	const auto rStatus = renderer.build(factory);

	status.add(prStatus);
	//status.add(pIdStatus);
	//status.add(cIdStatus);
	status.add(rStatus);

	return status;
}

void SceneShader::release(GLObjectFactory& factory)
{
	objectRenderer->release(factory);
	parentIdRenderer->release(factory);
	childIdRenderer->release(factory);
	renderer.release(factory);
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
		auto texture = objectRenderer->getTexture();
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