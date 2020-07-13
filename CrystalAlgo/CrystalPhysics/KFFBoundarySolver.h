#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Box3d.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class KFMacroParticle;

class KFFBoundarySolver : private UnCopyable
{
public:
	//~KFFBoundarySolver();

	explicit KFFBoundarySolver(const Math::Box3d& boundary) :
		boundary(boundary)
	{}

	~KFFBoundarySolver() { clear(); }

	void clear() { macros.clear(); }

	void solve(KFMacroParticle* particle, const double dt);

	void createMacro(KFMacroParticle* mp);

private:
	void createMacro(KFMacroParticle* mp, const Math::Vector3dd& position);


private:
	Math::Box3d boundary;
	std::vector<std::unique_ptr<KFMacroParticle>> macros;
};
	}
}