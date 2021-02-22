#include "VDBPolygonMeshScene.h"

#include "VDBPolygonMeshImpl.h"
#include "Converter.h"

#include "../../Crystal/Shape/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Scene;
using namespace Crystal::VDB;

VDBPolygonMeshScene::VDBPolygonMeshScene() :
	VDBPolygonMeshScene(-1, "")
{
}

VDBPolygonMeshScene::VDBPolygonMeshScene(const int id, const std::string& name) :
	IShapeScene(id, name)
{
	impl = std::make_unique<VDBPolygonMeshImpl>();
	presenter = std::make_unique<VDBPolygonMeshPresenter>(this);
}

VDBPolygonMeshScene::~VDBPolygonMeshScene()
{

}

void VDBPolygonMeshScene::addVertex(const Vector3df& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

Vector3df VDBPolygonMeshScene::getVertex(const int index)
{
	return Converter::fromVDB( impl->points[index] );
}

std::vector<Vector3df> VDBPolygonMeshScene::getVerticesf() const
{
	return Converter::fromVDBf<Vector3df>(impl->points);
}

std::vector<Vector3dd> VDBPolygonMeshScene::getVerticesd() const
{
	return Converter::fromVDBf<Vector3dd>(impl->points);
}

void VDBPolygonMeshScene::addTriangle(const std::array<unsigned int, 3>& indices)
{
	VDBPolygonMeshImpl::TriangleFace triangle;
	triangle.indices = Converter::toVDB( indices );
	//triangle.normal = Converter::toVDB(normal);
	impl->triangles.push_back(triangle);
}

std::vector<VDBPolygonMeshScene::TriangleFace> VDBPolygonMeshScene::getTriangleFaces() const
{
	std::vector<VDBPolygonMeshScene::TriangleFace> faces;
	for (const auto& t : impl->triangles) {
		VDBPolygonMeshScene::TriangleFace face;
		face.indices = Converter::fromVDB(t.indices);
		face.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(face);
	}
	return faces;
}

void VDBPolygonMeshScene::addQuad(const std::array<unsigned int, 4>& indices)
{
	VDBPolygonMeshImpl::QuadFace quad;
	quad.indices = Converter::toVDB(indices);
	//quad.normal = Converter::toVDB(normal);
	impl->quads.push_back(quad);
}

std::vector<VDBPolygonMeshScene::QuadFace> VDBPolygonMeshScene::getQuadFaces() const
{
	std::vector<VDBPolygonMeshScene::QuadFace> faces;
	for (const auto& q : impl->quads) {
		VDBPolygonMeshScene::QuadFace face;
		face.indices = Converter::fromVDB(q.indices);
		face.normal = Converter::fromVDB(q.normal);
		faces.emplace_back(face);
	}
	return faces;
}

std::vector<VDBPolygonMeshScene::Face> VDBPolygonMeshScene::getAllFaces() const
{
	std::vector<VDBPolygonMeshScene::Face> faces;
	for (const auto& t : impl->triangles) {
		VDBPolygonMeshScene::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	for (const auto& t : impl->quads) {
		VDBPolygonMeshScene::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2], t.indices[3] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	return faces;
}

Box3d VDBPolygonMeshScene::getBoundingBox() const
{
	if (impl->points.empty()) {
		return Box3d::createDegeneratedBox();
	}
	auto vertices = this->getVerticesd();

	Math::Box3d box(vertices[0]);
	for (auto v : vertices) {
		box.add(v);
	}
	return box;
}

void VDBPolygonMeshScene::updateNormals()
{
	impl->updateNormals();
}

void VDBPolygonMeshScene::scale(const double scale)
{
	for (auto& p : impl->points) {
		p *= scale;
	}
}
