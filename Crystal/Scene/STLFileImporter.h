#pragma once

#include <filesystem>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Model {
		class Scene;
		class IScene;
		class SceneFactory;

class STLFileImporter : public UnCopyable
{
public:
	explicit STLFileImporter(SceneFactory* sceneFactory) :
		sceneFactory(sceneFactory)
	{}

	bool importSTLAscii(const std::experimental::filesystem::path& filePath, Scene& objects);

	bool importSTLBinary(const std::experimental::filesystem::path& filePath, Scene& objects);

private:
	SceneFactory* sceneFactory;
	IScene* scene;
};
	}
}