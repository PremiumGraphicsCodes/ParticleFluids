#pragma once

#include "../IO/OBJFile.h"
#include "../IO/MTLFile.h"
#include "SceneFactory.h"
#include <experimental/filesystem>

namespace Crystal {
	namespace Model {
		class PolygonMeshScene;
		class MaterialScene;

class OBJFileImporter
{
public:
	OBJFileImporter(SceneFactory* sceneFactory) :
		sceneFactory(sceneFactory)
	{}

	bool importOBJ(const std::experimental::filesystem::path& filePath);

	bool importMTL(const std::experimental::filesystem::path& filePath);

	bool importOBJWithMTL(const std::experimental::filesystem::path& filePath);

private:
	//void match(const IO::OBJFile& obj, Scene& appearances);
	SceneFactory* sceneFactory;
};
	}
}