#include "SmoothShaderScene.h"

#include "../Shader/SmoothRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
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

void SmoothShaderScene::setMaterialBuffer(MaterialShaderScene* buffer)
{
	this->materialScene = buffer;
	buffer->addParent(this);
}

void SmoothShaderScene::sendMaterial(const int index, const Material& material)
{
	shader->sendMaterial(index, material);
}

void SmoothShaderScene::sendAllMaterials()
{
	const auto& materials = this->materialScene->getMaterials();
	for (auto i = 0; i < materials.size(); ++i) {
		shader->sendMaterial(i, materials[i]);
	}
}

void SmoothShaderScene::setLightBuffer(LightShaderScene* buffer)
{
	this->lightScene = buffer;
	buffer->addParent(this);
}

void SmoothShaderScene::sendLight(const int index, const PointLight& light)
{
	shader->sendLight(index, light);
}

void SmoothShaderScene::sendAllLights()
{
	const auto& lights = this->lightScene->getLights();
	for (auto i = 0; i < lights.size(); ++i) {
		shader->sendLight(i, lights[i]);
	}
}

void SmoothShaderScene::setTexture(TextureShaderScene* buffer)
{
	this->textureScene = buffer;
	buffer->addParent(this);
}

void SmoothShaderScene::sendTexture(const int index, const Shader::TextureObject& texture)
{
	shader->sendTexture(index, texture);
}

void SmoothShaderScene::sendAllTextures()
{
	const auto& textures = this->textureScene->getTextures();
	for (auto i = 0; i < textures.size(); ++i) {
		shader->sendTexture(i, *textures[i]);
	}
}

void SmoothShaderScene::render(const Graphics::Camera& camera)
{
	rBuffer.modelViewMatrix = camera.getModelViewMatrix();
	rBuffer.projectionMatrix = camera.getProjectionMatrix();
	shader->render(rBuffer);
}