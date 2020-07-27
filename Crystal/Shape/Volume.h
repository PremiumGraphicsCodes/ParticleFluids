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

	size_t getUNum() const { return nodes.size(); }

	size_t getVNum() const { return nodes[0].size(); }

	size_t getWNum() const { return nodes[0][0].size(); }

private:
	Math::Box3d box;
	std::vector<std::vector<std::vector<Particle<T>>>> nodes;
};

	}
}
