#pragma once

#include <map>
#include "Vertex.h"
#include "HalfEdge.h"
#include <array>

namespace Crystal {
	namespace Math {
		class Triangle3d;
	}
	namespace Shape {

//class Vertex;
//class HalfEdge;

class Face
{
public:
	Face(Vertex* v1, Vertex* v2, Vertex* v3, const int id = -1);

	Vertex* find(Vertex* v);

	Vertex* getV1() const { return v1; }

	Vertex* getV2() const { return v2; }

	Vertex* getV3() const { return v3; }

	//Math::Point3d<float> getCenterPoint() const;

	Math::Vector3dd getNormal() const;

	//Math::Orientation getOrientation(const Math::Vector3df& pos) const;

	std::array< Vertex*, 3 > getVertices() const;

	bool has(Vertex* v) const;

	float getArea() const;

	int getId() const { return id; }

	void changeId(const int id) { this->id = id; }

	bool isDegenerated(const float area) const;

	void reverse();

	Math::Triangle3d toTriangle() const;

private:
	Vertex* v1;
	Vertex* v2;
	Vertex* v3;
	int id;
};

	}
}