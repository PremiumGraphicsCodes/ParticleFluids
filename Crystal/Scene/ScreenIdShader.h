#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "../Scene/PointShader.h"
#include "../Scene/LineShaderScene.h"

#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class IScene;
		class SceneFactory;
		class ScreenIdShaderScene;

class ScreenIdShader //: public IShaderScene
{
public:
	explicit ScreenIdShader(const std::string& name);

	~ScreenIdShader() {}

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void render(const Graphics::Camera& camera);

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	Shader::TextureObject* getTextureScene() { return &texture; }

	void addScene(IShaderScene* scene) { this->scenes.push_back(scene); }

private:
	std::vector<IShaderScene*> scenes;

	Shader::TextureObject texture;
	Shader::FrameBufferObject frameBufferObject;
};
	}
}