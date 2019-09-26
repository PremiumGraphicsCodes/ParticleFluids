#pragma once

#include "ICommand.h"
#include <filesystem>
#include <vector>

namespace Crystal {
	namespace Command {

class FileImportCommand : public ICommand
{
public:
	struct Args
	{
		std::filesystem::path filePath;
	};

	void execute() override;
};

	}
}