#pragma once


namespace Crystal {
	namespace Scene {
		class PolygonMesh;
	}
	namespace Algo {

class BooleanAlgo
{
public:
	void calculateUnion(const Scene::PolygonMesh& lhs, const Scene::PolygonMesh& rhs);

	void calculateDifference(const Scene::PolygonMesh& lhs, const Scene::PolygonMesh& rhs);

	void calculateIntersection(const Scene::PolygonMesh& lhs, const Scene::PolygonMesh& rhs);

	Scene::PolygonMesh* getResult() { return result; }

private:
	Scene::PolygonMesh* result;
};
	}
}