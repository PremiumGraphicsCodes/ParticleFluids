#pragma once

#include "IShape.h"

#include "Particle.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

		/*
class IVolume : public IShape
{

};
*/

template<typename T>
class Volume : public IShape
{
public:
	Volume(const Math::Box3d& box, const std::array<size_t, 3>& resolutions);

	~Volume() {
		//clear();
	}

	void move(const Math::Vector3dd& v) override {
		box.translate(v);
	}

	void transform(const Math::Matrix3dd& m) override {

	}

	void transform(const Math::Matrix4dd& m) override {

	}

	Math::Box3d getBoundingBox() const override { return box; }

	std::array<size_t,3> getResolutions() const { return resolutions; }

	Math::Vector3dd getCellPosition(int i, int j, int k) const;

	std::array<size_t, 3> getIndexFromPosition(const Math::Vector3dd& position);

	Math::Vector3dd getCellLength() const;

	T getValue(const int i, const int j, const int k) const { return nodes[i][j][k]; }

	void setValue(const int i, const int j, const int k, const T value) { nodes[i][j][k] = value; }
	/*
	const double getDU() const { return box.getLength().x / static_cast<double>(unum); }

	const double getDV() const { return box.getLength().y / static_cast<double>(vnum); }

	const double getDW() const { return box.getLength().z / static_cast<double>(wnum); }
	*/

private:
	Math::Box3d box;
	std::array<size_t,3> resolutions;
	std::vector<std::vector<std::vector<T>>> nodes;
};

	}
}
