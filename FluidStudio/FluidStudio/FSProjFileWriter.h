#pragma once

#include <filesystem>

namespace PG {
	namespace FS {
		class MainModel;

class FSProjFileWriter
{
public:
	bool write(MainModel* model, const std::string& filePath);
};

	}
}