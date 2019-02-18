#include "WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrame::move(const Vector3dd& v)
{
	for (auto& l : lines) {
		l.move(v);
	}
}

void WireFrame::transform(const Matrix3dd& m)
{
	for (auto& l : lines) {
		l.transform(m);
	}
}

void WireFrame::transform(const Matrix4dd& m)
{
	for (auto& l : lines) {
		l.transform(m);
	}
}

std::vector<Line3dd> WireFrame::getLines() const
{
	return lines;
}

std::vector<Vector3dd> WireFrame::getVertices() const
{
	if (lines.empty()) {
		return std::vector<Vector3dd>();
	}

	std::vector<Vector3dd> vertices;
	for (const auto& l : lines) {
		vertices.push_back(l.getStart());
	}
	vertices.push_back(lines.back().getEnd());
	return vertices;
}
