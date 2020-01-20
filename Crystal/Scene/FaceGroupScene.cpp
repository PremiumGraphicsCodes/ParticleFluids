#include "FaceGroupScene.h"

#include "SmoothRenderer.h"

#include "SceneViewModel.h"

#include "PolygonMeshScene.h"
#include "TextureScene.h"

#include "MaterialScene.h"

using namespace Crystal::Scene;

FaceGroupScene::FaceGroupScene(const int id, const std::string& name) :
	IScene(id, name),
	material(nullptr),
	faces({})
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

	PolygonMeshScene* parent = static_cast<PolygonMeshScene*>( getParent() );
	const auto& shape = parent->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = parent->getMatrix();

	int materialId = 0;
	int ambientTexId = 0;
	if (material != nullptr) {
		materialId = material->getMaterialId();
		ambientTexId = material->getMabientTexId();
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
				buffer.addVertex(p, n, texCoord, materialId, ambientTexId, 0);
			}
		}
		viewModel.triangleBuffers.push_back(buffer);
	}
}

/*
void FaceGroupScene::toIdViewModel(SceneIdViewModel& parentIdViewModel, SceneIdViewModel& childIdViewModel) const
{

}
*/
