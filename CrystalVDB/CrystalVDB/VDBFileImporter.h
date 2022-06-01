#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBScene;

class VDBFileImporter
{
public:
	VDBScene* readPLY(const std::string& filePath);

	VDBScene* readPCD(const std::string& filePath);

	VDBScene* readOBJ(const std::string& filePath);

	VDBScene* readSTL(const std::string& filePath);
};
	}
}