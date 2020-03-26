#pragma once

#include "../Scene/PointShader.h"
#include "../Scene/LineShaderScene.h"
#include "../Scene/SmoothShader.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderBuffer;

class ScreenShaderScene : private UnCopyable
{
public:
	ScreenShaderScene()
	{
	}

	~ScreenShaderScene() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera, const ScreenShaderBuffer& buffer);

	struct Mask
	{
		Mask() :
			showPoints(true),
			showLines(true),
			showTrianlges(true)
		{}

		bool showPoints;
		bool showLines;
		bool showTrianlges;
	};

	void setMask(const Mask& mask) { this->mask = mask; }

	Mask getMask() const { return mask; }

	Shader::TextureObject getTexture() { return texture; }

	Graphics::Camera* getCamera() { return camera; }

private:
	PointShader pointRenderer;
	LineShaderScene wireRenderer;
	SmoothShader smoothRenderer;

	Mask mask;

	Graphics::Camera* camera;

	Shader::TextureObject texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;

};
	}
}