#pragma once

#include "IShaderScene.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"
#include "../Shader/SmoothRenderer.h"
#include "TextureShaderScene.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "ScreenShaderScene.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderScene;

class ShaderRepository : public IShaderScene
{
public:
	explicit ShaderRepository(const std::string& name);

	~ShaderRepository() {}

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	void setBuffer(const ScreenShaderScene& buffer);

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

	//Shader::TextureObject getTexture() { return texture; }

	Shader::PointRenderer* getPointShader() { return pointRenderer; }

	Shader::LineRenderer* getWireShader() { return wireRenderer; }

	Shader::TriangleRenderer* getTriangleShader() { return triagleRenderer; }

	Shader::SmoothRenderer* getSmoothShader() { return smoothRenderer; }

	TextureShaderScene* getTextureScene() { return texture; }

private:
	Shader::PointRenderer* pointRenderer;
	Shader::LineRenderer* wireRenderer;
	Shader::TriangleRenderer* triagleRenderer;
	Shader::SmoothRenderer* smoothRenderer;

	Mask mask;

	TextureShaderScene* texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;
	ScreenShaderScene buffer;
};
	}
}