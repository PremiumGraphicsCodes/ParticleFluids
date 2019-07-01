#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {
		class SceneIdViewModel;

class ObjectIdRenderer : private UnCopyable
{
public:
	explicit ObjectIdRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectIdRenderer() {}

	bool build(Shader::ShaderObjectRepository& shaders, Shader::TextureObjectRepository& textures);

	void render();

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	void setViewModel(const SceneIdViewModel& vm);

	Shader::TextureObject* getTexture() { return texture; }

private:
	Shader::PointRenderer pointIdRenderer;
	Shader::LineRenderer lineIdRenderer;
	Shader::TriangleRenderer triangleIdRenderer;

	Shader::FrameBufferObject frameBufferObject;
	Shader::TextureObject* texture;

	Graphics::ICamera* camera;
};
	}
}