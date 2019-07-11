#pragma once

#include <filesystem>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;

class STLFileImporter : public UnCopyable
{
public:
	explicit STLFileImporter(SceneFactory* sceneFactory);

	bool importSTLAscii(const std::experimental::filesystem::path& filePath, IScene* parent);

	bool importSTLBinary(const std::experimental::filesystem::path& filePath, IScene* parent);

private:
	SceneFactory* sceneFactory;
};
	}
}