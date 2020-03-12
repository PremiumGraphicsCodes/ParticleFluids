#pragma once

#include "../Graphics/DrawableId.h"

#include "../Scene/TriangleRenderer.h"
#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "../Scene/PointRenderer.h"
#include "../Scene/LineRenderer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class IScene;
		class SceneFactory;
		class SceneIdViewModel;

class SceneIdRenderer : private UnCopyable
{
public:
	SceneIdRenderer()
	{}

	~SceneIdRenderer() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera, const SceneIdViewModel& vm);

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	PointRenderer::GLBuffer pointBuffer;
	LineRenderer::GLBuffer lineBuffer;
	TriangleRenderer::GLBuffer triangleBuffer;

	PointRenderer pointIdRenderer;
	LineRenderer lineIdRenderer;
	TriangleRenderer triangleIdRenderer;

	Shader::TextureObject texture;
	std::unique_ptr<Shader::FrameBufferObject> frameBufferObject;
};
	}
}