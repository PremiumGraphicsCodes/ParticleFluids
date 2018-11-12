#pragma once

using namespace System;

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
	namespace Shader {
		class PointRenderer;
	}
}

namespace PG {
	namespace CLI {

public ref class Renderer
{
public:
	Renderer(IntPtr handle);

	~Renderer(void);

	void Render();

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::Graphics::ICamera* camera;
	Crystal::Shader::PointRenderer* pointRenderer;
};
	}
}