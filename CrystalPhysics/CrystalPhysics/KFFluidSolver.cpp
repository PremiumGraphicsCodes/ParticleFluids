#include "KFFluidSolver.h"

#include "KFMacroParticle.h"
#include "KFMicroParticle.h"

#include "KFFluidScene.h"
#include "CSGBoundaryScene.h"

#include "MeshBoundaryScene.h"

#include "../../CrystalSpace/CrystalAlgo/DistanceCalculator.h"

#include "../../CrystalSpace/CrystalAlgo/CompactSpaceHash3d.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::Search;
using namespace Crystal::Physics;

void KFBoundarySolver::setup(const float effectLength)
{
	std::vector<KFMacroParticle*> boundaryParticles;
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
		const auto& microParticles = bp->getPoints();
		for (auto mp : microParticles) {
			spaceHash->add(mp);
		}
	}
}

std::vector<IParticle*> KFBoundarySolver::findNeighbors(const Vector3dd& position)
{
	if (spaceHash == nullptr) {
		return {};
	}
	return spaceHash->findNeighbors(position);
}

void KFMeshBoundarySolver::setup()
{
	std::vector<BoundaryMeshParticle*> boundaryParticles;
	for (auto b : boundaries) {
		const auto bp = b->getParticles();
		boundaryParticles.insert(boundaryParticles.end(), bp.begin(), bp.end());
	}

	if (boundaryParticles.empty()) {
		return;
	}

	const auto hashSize = boundaryParticles.size();
	const auto searchRadius = boundaries.front()->getRadius() * 1.25;// boundaryParticles.front()->getRadius() * 2.25;
	spaceHash = std::make_unique<CompactSpaceHash3d>(searchRadius, boundaryParticles.size());
	//spaceHash.setup(searchRadius, boundaryParticles.size());

	for (auto bp : boundaryParticles) {
		spaceHash->add(bp);
	}
}

void KFMeshBoundarySolver::searchNeighbors(const std::vector<KFMacroParticle*>& macros)
{
	if (spaceHash == nullptr) {
		return;
	}
	table.clear();
	for (auto m : macros) {
		const auto neighbors = spaceHash->findNeighbors(m->getPosition());
		table.push_back(std::make_pair(m, neighbors));
	}
}

void KFMeshBoundarySolver::calculateForces(const float dt, const float searchRadius)
{
	for (const auto& t : table) {
		calculatePressureForce(t, dt, searchRadius);
	}
}

void KFMeshBoundarySolver::calculatePressureForce(const std::pair<KFMacroParticle*, std::vector<IParticle*>>& pair, const double dt, const float effectLength)
{
	auto mp = pair.first;
	const auto& meshes = pair.second;
	for (const auto& mm : meshes) {
		const auto distanceSquared = Crystal::Math::getDistanceSquared(pair.first->getPosition(), mm->getPosition());
		if (distanceSquared > effectLength * effectLength) {
			continue;
		}

		const auto fluidPos = mp->getPosition();
		auto m = static_cast<BoundaryMeshParticle*>(mm);
		const auto& n = m->getAttribute().normal;
		const auto boundaryPos = m->getPosition();
		const auto v = fluidPos - boundaryPos;
		const auto distance = glm::dot(n, v);
		if (distance < 0.0) {
			const auto f = ::fabs(distance)* n;
			mp->addForce(f / dt / dt);
		}
	}
	//return spaceHash->findNeighbors(position);
}

KFFluidSolver::KFFluidSolver(const int id) :
	IAnimator(id)
{}

void KFFluidSolver::setupBoundaries()
{
	//this->boundarySolver = KFBoundarySolver();
	this->boundarySolver.setup(effectLength);
	this->meshBoundarySolver.setup();
}

void KFFluidSolver::addFluidScene(KFFluidScene* scene)
{
	this->fluids.push_back(scene);
}

void KFFluidSolver::addBoundaryScene(KFFluidScene* scene)
{
	this->boundarySolver.addBoundaryScene(scene);
}

void KFFluidSolver::addBoundary(MeshBoundaryScene* scene)
{
	this->meshBoundarySolver.addScene(scene);
}

void KFFluidSolver::step()
{
	simulate();
}

