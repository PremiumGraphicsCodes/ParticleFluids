#pragma once

#include <filesystem>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class Scene;
		class IScene;
		class SceneFactory;

class STLFileImporter : public UnCopyable
{
public:
	explicit STLFileImporter(SceneFactory* sceneFactory);

	bool importSTLAscii(const std::experimental::filesystem::path& filePath);

	bool importSTLBinary(const std::experimental::filesystem::path& filePath);

	IScene* getScene() const { return scene; }

private:
	SceneFactory* sceneFactory;
	IScene* scene;
};
	}
}