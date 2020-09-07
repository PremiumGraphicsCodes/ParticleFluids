#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Box3d.h"

#include "KFBoundaryParticle.h"

#include <memory>

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class KFFBoundarySolver : private UnCopyable
{
public:
	//~KFFBoundarySolver();

	KFFBoundarySolver()
	{}

	void add(const Math::Box3d& box) { this->surfaces.push_back(box); }

	void add(KFBoundaryParticle* bp) { this->boudaryParticles.push_back(bp); }

	~KFFBoundarySolver() { clear(); }

	void clear() { macros.clear(); }

	void solve(KFMacroParticle* particle, const double dt);

	//void createMacro(KFMacroParticle* mp);

private:
	//void createMacro(KFMacroParticle* mp, const Math::Vector3dd& position);

private:
	std::vector<Math::Box3d> surfaces;
	std::vector<std::unique_ptr<KFMacroParticle>> macros;
	std::vector<KFBoundaryParticle*> boudaryParticles;
};
	}
}