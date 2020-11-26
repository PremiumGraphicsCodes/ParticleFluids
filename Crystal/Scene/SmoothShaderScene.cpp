#include "SmoothShaderScene.h"

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
	rBuffer.position.build();
	rBuffer.normal.build();
	rBuffer.texCoord.build();
	rBuffer.materialId.build();
	return true;
}

void SmoothShaderScene::release(GLObjectFactory& glFactory)
{
	rBuffer.position.release();
	rBuffer.normal.release();
	rBuffer.texCoord.release();
	rBuffer.materialId.release();
}

void SmoothShaderScene::send(const SmoothBuffer& buffer)
{
	rBuffer.position.send(buffer.getPositions().get());
	rBuffer.normal.send(buffer.getNormals().get());
	rBuffer.texCoord.send(buffer.getTexCoords().get());
	rBuffer.materialId.send(buffer.getMaterialIds().get());

	rBuffer.count = static_cast<int>( buffer.getPositions().get().size() / 3 );
	rBuffer.matrix = buffer.getMatrix();
}

void SmoothShaderScene::render(const Graphics::Camera& camera)
{
	rBuffer.modelViewMatrix = camera.getModelViewMatrix();
	rBuffer.projectionMatrix = camera.getProjectionMatrix();
	shader->render(rBuffer);
}