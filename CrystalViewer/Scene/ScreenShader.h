#pragma once

#include "IShaderScene.h"

#include "Crystal/Shader/PointRenderer.h"
#include "Crystal/Shader/LineRenderer.h"
#include "Crystal/Shader/TriangleRenderer.h"
#include "Crystal/Shader/SmoothRenderer.h"

#include "Crystal/Shader/FrameBufferObject.h"
#include "Crystal/Shader/TextureObject.h"
#include "Crystal/Shader/ShaderBuildStatus.h"

#include "MaterialShaderScene.h"

#include "Crystal/Util/UnCopyable.h"
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

	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory);

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

	Shader::TextureObject* getTexture() { return texture; }

	Shader::PointRenderer* getPointShader() { return pointRenderer; }

	Shader::LineRenderer* getWireShader() { return wireRenderer; }

	Shader::TriangleRenderer* getTriangleShader() { return triagleRenderer; }

	Shader::SmoothRenderer* getSmoothShader() { return smoothRenderer; }

	void addScene(IShaderScene* scene) { this->scenes.push_back(scene); }

	void removeScene(IShaderScene* scene) { this->scenes.remove(scene); }

	MaterialShaderScene* getMateialScene() { return &this->materialScene; }

private:
	Shader::PointRenderer* pointRenderer;
	Shader::LineRenderer* wireRenderer;
	Shader::TriangleRenderer* triagleRenderer;
	Shader::SmoothRenderer* smoothRenderer;

	std::list<IShaderScene*> scenes;
	MaterialShaderScene materialScene;

	Mask mask;

	Shader::TextureObject* texture;
	Shader::FrameBufferObject* frameBufferObject;
};
	}
}