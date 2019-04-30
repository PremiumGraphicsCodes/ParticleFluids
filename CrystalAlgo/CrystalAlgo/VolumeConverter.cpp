#include "VolumeConverter.h"

#include "Octree.h"
#include "../../Crystal/Math/Gaussian.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Algo;

void VolumeConverter::convert(const Box3d& space, const ParticleSystem<double>& particleSystem, const int levelOfDetail)
{
	/*
	Octree tree(space);
	const auto& particles = particleSystem.getParticles();
	for (auto& p : particles) {
		tree.add(p);
	}
	std::vector<VolumeCell> cells;
	const auto& children = tree.createChildren(levelOfDetail);//Vector3d<float>(effectLength,effectLength,effectLength));

	Gaussian kernel;
	for (const auto& c : children) {
		const auto& box = c.getBoundingBox();
		const auto& poss = box.toSpace().toArray();
		std::array<float, 8> values;
		values.fill(0.0f);
		for (int i = 0; i < 8; ++i) {
			for (const auto& particle : c.getParticles()) {
				const auto dist2 = poss[i].getDistanceSquared(particle->getPosition());
				const auto radiusSquared = particle->getBoundingRadius() * particle->getBoundingRadius();
				if (dist2 < radiusSquared) {
					//const auto value = kernel.getPoly6Kernel(std::sqrt(dist2), std::sqrt(radiusSquared)) * particle->getDensity();
					const auto distance = std::sqrt(dist2);																		//				const auto mm = Matrix3d<float>(1.0 / particle->getRadii().getX(), 0, 0, 0, 1.0 / particle->getRadii().getY(), 0, 0, 0, 1.0 / particle->getRadii().getZ());
					const auto value = kernel.getValue(distance);
					values[i] += value;
				}
			}
		}
		VolumeCell cell(c.getBoundingBox().toSpace(), values);
		cells.emplace_back(cell);
	}
	*/
}