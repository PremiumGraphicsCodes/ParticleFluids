#pragma once

#include "../../Crystal/Math/Box3d.h"
#include "../../Crystal/Shape/IParticle.h"
#include "../../Crystal/Util/UnCopyable.h"

#include <map>
#include <vector>
#include <list>
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
	SparseVolumeNode(const Math::Vector3dd& position, const std::array<int,3>& index) :
		position(position),
		value(0.0),
		index(index)
	{}

	Math::Vector3dd getPosition() const override { return position; }

	T getValue() const { return value; }

	void setValue(const T v) { this->value = v; }

	std::array<int, 3> getIndex() const { return index; }

private:
	Math::Vector3dd position;
	T value;
	const std::array<int, 3> index;
};

template<typename T>
class SparseVolume : private UnCopyable
{
public:
	SparseVolume()
	{
		table.resize(10000);
	}

	SparseVolume(const Math::Box3dd& bb, const std::array<size_t, 3>& resolutions) :
		boundingBox(bb),
		resolutions(resolutions)
	{
		table.resize(10000);
	}

	~SparseVolume()
	{
		clear();
	}

	void clear();

	void setBox(const Math::Box3dd& bb)
	{
		this->boundingBox = bb;
	}

	void setResolution(const std::array<size_t, 3>& resolution)
	{
		this->resolutions = resolution;
	}

	Math::Box3dd getBoundingBox() const { return boundingBox; }

	SparseVolumeNode<T>* createNode(const std::array<int, 3>& index);

	Math::Vector3dd getPositionAt(const std::array<int, 3>& index) const;

	SparseVolumeNode<T>* findNode(const std::array<int, 3>& index) const;

	void addValue(const std::array<int, 3>& index, const T value);

	T getValueAt(const std::array<int, 3>& index) const;

	bool exists(const std::array<int, 3>& index) const;

	Math::Vector3dd getCellLength() const;

	std::list<SparseVolumeNode<T>*> getNodes() const;

private:
	std::array<int, 3> toIndex(const Math::Vector3df& pos) const;

	int toHash(const Math::Vector3df& pos) const;

	int toHash(const std::array<int, 3>& index) const;

	Math::Box3dd boundingBox;
	std::array<size_t, 3> resolutions;
	std::vector<std::list<SparseVolumeNode<T>*>> table;
};

using SparseVolumef = SparseVolume<float>;
using SparseVolumed = SparseVolume<double>;
	}
}