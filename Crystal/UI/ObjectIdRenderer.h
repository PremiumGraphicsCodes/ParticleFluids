#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"

#include "../Shader/FrameBufferObject.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {
		class ObjectIdViewModel;

class ObjectIdRenderer : private UnCopyable
{
public:
	ObjectIdRenderer(Graphics::ICamera* camera) :
		camera(camera)
	{
	}

	~ObjectIdRenderer() {}

	bool build();

	void render();

	Graphics::DrawableID getId(const double x, const double y);

	void setViewModel(const ObjectIdViewModel& vm);

	Shader::TextureObject* getTexture() { return &texture; }

private:
	Shader::PointRenderer pointIdRenderer;
	Shader::LineRenderer lineIdRenderer;
	Shader::TriangleRenderer triangleIdRenderer;

	Shader::FrameBufferObject frameBufferObject;
	Shader::TextureObject texture;

	Graphics::ICamera* camera;
};
	}
}