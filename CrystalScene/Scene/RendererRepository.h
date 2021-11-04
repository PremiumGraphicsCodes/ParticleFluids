#pragma once

#include "Crystal/Shader/ShaderBuildStatus.h"
#include "Crystal/Shader/PointRenderer.h"
#include "Crystal/Shader/LineRenderer.h"
#include "Crystal/Shader/TriangleRenderer.h"
#include "Crystal/Shader/SmoothRenderer.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ScreenShaderScene;

class RendererRepository
{
public:
	RendererRepository();

	~RendererRepository();

	Shader::ShaderBuildStatus build(Shader::GLObjectFactory& factory);

	void release(Shader::GLObjectFactory& factory);

	Shader::PointRenderer* getPointShader() { return pointRenderer; }

	Shader::LineRenderer* getWireShader() { return wireRenderer; }

	Shader::TriangleRenderer* getTriangleShader() { return triagleRenderer; }

	Shader::SmoothRenderer* getSmoothShader() { return smoothRenderer; }

private:
	Shader::PointRenderer* pointRenderer;
	Shader::LineRenderer* wireRenderer;
	Shader::TriangleRenderer* triagleRenderer;
	Shader::SmoothRenderer* smoothRenderer;
};

	}
}