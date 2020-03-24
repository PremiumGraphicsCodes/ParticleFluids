#include "FaceGroupScene.h"
#include "SmoothShaderScene.h"

#include "PolygonMeshScene.h"
#include "TextureScene.h"

#include "MaterialScene.h"

#include "ScreenShaderScene.h"

using namespace Crystal::Shader;
using namespace Crystal::Scene;

FaceGroupScene::FaceGroupScene(const int id, const std::string& name, PolygonMeshScene* polygonMesh) :
	IScene(id, name),
	material(nullptr),
	faces({}),
	polygonMesh(polygonMesh)
{}

void FaceGroupScene::setMaterial(MaterialScene* material)
{
	this->material = material;
}