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

private:
	Math::Vector3dd position;
};

class SPHSurfaceBuilder
{
public:
	//void add(Shape::IParticle* particle);

	void buildIsotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius);

	void buildAnisotoropic(const std::vector<Math::Vector3dd>& positions, const float searchRadius);

	const std::vector<std::unique_ptr<SPHSurfaceParticle>>& getParticles() const { return particles; }

	std::unique_ptr<Space::SparseVolume> getVolume() { return std::move(volume); }

private:
	std::unique_ptr<Space::SparseVolume> createSparseVolume(const std::vector<Math::Vector3dd>& particles, const float searchRadius);

	void calculateAnisotoropicMatrix(SPHSurfaceParticle* particle, const std::vector<Shape::IParticle*>& neighbors, const float searchRadius);
	
	//std::vector<Shape::IParticle*> particles;

	std::unique_ptr<Space::SparseVolume> volume;
	std::vector<std::unique_ptr<SPHSurfaceParticle>> particles;
};
	}
}