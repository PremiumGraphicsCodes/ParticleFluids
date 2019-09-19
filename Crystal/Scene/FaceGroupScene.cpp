#include "FaceGroupScene.h"

#include "SmoothRenderer.h"

#include "PolygonMeshScene.h"

using namespace Crystal::Scene;

void FaceGroupScene::toViewModel(SceneViewModel& viewModel) const
{
	if (!isVisible()) {
		return;
	}

	/*
	PolygonMeshScene* parent = static_cast<PolygonMeshScene*>( getParent() );
	const auto& shape = parent->getShape();
	{
		SmoothTriangleBuffer buffer;
		for (const auto& f : faces) {
			const auto& vIds = f.getVertexIds();
			for (const auto vId : vIds) {
				const auto& v = vertices[vId];
				const auto& p = ps[v.positionId];
				const auto& n = ns[v.normalId];
				Math::Vector2df texCoord(0, 0);
				if (v.texCoordId != -1) {
					texCoord = tcs[v.texCoordId];
				}
				buffer.addVertex(p, n, texCoord, 0);
			}
		}
		viewModel.triangleBuffers.push_back(buffer);
	}
	*/
}
