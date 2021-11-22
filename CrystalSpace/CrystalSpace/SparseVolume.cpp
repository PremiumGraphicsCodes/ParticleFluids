#include "SparseVolume.h"
#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Space;

namespace {
	constexpr long int p1 = 73856093;
	constexpr long int p2 = 19349663;
	constexpr long int p3 = 83492791;
}

template class SparseVolumeNode<bool>;
template class SparseVolumeNode<float>;
template class SparseVolumeNode<double>;

template<typename T>
void SparseVolume<T>::clear()
{
	for (auto n : nodes) {
		delete n.second;
	}
	nodes.clear();
}

template<typename T>
Vector3dd SparseVolume<T>::getPositionAt(const std::array<size_t, 3>& index) const
{
	const auto u = index[0] / static_cast<double>(resolutions[0]);
	const auto v = index[1] / static_cast<double>(resolutions[1]);
	const auto w = index[2] / static_cast<double>(resolutions[2]);

	return boundingBox.getPosition(u, v, w);
}

template<typename T>
SparseVolumeNode<T>* SparseVolume<T>::createNode(const std::array<size_t, 3>& index)
{
	const auto pos = getPositionAt(index);
	auto node = new SparseVolumeNode<T>(pos);
	nodes[index] = node;
	return node;
}

template<typename T>
void SparseVolume<T>::addValue(const std::array<size_t, 3>& index, const T value)
{
	auto n = nodes[index];
	n->setValue(n->getValue() + value);
}

template<typename T>
T SparseVolume<T>::getValueAt(const std::array<size_t, 3>& index) const
{
	auto iter = nodes.find(index);
	if (iter == nodes.end()) {
		return 0.0f;
	}
	return iter->second->getValue();
}

template<typename T>
bool SparseVolume<T>::exists(const std::array<size_t, 3>& index) const
{
	auto iter = nodes.find(index);
	return iter != nodes.end();
}

template<typename T>
std::array<int, 3> SparseVolume<T>::toIndex(const Vector3df& pos) const
{
	const int ix = static_cast<int>((pos[0]) / resolutions[0]);
	const int iy = static_cast<int>((pos[1]) / resolutions[1]);
	const int iz = static_cast<int>((pos[2]) / resolutions[2]);
	return { ix, iy, iz };
}

template<typename T>
int SparseVolume<T>::toHash(const Vector3df& pos) const
{
	return toHash(toIndex(pos));
}

template<typename T>
int SparseVolume<T>::toHash(const std::array<int, 3>& index) const
{
	std::bitset<32> x = index[0] * p1;
	std::bitset<32> y = index[1] * p2;
	std::bitset<32> z = index[2] * p3;
	//assert(x >= 0);
	//assert(y >= 0);
	//assert(z >= 0);
	const auto value = (x ^ y ^ z).to_ulong();
	return value % table.size();
}

template<typename T>
Vector3dd SparseVolume<T>::getCellLength() const
{
	const auto lx = boundingBox.getLength().x / resolutions[0];
	const auto ly = boundingBox.getLength().y / resolutions[1];
	const auto lz = boundingBox.getLength().z / resolutions[2];
	return Vector3dd(lx, ly, lz);
}


template class SparseVolume<bool>;
template class SparseVolume<float>;
template class SparseVolume<double>;
