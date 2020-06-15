#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "IndexedParticle.h"
#include <vector>
//#include "ParticlePair.h"

namespace Crystal {
	namespace Algo {

using ParticlePair = std::pair<Shape::IPoint*, Shape::IPoint*>;

class IndexedFinder final : private UnCopyable {
public:
	IndexedFinder(const float effectLength) :
		effectLength(effectLength)
	{}

	void add(Shape::IPoint* particle);

	void createPairs();

	std::vector<ParticlePair> getPairs() const { return pairs; }

	//std::list<SPHParticle*> find(const Math::Vector3d<float>& position);

private:
	std::vector<ParticlePair> pairs;

	std::vector<ParticlePair> search1(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<ParticlePair> search2(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<IndexedParticle> iparticles;
	const float effectLength;
};

	}
}
