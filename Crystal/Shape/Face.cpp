#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "HalfEdge.h"
#include "../Math/Triangle3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

Face::Face(HalfEdge* e1, HalfEdge* e2, HalfEdge* e3, const int id) :
	id(id)
{
	e1->connect(e2);
	e2->connect(e3);
	e3->connect(e1);
	e1->setFace(this);
	e2->setFace(this);
	e3->setFace(this);
	this->start = (e1);
}

Face::Face(const std::array<HalfEdge*, 3>& edges, const int id) :
	id(id)
{
	edges[0]->setFace(this);
	edges[1]->setFace(this);
	edges[2]->setFace(this);
	this->start = edges[0];
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

std::array< HalfEdge*, 3 > Face::getEdges() const
{
	return{ start, start->getNext(), start->getNext()->getNext() };
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
	const auto& edges = getEdges();
	auto v1 = (edges[0]->getEnd()->getPosition() - edges[0]->getStart()->getPosition());
	auto v2 = (edges[1]->getEnd()->getPosition() - edges[0]->getStart()->getPosition());
	return glm::length( glm::cross( v1, v2) ) / 2.0f;
}

bool Face::isDegenerated(const float area) const
{
	return ::fabs( getArea() ) < area;
}

void Face::reverse()
{
	const auto edges = getEdges();

	/*
	for (auto iter = edges.rbegin(); iter != edges.rend()-1; ++iter) {
	auto e = *(iter);
	auto next = *(iter + 1);
	e->reverse();
	e->connect(next);
	}
	edges.back()->connect(edges.front());
	*/
	edges[2]->reverse();
	edges[1]->reverse();
	edges[0]->reverse();
	edges[2]->connect(edges[1]);
	edges[1]->connect(edges[0]);
	edges[0]->connect(edges[2]);
	this->start = edges.back();
}

Triangle3d Face::toTriangle() const
{
	const auto& v1 = getV1()->getPosition();
	const auto& v2 = getV2()->getPosition();
	const auto& v3 = getV3()->getPosition();
	return Triangle3d({ v1, v2, v3 });
}