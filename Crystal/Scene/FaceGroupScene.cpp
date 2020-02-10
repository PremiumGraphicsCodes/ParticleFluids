#include "FaceGroupScene.h"

#include "SmoothRenderer.h"

#include "SceneViewModel.h"

#include "PolygonMeshScene.h"
#include "TextureScene.h"

#include "MaterialScene.h"

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

void FaceGroupScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	PolygonMeshScene* parent = polygonMesh;
	const auto& shape = parent->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = parent->getMatrix();

	int materialId = 0;
	int ambientTexId = 0;
	int diffuseTexId = 0;
	int specularTexId = 0;
	if (material != nullptr) {
		materialId = material->getMaterialId();
		auto ambientTexture = material->getAmbientTexture();
		if (ambientTexture != nullptr) {
			ambientTexId = ambientTexture->getTextureObject().getHandle();
		}
		auto diffuseTexture = material->getDiffuseTexture();
		if (diffuseTexture != nullptr) {
			diffuseTexId = diffuseTexture->getTextureObject().getHandle();
		}
		auto specularTexture = material->getSpecularTexture();
		if (specularTexture != nullptr) {
			specularTexId = specularTexture->getTextureObject().getHandle();
		}
	}

	{
		SmoothTriangleBuffer buffer;
		buffer.setMatrix(matrix);
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				const auto& v = vs[vId];
				const auto& p = ps[v.positionId];
				const auto& n = ns[v.normalId];
				auto texCoord = tcs[v.texCoordId];
//				Math::Vector2df texCoord(0, 0);
				/*
				if (v.texCoordId != -1) {
				}
				*/
				buffer.addVertex(p, n, texCoord, materialId, ambientTexId, diffuseTexId, specularTexId);
			}
		}
		SmoothRenderer::GLBuffer glBuffer;
		glBuffer.build();
		glBuffer.send(buffer);
		viewModel.triangleBuffers.push_back(glBuffer);
	}
}

/*
void FaceGroupScene::toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{

}
*/
