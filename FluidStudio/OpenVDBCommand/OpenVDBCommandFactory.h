#pragma once

#include <memory>

#include "../../Crystal/Util/UnCopyable.h"
#include "../../CrystalViewer/Command/ICommand.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBCommandFactory : UnCopyable
{
public:
	static std::unique_ptr<Command::ICommand> create(const std::string& name);
};
	}
}