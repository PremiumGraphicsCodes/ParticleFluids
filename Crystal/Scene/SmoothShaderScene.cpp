#include "SmoothShaderScene.h"
#include "CameraShaderScene.h"

#include "../Shader/SmoothRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Scene;

SmoothShaderScene::SmoothShaderScene(const std::string& name) :
	IShaderScene(name),
	shader(nullptr)
{}

void SmoothBuffer::addVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord, const int materialId)
{
	positions.add(position);
	normals.add(normal);
	texCoords.add(texCoord);
	materialIds.add(materialId);
}

bool SmoothShaderScene::build(GLObjectFactory& glFactory)
{
	position.build();
	normal.build();
	texCoord.build();
	materialId.build();
	return true;
}

void SmoothShaderScene::release(GLObjectFactory& glFactory)
{
	position.release();
	normal.release();
	texCoord.release();
	materialId.release();
}

void SmoothShaderScene::send(const SmoothBuffer& buffer)
{
	position.send(buffer.getPositions().get());
	normal.send(buffer.getNormals().get());
	texCoord.send(buffer.getTexCoords().get());
	materialId.send(buffer.getMaterialIds().get());

	count = buffer.getPositions().get().size() / 3;
	matrix = buffer.getMatrix();
}

void SmoothShaderScene::render(const Graphics::Camera& camera)
{
	rBuffer.modelViewMatrix = camera.getModelViewMatrix();
	rBuffer.projectionMatrix = camera.getProjectionMatrix();
	shader->render(rBuffer);
}