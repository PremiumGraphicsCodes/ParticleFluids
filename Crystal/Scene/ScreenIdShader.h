#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "../Scene/PointShader.h"
#include "../Scene/LineShader.h"
#include "../Scene/TriangleShader.h"

#include "IShaderScene.h"
#include "TextureShaderScene.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class IScene;
		class SceneFactory;
		class ScreenIdShaderScene;

class ScreenIdShader : public IShaderScene
{
public:
	explicit ScreenIdShader(const std::string& name);

	~ScreenIdShader() {}

	bool build(Shader::GLObjectFactory& factory) override;

	void release(Shader::GLObjectFactory& factory) override;

	void render(const ScreenIdShaderScene& vm);

	void render() override;

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	TextureShaderScene* getTextureScene() { return texture; }

private:
	LineShaderScene lineBuffer;
	TriangleShader::GLBuffer triangleBuffer;

	LineShader lineIdRenderer;
	TriangleShader triangleIdRenderer;

	TextureShaderScene* texture;
	std::unique_ptr<Shader::FrameBufferObject> frameBufferObject;
};
	}
}