#include "SparseVolume.h"

using namespace Crystal::Math;
using namespace Crystal::Space;

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
Vector3dd SparseVolume<T>::getPositionAt(const std::array<int, 3>& index) const
{
	const auto u = index[0] / static_cast<double>(resolutions[0]);
	const auto v = index[1] / static_cast<double>(resolutions[1]);
	const auto w = index[2] / static_cast<double>(resolutions[2]);

	return boundingBox.getPosition(u, v, w);
}

template<typename T>
SparseVolumeNode<T>* SparseVolume<T>::createNode(const std::array<int, 3>& index)
{
	const auto pos = getPositionAt(index);
	auto node = new SparseVolumeNode<T>(pos);
	nodes[index] = node;
	return node;
}

template<typename T>
void SparseVolume<T>::addValue(const std::array<int, 3>& index, const T value)
{
	auto n = nodes[index];
	n->setValue(n->getValue() + value);
}

template<typename T>
T SparseVolume<T>::getValueAt(const std::array<int, 3>& index) const
{
	auto iter = nodes.find(index);
	if (iter == nodes.end()) {
		return 0.0f;
	}
	return iter->second->getValue();
}

template<typename T>
bool SparseVolume<T>::exists(const std::array<int, 3>& index) const
{
	auto iter = nodes.find(index);
	return iter == nodes.end();
}


template class SparseVolume<bool>;
template class SparseVolume<float>;
template class SparseVolume<double>;
