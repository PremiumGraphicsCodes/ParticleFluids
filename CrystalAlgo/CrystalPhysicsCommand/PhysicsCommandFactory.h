#pragma once

#include "../../Crystal/Util/UnCopyable.h"
#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace Physics {

class PhysicsCommandFactory : UnCopyable
{
public:
	static std::unique_ptr<Command::ICommand> create(const std::string& name);
};

	}
}
