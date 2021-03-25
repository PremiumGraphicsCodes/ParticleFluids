#pragma once

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"

#include <map>

namespace Crystal {
	namespace Space {

		/*
class SparseVolumeAttr : public Shape::IParticleAttribute
{

};
*/

class SparseVolumeNode : public Shape::IParticle
{
public:
	explicit SparseVolumeNode(const Math::Vector3dd& position) :
		position(position),
		value(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	double getValue() const { return value; }

	void setValue(const double v) { this->value = v; }

private:
	Math::Vector3dd position;
	double value;
	//std::array<int,3> index;
};

class SparseVolume
{
public:
	SparseVolume(const Math::Box3d& bb, const std::array<int, 3>& resolutions) :
		boundingBox(bb),
		resolutions(resolutions)
	{
	}

	Math::Box3d getBoundingBox() const { return boundingBox; }

	void createNode(const std::array<int, 3>& index);

	Math::Vector3dd getPositionAt(const std::array<int, 3>& index) const;

	SparseVolumeNode* findNode(const std::array<int, 3>& index) { return nodes[index]; }

	std::map< std::array<int, 3>, SparseVolumeNode*> getNodes() const { return nodes; }

private:
	std::map< std::array<int, 3>, SparseVolumeNode*> nodes;

	Math::Box3d boundingBox;
	std::array<int, 3> resolutions;
};

	}
}