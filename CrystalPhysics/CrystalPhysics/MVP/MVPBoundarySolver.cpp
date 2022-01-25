#include "MVPBoundarySolver.h"

#include "MVPVolumeParticle.h"
#include "MVPFluidScene.h"
#include "../CSGBoundaryScene.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Space;
using namespace Crystal::Physics;

void MVPBoundarySolver::setup(const float effectLength)
{
	std::vector<MVPVolumeParticle*> boundaryParticles;
	for (auto b : boundaries) {
		const auto bp = b->getParticles();
		boundaryParticles.insert(boundaryParticles.end(), bp.begin(), bp.end());
	}

	if (boundaryParticles.empty()) {
		return;
	}

	const auto hashSize = boundaryParticles.front()->getPoints().size() * boundaryParticles.size();
	const auto searchRadius = effectLength;
	spaceHash = std::make_unique<CompactSpaceHash3d>(searchRadius, boundaryParticles.size());
	//spaceHash.setup(searchRadius, boundaryParticles.size());

	for (auto bp : boundaryParticles) {
		spaceHash->add(bp);
		/*
		const auto& microParticles = bp->getPoints();
		for (auto mp : microParticles) {
			spaceHash->add(mp);
		}
		*/
	}
}

std::vector<IParticle*> MVPBoundarySolver::findNeighbors(const Vector3dd& position)
{
	if (spaceHash == nullptr) {
		return {};
	}
	return spaceHash->findNeighbors(position);
}

void MVPBoundarySolver::solvePressure(MVPVolumeParticle* particle, const double dt)
{
	for (const auto& csg : csgBoundaries) {
		for (const auto& boundary : csg->getBoxes()) {
			auto position = particle->getPosition();
			if (position.y < boundary.getMinY()) {
				const auto distance = boundary.getMinY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.y > boundary.getMaxY()) {
				const auto distance = boundary.getMaxY() - position.y;
				const auto overlap = Vector3dd(0, distance, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x > boundary.getMaxX()) {
				const auto distance = boundary.getMaxX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.x < boundary.getMinX()) {
				const auto distance = boundary.getMinX() - position.x;
				const auto overlap = Vector3dd(distance, 0, 0);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z > boundary.getMaxZ()) {
				const auto distance = boundary.getMaxZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z < boundary.getMinZ()) {
				const auto distance = boundary.getMinZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				particle->addForce(overlap / dt / dt);
			}
		}
	}

}
