#pragma once

#include <list>
#include "../Math/Line3d.h"

namespace Crystal {
	namespace Shape {

class WireFrame
{
public:
	explicit WireFrame(const std::vector<Math::Line3dd>& lines) :
		lines(lines)
	{}

	void add(const Math::Line3dd& l) {
		this->lines.push_back(l);
	}

	void move(const Math::Vector3dd& v) {
		for (auto& l : lines) {
			l.move(v);
		}
	}

	std::vector<Math::Line3dd> getLines() const;

	std::vector<Math::Vector3dd> getVertices() const;

	void transform(const Math::Matrix3dd& m) {
		for (auto& l : lines) {
			l.transform(m);
		}
	}

	void transform(const Math::Matrix4dd& m) {
		for (auto& l : lines) {
			l.transform(m);
		}
	}

private:
	std::vector<Math::Line3dd> lines;
};
	}
}