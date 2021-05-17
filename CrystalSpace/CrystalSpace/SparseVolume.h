#pragma once

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Util/UnCopyable.h"

#include <map>
#include <array>

namespace Crystal {
	namespace Space {

		/*
class SparseVolumeAttr : public Shape::IParticleAttribute
{

};
*/

template<typename T>
class SparseVolumeNode : public Shape::IParticle
{
public:
	explicit SparseVolumeNode(const Math::Vector3dd& position) :
		position(position),
		value(0.0)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	T getValue() const { return value; }

	void setValue(const T v) { this->value = v; }

private:
	Math::Vector3dd position;
	T value;
	//std::array<int,3> index;
};

template<typename T>
class SparseVolume : private UnCopyable
{
public:
	SparseVolume()
	{}

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

	void setBox(const Math::Box3d& bb)
	{
		this->boundingBox = bb;
	}

	void setResolution(const std::array<int, 3>& resolution)
	{
		this->resolutions = resolution;
	}

	Math::Box3d getBoundingBox() const { return boundingBox; }

	SparseVolumeNode<T>* createNode(const std::array<int, 3>& index);

	Math::Vector3dd getPositionAt(const std::array<int, 3>& index) const;

	SparseVolumeNode<T>* findNode(const std::array<int, 3>& index) { return nodes[index]; }

	std::map< std::array<int, 3>, SparseVolumeNode<T>*> getNodes() const { return nodes; }

	std::map< std::array<int, 3>, SparseVolumeNode<T>*>& getNodes() { return nodes; }

	void addValue(const std::array<int, 3>& index, const T value);

	T getValueAt(const std::array<int, 3>& index) const;

	bool exists(const std::array<int, 3>& index) const;

private:
	std::map< std::array<int, 3>, SparseVolumeNode<T>*> nodes;

	Math::Box3d boundingBox;
	std::array<int, 3> resolutions;
};

using SparseVolumef = SparseVolume<float>;
using SparseVolumed = SparseVolume<double>;
	}
}