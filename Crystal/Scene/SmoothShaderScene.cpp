#include "SmoothShaderScene.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;

void SmoothBuffer::addVertex(const Vector3df& position, const Vector3df& normal, const Vector2df& texCoord, const int materialId)
{
	positions.add(position);
	normals.add(normal);
	texCoords.add(texCoord);
	materialIds.add(materialId);
}

void SmoothShaderScene::build()
{
	position.build();
	normal.build();
	texCoord.build();
	materialId.build();
}

void SmoothShaderScene::release()
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
