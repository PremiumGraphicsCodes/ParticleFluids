#include "VDBPolygonMeshPresenter.h"

#include "VDBPolygonMesh.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/LineShaderScene.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::VDB;

VDBPolygonMeshPresenter::VDBPolygonMeshPresenter(VDBPolygonMesh* model) :
	model(model),
	view(nullptr)
{
}

void VDBPolygonMeshPresenter::createView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	{
		this->view = new LineShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getWireShader());
		this->view->build(glFactory);


		sceneShader->getObjectRenderer()->addScene(this->view);
	}

	updateView();
}

void VDBPolygonMeshPresenter::removeView(SceneShader* sceneShader, GLObjectFactory& glFactory)
{
	this->view->release(glFactory);
	sceneShader->getObjectRenderer()->removeScene(this->view);
	delete this->view;
}

void VDBPolygonMeshPresenter::updateView()
{
	updateScreenView();
	updateParentIdView();
	updateChildIdView();
}

void VDBPolygonMeshPresenter::updateScreenView()
{
	const auto ps = model->getVerticesf();
	LineBuffer buffer;
	for (const auto& p : ps) {
		buffer.addVertex(p, ColorRGBAf(1.0, 1.0, 1.0, 1.0));
	}

	const auto triangles = model->getTriangleFaces();

	for (const auto& tt : triangles) {
		const auto t = tt.indices;
		buffer.addIndex(t[0]);
		buffer.addIndex(t[1]);
		buffer.addIndex(t[1]);
		buffer.addIndex(t[2]);
	}

	const auto quads = model->getQuadFaces();

	for (const auto& qq : quads) {
		const auto q = qq.indices;
		buffer.addIndex(q[0]);
		buffer.addIndex(q[1]);
		buffer.addIndex(q[1]);
		buffer.addIndex(q[2]);
		buffer.addIndex(q[2]);
		buffer.addIndex(q[3]);
	}

	this->view->send(buffer);
}

void VDBPolygonMeshPresenter::updateParentIdView()
{
}

void VDBPolygonMeshPresenter::updateChildIdView()
{

}