void KFFluidSolver::simulate()
{
	std::vector<KFMacroParticle*> fluidParticles;

	for (auto fluid : fluids) {
		const auto ps = fluid->getParticles();
		fluidParticles.insert(fluidParticles.end(), ps.begin(), ps.end());
	}

	for (auto particle : fluidParticles) {
		particle->reset(true);
	}

	if (fluidParticles.empty()) {
		return;
	}

	const auto hashSize = fluidParticles.front()->getPoints().size() * fluidParticles.size();
	const auto searchRadius = effectLength;
	CompactSpaceHash3d spaceHash(searchRadius, static_cast<int>( hashSize));
	for (auto particle : fluidParticles) {
		particle->updateMicros();
		const auto& microParticles = particle->getPoints();
		for (auto mp : microParticles) {
			spaceHash.add(mp);
		}
	}

#pragma omp parallel for
	for(int i = 0; i < fluidParticles.size(); ++i) {
		const auto particle = fluidParticles[i];
		const auto& neighbors = spaceHash.findNeighbors(particle);
		for (auto n : neighbors) {
			particle->addMicro(static_cast<KFMicroParticle*>(n));
		}
		const auto& bps = boundarySolver.findNeighbors(particle->getPosition());
		for (auto n : bps) {
			particle->addMicro(static_cast<KFMicroParticle*>(n));
		}
	}

	meshBoundarySolver.searchNeighbors(fluidParticles);

	double time = 0.0;
	while (time < maxTimeStep) {
		const auto dt = calculateTimeStep(fluidParticles);

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			particle->updateInnerPoints();
			particle->calculatePressure(1.0);
			particle->calculateViscosity();
		}
		

#pragma omp parallel for
		for (int i = 0; i < fluidParticles.size(); ++i) {
			const auto particle = fluidParticles[i];
			//boundarySolver.createMacro(particle);
			meshBoundarySolver.calculateForces(dt, searchRadius * 0.5);
			solveBoundary(particle, dt);
		}

		for (auto particle : fluidParticles) {
			particle->addForce(Vector3dd(0.0, -9.8 * particle->getDensity(), 0.0));
			particle->stepTime(dt);
		}

		// solve incompressibility.
		float relaxationCoe = 0.5f;
		for (int i = 0; i < 2; ++i) {
			for (auto particle : fluidParticles) {
				particle->reset(false);
				particle->updateMicros();
			}

#pragma omp parallel for
			for (int i = 0; i < fluidParticles.size(); ++i) {
				const auto particle = fluidParticles[i];
				particle->updateInnerPoints();
				particle->calculatePressure(relaxationCoe);
			}

			for (auto particle : fluidParticles) {
				solveBoundary(particle, dt);
			}
			//	solveBoundary(particles);

			for (auto particle : fluidParticles) {
				//particle->calculateViscosity(particle->getScene()->getViscosityCoe() * relaxationCoe);
				particle->stepTime(dt);
			}
			relaxationCoe /= 2.0;
		}

		time += dt;
	}

	auto densityError = 0.0;
	for (auto particle : fluidParticles) {
		densityError += particle->getDensity() / (double)fluidParticles.size();
	}
	std::cout << densityError << std::endl;


	/*
	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
	}
	*/
}

float KFFluidSolver::calculateTimeStep(const std::vector<KFMacroParticle*>& particles)
{
	float maxVelocity = 0.0f;
	for (auto p : particles) {
		maxVelocity = std::max<float>(maxVelocity, Math::getLengthSquared( p->getVelocity() ) );
	}
	if (maxVelocity < 1.0e-3) {
		return maxTimeStep;
	}
	maxVelocity = std::sqrt(maxVelocity);
	const auto dt = 0.4f * particles.front()->getRadius() * 2.0f / maxVelocity;
	return maxTimeStep;
	//return std::min(dt, maxTimeStep);
}

void KFFluidSolver::solveBoundary(KFMacroParticle* particle, const double dt)
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
				//const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z > boundary.getMaxZ()) {
				const auto distance = boundary.getMaxZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
				particle->addForce(overlap / dt / dt);
			}
			if (position.z < boundary.getMinZ()) {
				const auto distance = boundary.getMinZ() - position.z;
				const auto overlap = Vector3dd(0, 0, distance);
				const auto count = ::fabs(distance) / (particle->getRadius() * 0.1);
				//particle->addBoundaryCount(count * 10);
				particle->addForce(overlap / dt / dt);
			}
		}
	}
}

void KFFUpdater::step()
{
	for (auto fluid : fluids) {
		fluid->getPresenter()->updateView();
		//for(auto b : fluid->get)
	}
	//for(auto b : csgB)
}
