#pragma once

#include <vector>
#include <memory>

#include "../../Crystal/Shape/IParticle.h"
#include "../../CrystalSpace/CrystalSpace/SparseVolume.h"

namespace Crystal {
	namespace Physics {

class SPHSurfaceParticle : public Shape::IParticle
{
public:
	explicit SPHSurfaceParticle(const Math::Vector3dd& p) :
		position(p),
		matrix(Math::identitiyMatrix())
	{}

	Math::Vector3dd getPosition() const { return position; }

	Math::Matrix3dd matrix;

	void calculateCorrectedPosition(const float lamda);

	void calculateAnisotoropicMatrix(const std::vector<Shape::IParticle*>& neighbors, const float searchRadius);

	Math::Vector3df getCorrectedPosition() const { return correctedPosition; }

private:
	Math::Vector3df position;
	Math::Vector3df correctedPosition;
	Math::Vector3df weightedMean;
};

class SPHSurfaceBuilder
{
public:
	//void add(Shape::IParticle* particle);

	void buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius);

	void buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius, const float cellLength);

	const std::vector<std::unique_ptr<SPHSurfaceParticle>>& getParticles() const { return particles; }

	std::unique_ptr<Space::SparseVolume> getVolume() { return std::move(volume); }

private:
	std::unique_ptr<Space::SparseVolume> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float searchRadius, const float cellLength);

	
	//std::vector<Shape::IParticle*> particles;

	std::unique_ptr<Space::SparseVolume> volume;
	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
};
	}
}