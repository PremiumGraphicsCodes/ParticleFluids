#include "SpaceHash.h"

#include "MicroParticle.h"
#include "MacroParticle.h"
#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Physics;

namespace {
	constexpr long int p1 = 73856093;
	constexpr long int p2 = 19349663;
	constexpr long int p3 = 83492791;
}

SpaceHash::SpaceHash(const double divideLength, const int tableSize) :
	divideLength(divideLength),
	table(tableSize)
{
}

/*
void SpaceHash::add(const IParticleSystem& particles)
{
	const auto& points = particles.getIParticles();
	for (auto p : points) {
		add(p);
	}
}
*/

void SpaceHash::add(MacroParticle* particle)
{
	const auto& index = toIndex(particle->getPosition());
	const auto hashIndex = toHash(index);
	table[hashIndex].push_back(particle);
}

void SpaceHash::solveInteractions(MicroParticle* micro, const std::function<void(MacroParticle*, IPoint*)>& func)
{
	const auto position = micro->getPosition();
	const auto& index = toIndex(position);
	for (int i = index[0] - 1; i <= index[0] + 1; ++i) {
		for (int j = index[1] - 1; j <= index[1] + 1; ++j) {
			for (int k = index[2] - 1; k <= index[2] + 1; ++k) {
				std::array<int, 3> index{ i,j,k };
				const auto& hash = toHash(index);
				const auto& points = table[hash];
				for (auto p : points) {
					const auto ix = toIndex(p->getPosition());
					if (ix != index) {
						continue;
					}
					/*
					if (p->getParent() == macro) {
						continue;
					}
					*/
					const double d2 = Math::getDistanceSquared(p->getPosition(), position);
					if (d2 < divideLength * divideLength) {
						func(p, micro);
					}
				}
				//				results.insert(results.end(), points.begin(), points.end());
			}
		}
	}
}

std::array<int, 3> SpaceHash::toIndex(const Vector3df& pos)
{
	const int ix = static_cast<int>((pos[0]) / divideLength);
	const int iy = static_cast<int>((pos[1]) / divideLength);
	const int iz = static_cast<int>((pos[2]) / divideLength);
	return { ix, iy, iz };
}

int SpaceHash::toHash(const Vector3df& pos)
{
	return toHash(toIndex(pos));
}

int SpaceHash::toHash(const std::array<int, 3>& index)
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