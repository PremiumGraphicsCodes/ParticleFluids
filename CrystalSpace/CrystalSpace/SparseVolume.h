#pragma once

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Util/UnCopyable.h"

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

class SparseVolume : private UnCopyable
{
public:
	SparseVolume(const Math::Box3d& bb, const std::array<int, 3>& resolutions) :
		boundingBox(bb),
		resolutions(resolutions)
	{
	}

	~SparseVolume()
	{
		clear();
	}

	void clear();

	Math::Box3d getBoundingBox() const { return boundingBox; }

	SparseVolumeNode* createNode(const std::array<int, 3>& index);

	Math::Vector3dd getPositionAt(const std::array<int, 3>& index) const;

	SparseVolumeNode* findNode(const std::array<int, 3>& index) { return nodes[index]; }

	std::map< std::array<int, 3>, SparseVolumeNode*> getNodes() const { return nodes; }

	std::map< std::array<int, 3>, SparseVolumeNode*>& getNodes() { return nodes; }

	void addValue(const std::array<int, 3>& index, const float value);

	float getValueAt(const std::array<int, 3>& index) const;

private:
	std::map< std::array<int, 3>, SparseVolumeNode*> nodes;

	Math::Box3d boundingBox;
	std::array<int, 3> resolutions;
};

	}
}