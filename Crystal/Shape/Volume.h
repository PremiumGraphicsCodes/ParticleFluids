#pragma once

#include "IShape.h"

#include "Particle.h"

#include "../Math/Box3d.h"

#include "../Math/Matrix3d.h"
#include "../Math/Matrix4d.h"

namespace Crystal {
	namespace Shape {

template<typename T>
class Volume : public IShape
{
public:
	Volume(const Math::Box3d& box, const std::array<size_t, 3>& resolutions) :
		box(box),
		resolutions(resolutions)
	{
		nodes.resize(resolutions[0]);
		for (int i = 0; i < resolutions[0]; ++i) {
			nodes[i].resize(resolutions[1]);
			for (int j = 0; j < resolutions[1]; ++j) {
				nodes[i][j].resize(resolutions[2]);
			}
		}
	}

	/*
	Volume(const int unum, const int vnum, const int wnum)
	{
		build(unum, vnum, wnum);
	}
	*/

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

	Math::Vector3dd getCellPosition(int i, int j, int k) const {
		const auto& length = getCellLength();
		const auto cx = length.x * i;
		const auto cy = length.y * j;
		const auto cz = length.z * k;
		return box.getMin() + length * 0.5 + Math::Vector3dd(cx, cy, cz);
	}

	Math::Vector3dd getCellLength() const {
		const auto& length = box.getLength();
		const auto dx = length.x / static_cast<double>(resolutions[0]);
		const auto dy = length.y / static_cast<double>(resolutions[1]);
		const auto dz = length.z / static_cast<double>(resolutions[2]);
		return Math::Vector3dd(dx, dy, dz);
	}

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
