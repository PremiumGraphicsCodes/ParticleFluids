#pragma once

#include "../../Crystal/Util/UnCopyable.h"

#include "../../Crystal/Math/Box3d.h"
#include <memory>

namespace Crystal {
	namespace Physics {
		class MacroParticle;

class KFFBoundarySolver : private UnCopyable
{
public:
	//~KFFBoundarySolver();

	explicit KFFBoundarySolver(const Math::Box3d& boundary) :
		boundary(boundary)
	{}

	void clear() { macros.clear(); }

	void solve(MacroParticle* particle, const double dt);

	void createMacro(MacroParticle* mp);

private:
	void createMacro(MacroParticle* mp, const Math::Vector3dd& position);


private:
	Math::Box3d boundary;
	std::vector<std::unique_ptr<MacroParticle>> macros;
};
	}
}