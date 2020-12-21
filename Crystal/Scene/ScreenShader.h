#pragma once

#include "IShaderScene.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

#include "MaterialShaderScene.h"
//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"
#include <memory>

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderScene;

class ScreenShader
{
public:
	explicit ScreenShader(const std::string& name);

	~ScreenShader() {}

	bool build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	//void setBuffer(const ScreenShaderScene& buffer);

	void render(const Graphics::Camera& camera);

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

	Shader::TextureObject* getTextureScene() { return texture; }

	void addScene(IShaderScene* scene) { this->scenes.push_back(scene); }

	void removeScene(IShaderScene* scene) { this->scenes.remove(scene); }

	MaterialShaderScene* getMateialBuffer() { return &this->materialBuffer; }

private:
	Shader::PointRenderer* pointRenderer;
	Shader::LineRenderer* wireRenderer;
	Shader::TriangleRenderer* triagleRenderer;
	Shader::SmoothRenderer* smoothRenderer;

	std::list<IShaderScene*> scenes;
	MaterialShaderScene materialBuffer;

	Mask mask;

	Shader::TextureObject* texture;
	Shader::FrameBufferObject* frameBufferObject;
};
	}
}