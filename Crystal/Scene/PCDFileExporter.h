#pragma once

#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class ObjectRepository;

class PCDFileExporter
{
public:
	bool exportPCD(const std::experimental::filesystem::path& filePath, ObjectRepository& objects);
};

	}
}