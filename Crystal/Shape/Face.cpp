#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include "../Math/Triangle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Face::Face(Vertex* v1, Vertex* v2, Vertex* v3, const int id) :
	v1(v1),
	v2(v2),
	v3(v3),
	id(id)
{
}

Vertex* Face::find(Vertex* v)
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	if (f != vertices.end()) {
		return v;
	}
	assert(false);
	return nullptr;
}

Vector3dd Face::getNormal() const
{
	auto vertices = getVertices();
	auto normal = glm::cross((vertices[1]->getPosition() - vertices[0]->getPosition()), (vertices[2]->getPosition() - vertices[0]->getPosition()));
	return glm::normalize( normal );
}

std::array< Vertex*, 3 > Face::getVertices() const
{
	return{ getV1(), getV2(), getV3() };
}

bool Face::has(Vertex* v) const
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	return (f != vertices.end());
}

float Face::getArea() const
{
	auto v1 = (this->v2->getPosition() - this->v1->getPosition());
	auto v2 = (this->v3->getPosition() - this->v1->getPosition());
	return glm::length( glm::cross( v1, v2) ) / 2.0f;
}

bool Face::isDegenerated(const float area) const
{
	return ::fabs( getArea() ) < area;
}

void Face::reverse()
{
	std::swap(v2, v3);
}

Triangle3d Face::toTriangle() const
{
	const auto& v1 = getV1()->getPosition();
	const auto& v2 = getV2()->getPosition();
	const auto& v3 = getV3()->getPosition();
	return Triangle3d({ v1, v2, v3 });
}