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
	explicit Volume(const Math::Box3d& box) :
		box(box)
	{}

	/*
	Volume(const int unum, const int vnum, const int wnum)
	{
		build(unum, vnum, wnum);
	}
	*/

	~Volume() {
		//clear();
	}

	void build(const int unum, const int vnum, const int wnum)
	{
		this->unum = unum;
		this->vnum = vnum;
		this->wnum = wnum;

		nodes.resize(unum);
		for (int i = 0; i < unum; ++i) {
			nodes[i].resize(vnum);
			for (int j = 0; j < vnum; ++j) {
				nodes[i][j].resize(wnum);
				/*
				for (int k = 0; k < wnum; ++k) {
					nodes[i][j][k] = new Particle<T>();
				}
				*/
			}
		}
	}

	void move(const Math::Vector3dd& v) override {
		box.translate(v);
	}

	void transform(const Math::Matrix3dd& m) override {

	}

	void transform(const Math::Matrix4dd& m) override {

	}

	Math::Box3d getBoundingBox() const override { return box; }

	size_t getUNum() const { return unum; }

	size_t getVNum() const { return vnum; }

	size_t getWNum() const { return wnum; }

	Math::Vector3dd getCellPosition(int i, int j, int k) const {
		const auto& length = getCellLength();
		const auto cx = length.x * i;
		const auto cy = length.y * j;
		const auto cz = length.z * k;
		return box.getMin() + length * 0.5 + Vector3dd(cx, cy, cz);
	}

	Math::Vector3dd getCellLength() const {
		const auto& length = box.getLength();
		const auto dx = length.x / static_cast<double>(unum);
		const auto dy = length.y / static_cast<double>(vnum);
		const auto dz = length.z / static_cast<double>(wnum);
		return Vector3dd(dx, dy, dz);
	}

	T getValue(const int i, const int j, const int k) { return nodes[i][j][k]; }

	void setValue(const int i, const int j, const int k, const T value) { nodes[i][j][k] = value; }
	/*
	const double getDU() const { return box.getLength().x / static_cast<double>(unum); }

	const double getDV() const { return box.getLength().y / static_cast<double>(vnum); }

	const double getDW() const { return box.getLength().z / static_cast<double>(wnum); }
	*/

private:
	Math::Box3d box;
	size_t unum;
	size_t vnum;
	size_t wnum;
	std::vector<std::vector<std::vector<T>>> nodes;
};

	}
}
