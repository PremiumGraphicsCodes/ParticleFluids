#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "../Scene/PointShader.h"
#include "../Scene/LineShaderScene.h"
#include "../Scene/TriangleShaderScene.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class IScene;
		class SceneFactory;
		class SceneIdViewModel;

class ScreenIdShaderScene : private UnCopyable
{
public:
	ScreenIdShaderScene()
	{}

	~ScreenIdShaderScene() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera, const SceneIdViewModel& vm);

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	PointShaderBuffer pointBuffer;
	LineShaderBuffer lineBuffer;
	TriangleShaderScene::GLBuffer triangleBuffer;

	PointShader pointIdRenderer;
	LineShaderScene lineIdRenderer;
	TriangleShaderScene triangleIdRenderer;

	Shader::TextureObject texture;
	std::unique_ptr<Shader::FrameBufferObject> frameBufferObject;
};
	}
}