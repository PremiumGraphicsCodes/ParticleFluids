#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBuffer.h"

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
	Shader::WireFrameRenderer lineIdRenderer;

	Shader::FrameBuffer frameBufferObject;
	Shader::TextureObject texture;

	Graphics::ICamera* camera;
};
	}
}