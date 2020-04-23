#include "PolygonMeshController.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Scene;
using namespace Crystal::Shader;

PolygonMeshController::PolygonMeshController(PolygonMeshScene* model) :
	model(model),
	view(nullptr)
{
}

void PolygonMeshController::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = model->getMatrix();

	for (auto child : model->getChildren()) {
		int materialId = 0;
		auto scene = static_cast<FaceGroupScene*>(child);
		/*
		if (scene->getMaterial() != nullptr) {
			materialId = scene->getMaterial()->getMaterialId();
		}
		*/

		auto faces = scene->getFaces();
		{
			SmoothBuffer buffer;
			buffer.setMatrix(matrix);
			for (const auto& f : faces) {
				const auto& vIds = f.getVertexIds();
				for (const auto vId : vIds) {
					const auto& v = vs[vId];
					const auto& p = ps[v.positionId];
					const auto& n = ns[v.normalId];
					Math::Vector2df texCoord(0, 0);
					if (v.texCoordId != -1) {
						texCoord = tcs[v.texCoordId];
					}
					buffer.addVertex(p, n, texCoord, materialId);
				}
			}
			SmoothShaderScene* glBuffer = new SmoothShaderScene("");
			glBuffer->setShader(sceneShader->getObjectRenderer()->getSmoothShader());
			glBuffer->build(glFactory);
			glBuffer->send(buffer);
			sceneShader->getScene()->screen.add(glBuffer);
		}
	}
}

void PolygonMeshController::updateView()
{

}