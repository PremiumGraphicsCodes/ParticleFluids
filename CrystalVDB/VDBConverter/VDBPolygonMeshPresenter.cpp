#include "VDBPolygonMeshPresenter.h"

#include "VDBPolygonMesh.h"

#include "../../Crystal/Scene/SceneShader.h"
#include "../../Crystal/Scene/SmoothShaderScene.h"

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
		this->view = new SmoothShaderScene(model->getName());
		this->view->setShader(sceneShader->getObjectRenderer()->getSmoothShader());
		this->view->build(glFactory);

		this->view->setMaterialBuffer(sceneShader->getObjectRenderer()->getMateialScene());
		this->view->sendAllMaterials();
		this->view->sendAllLights();
		this->view->sendAllTextures();

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
	if (!model->isVisible()) {
		this->view->send(SmoothBuffer());
		return;
	}
	const auto vertices = model->getVerticesf();
	const auto vs = model->getTriangles();
	/*
	const auto& shape = model->getShape();
	const auto& vs = shape->getVertices();
	const auto& ps = shape->getPositions();
	const auto& tcs = shape->getTexCoords();
	const auto& ns = shape->getNormals();

	SmoothBuffer buffer;

	auto groups = model->getGroups();
	for (const auto& group : groups) {
		int materialId = 0;//group.material->;

		auto faces = group.faces;
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
	}
	this->view->send(buffer);
	*/
}

void VDBPolygonMeshPresenter::updateParentIdView()
{
}

void VDBPolygonMeshPresenter::updateChildIdView()
{

}
