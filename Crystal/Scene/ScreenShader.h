#pragma once

#include "IShader.h"

#include "../Scene/PointShader.h"
#include "../Scene/LineShader.h"
#include "../Scene/SmoothShader.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "ScreenShaderScene.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderScene;

class ScreenShader : public IShader
{
public:
	ScreenShader()
	{
	}

	~ScreenShader() {}

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void setBuffer(Graphics::Camera* camera, const ScreenShaderScene& buffer);

	void render();

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

	PointShader* getPointShader() { return &pointRenderer; }

	LineShader* getWireShader() { return &wireRenderer; }

	SmoothShader* getSmoothShader() { return &smoothRenderer; }

private:
	PointShader pointRenderer;
	LineShader wireRenderer;
	SmoothShader smoothRenderer;

	Mask mask;

	Graphics::Camera* camera;

	Shader::TextureObject texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;
	ScreenShaderScene buffer;
};
	}
}