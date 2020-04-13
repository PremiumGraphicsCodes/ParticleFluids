#include "MaterialController.h"

#include "MaterialShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

MaterialController::MaterialController(MaterialScene* model) :
	model(model)
{}

void MaterialController::createView(SceneShader* sceneShader, GLObjectFactory& factory)
{

}
