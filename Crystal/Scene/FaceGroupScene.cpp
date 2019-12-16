#include "FaceGroupScene.h"

#include "SmoothRenderer.h"

#include "SceneViewModel.h"

#include "PolygonMeshScene.h"

using namespace Crystal::Scene;

FaceGroupScene::FaceGroupScene(const int id, const std::string& name) :
	IScene(id, name),
	materialId(0),
	faces({})
{}

void FaceGroupScene::setMaterialName(const std::string& name)
{
	this->materialName = name;
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
	const auto& ns = shape->getNormals();
	{
		SmoothTriangleBuffer buffer;
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				const auto& v = vs[vId];
				const auto& p = ps[v.positionId];
				const auto& n = ns[v.normalId];
				Math::Vector2df texCoord(0, 0);
				/*
				if (v.texCoordId != -1) {
					texCoord = tcs[v.texCoordId];
				}
				*/
				buffer.addVertex(p, n, texCoord, f.materialId);
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
