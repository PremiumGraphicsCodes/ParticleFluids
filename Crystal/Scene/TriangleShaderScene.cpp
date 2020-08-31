#include "TriangleShaderScene.h"

#include "../Shader/TriangleRenderer.h"
#include "CameraShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

bool TriangleShaderScene::build(GLObjectFactory& glFactory)
{
	sBuffer.position.build();
	sBuffer.color.build();
	return true;
}

void TriangleShaderScene::release(GLObjectFactory& glFactory)
{
	sBuffer.position.release();
	sBuffer.color.release();
}

void TriangleShaderScene::send(const TriangleBuffer& buffer)
{
	sBuffer.position.send(buffer.getPositions().get());
	sBuffer.color.send(buffer.getColors().get());

	sBuffer.indices = buffer.getIndices().get();
}

void TriangleShaderScene::render()
{
	sBuffer.projectionMatrix = camera->getProjectionMatrix();
	sBuffer.modelViewMatrix = camera->getModelViewMatrix();
	shader->render(sBuffer);
}

void TriangleShaderScene::setShader(TriangleRenderer* shader)
{
	this->shader = shader;
}
