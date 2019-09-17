#pragma once

#include <list>
#include "../Math/Line3d.h"
#include "../Shape/IShape.h"

namespace Crystal {
	namespace Shape {

class WireFrame : public IShape
{
public:
	WireFrame() {};

	explicit WireFrame(const std::vector<Math::Line3dd>& lines) :
		lines(lines)
	{}

	void add(const Math::Line3dd& l) {
		this->lines.push_back(l);
	}

	void move(const Math::Vector3dd& v) override;

	void transform(const Math::Matrix3dd& m) override;

	void transform(const Math::Matrix4dd& m) override;

	std::vector<Math::Line3dd> getLines() const;

	std::vector<Math::Vector3dd> getVertices() const;

	Math::Box3d getBoundingBox() const override;

private:
	std::vector<Math::Line3dd> lines;
};
	}
}