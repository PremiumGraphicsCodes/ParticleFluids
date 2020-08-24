#include "PMToWFPresenter.h"

#include "PolygonMeshScene.h"

#include "SceneShader.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;

PMToWFPresenter::PMToWFPresenter(PolygonMeshScene* model) :
	model(model),
	view(nullptr)
{
}

void PMToWFPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();
	const auto& matrix = model->getMatrix();

	for (auto child : model->getChildren()) {
		auto scene = static_cast<FaceGroupScene*>(child);

		auto faces = scene->getFaces();
		{
			LineBuffer buffer;
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
					buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
				}
			}
			LineShaderScene* glBuffer = new LineShaderScene("");
			glBuffer->setShader(sceneShader->getObjectRenderer()->getWireShader());
			glBuffer->build(glFactory);
			glBuffer->send(buffer);
			sceneShader->getScene()->screen.add(glBuffer);
		}
	}
}

void PMToWFPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void PMToWFPresenter::updateScreenView()
{

}

void PMToWFPresenter::updateParentIdView()
{

}

void PMToWFPresenter::updateChildIdView()
{

}
