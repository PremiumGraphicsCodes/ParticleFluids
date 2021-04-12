#include "FLIPSSolver.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void FLIPSGrid::solvePressure()
{
	const auto resolutions = cells.getResolutions();
	for (auto ix = 0; ix < resolutions.size(); ++ix) {
		for (auto iy = 0; iy < resolutions.size(); ++iy) {
			for (auto iz = 0; iz < resolutions.size(); ++iz) {
				const auto c = cells.getValue(ix, iy, iz);
				const auto left = cells.getValue(ix - 1, iy, iz);
				const auto right = cells.getValue(ix + 1, iy, iz);
				c->getPressure() - left->getPressure();
			}
		}
	}
}

void FLIPSGrid::solveViscosity()
{

}

void FLIPSSolver::solve(const float dt)
{
	const Vector3df dv = 0.5f * dt * dt * Vector3df(0.0, -9.8, 0.0);
	for (auto p : particles) {
		p->translate(dv);
	}

	// particle->grid‚ÉƒAƒTƒCƒ“‚·‚é
	/*
	for (auto p : particles) {
		p->getPosition() / grid.;
	}
	*/

	grid.solvePressure();

	grid.solveViscosity();
	//grid.getCellLength()
}