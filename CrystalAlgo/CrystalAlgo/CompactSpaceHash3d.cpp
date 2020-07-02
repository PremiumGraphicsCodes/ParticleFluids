#include "CompactSpaceHash3d.h"

#include <bitset>

#include "../../Crystal/Shape/IPoint.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;

namespace {
	constexpr long int p1 = 73856093;
	constexpr long int p2 = 19349663;
	constexpr long int p3 = 83492791;
}

CompactSpaceHash3d::CompactSpaceHash3d(const double divideLength, const int tableSize) :
	divideLength(divideLength),
	table(tableSize),
	zCurve()
{
}

CompactSpaceHash3d::~CompactSpaceHash3d()
{
	clear();
}

void CompactSpaceHash3d::clear()
{
	for (auto cell : cells) {
		delete cell;
	}
	cells.clear();
}

void CompactSpaceHash3d::add(IPoint* particle)
{
	const auto& index = toIndex(particle->getPosition());
	const auto hashIndex = toHash(index);
	const auto cellId = toZIndex(index);

	auto& cells = table[hashIndex];
	auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) {
		return cell->cellId == cellId;
	});
	if (iter == cells.end()) {
		auto cell = new CompactSpaceCell();
		cell->cellId = cellId;
		cell->particles.push_back(particle);
		cells.push_back(cell);
	}
	else {
		(*iter)->particles.push_back(particle);
	}
}

void CompactSpaceHash3d::solveInteractions(IPoint* particle, const std::function<void(IPoint*, IPoint*)>& func)
{
	const auto position = particle->getPosition();

	const auto index = toIndex(position);

	for (unsigned int i = index[0] - 1; i <= index[0] + 1; ++i) {
		for (unsigned int j = index[1] - 1; j <= index[1] + 1; ++j) {
			for (unsigned int k = index[2] - 1; k <= index[2] + 1; ++k) {
				std::array<unsigned int, 3> ix{ i,j,k };
				const auto hash = toHash(ix);
				const auto& cells = table[hash];
				const auto cellId = toZIndex(ix);
				auto iter = std::find_if(cells.begin(), cells.end(), [cellId](CompactSpaceCell* cell) {
					return cell->cellId == cellId;
				});
				if (iter == cells.end()) {
					continue;
				}
				const auto& particles = (*iter)->particles;
				for (auto p : particles) {
					if (p == particle) {
						continue; // self.
					}
					const double d2 = Math::getDistanceSquared(p->getPosition(), position);
					if (d2 < divideLength * divideLength) {
						func(particle, p);
					}
				}
			}
		}
	}
}

std::array<unsigned int, 3> CompactSpaceHash3d::toIndex(const Vector3df& pos) const
{
	const auto ix = static_cast<unsigned int>((pos[0]) / divideLength);
	const auto iy = static_cast<unsigned int>((pos[1]) / divideLength);
	const auto iz = static_cast<unsigned int>((pos[2]) / divideLength);
	return { ix, iy, iz };
}

unsigned int CompactSpaceHash3d::toHash(const Vector3df& pos) const
{
	return toHash(toIndex(pos));
}

unsigned int CompactSpaceHash3d::toHash(const std::array<unsigned int, 3>& index) const
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

unsigned int CompactSpaceHash3d::toZIndex(const std::array<unsigned int, 3>& index) const
{
	return zCurve.encode(index);
}
