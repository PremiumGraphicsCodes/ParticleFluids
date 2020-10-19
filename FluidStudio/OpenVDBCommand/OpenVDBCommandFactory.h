#pragma once

#include <memory>

#include "../../Crystal/Util/UnCopyable.h"
#include "../../CrystalViewer/Command/ICommand.h"
#include "../../CrystalViewer/Command/CommandFactory.h"

namespace Crystal {
	namespace OpenVDB {

class OpenVDBCommandFactory : public ICommandFactory
{
public:
	std::unique_ptr<Command::ICommand> create(const std::string& name) override;
};
	}
}