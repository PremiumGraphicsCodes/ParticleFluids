#include "MaterialShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;

MaterialShaderScene::MaterialShaderScene(const std::string& name) :
	IShaderScene(name)
{

}

bool MaterialShaderScene::build(Shader::GLObjectFactory& glFactory)
{
	return true;
}

void MaterialShaderScene::send(const Graphics::Material& buffer)
{

}
/*
void release(Shader::GLObjectFactory& glFactory) override;

void render(const Graphics::Camera& camera) override;
*/