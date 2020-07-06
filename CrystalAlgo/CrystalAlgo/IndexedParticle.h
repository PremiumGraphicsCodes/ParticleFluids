#pragma once

#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Shape/IPoint.h"

namespace Crystal {
	namespace Search {

class IndexedParticle
{
public:
	IndexedParticle() :
		particle(nullptr)
	{}

	IndexedParticle(Shape::IPoint* particle) :
		particle(particle)
	{
	}

public:
	void setGridID(const float effectLength);

	Math::Vector3df getPosition() const { return particle->getPosition(); }

	static int toGridId(const Math::Vector3df pos, const float effectLength);

	static std::array<int, 3> toIndex(const Math::Vector3df pos, const float effectLength);

	int getGridID() const { return gridID; }

	bool operator<(const IndexedParticle& rhs) {
		return this->getGridID() < rhs.getGridID();
	}

	Shape::IPoint* getParticle() const { return particle; }

private:
	static int toIdX(std::array<int, 3> index);

private:
	Shape::IPoint* particle;
	int gridID;
};

	}
}