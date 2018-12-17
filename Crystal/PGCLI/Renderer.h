#pragma once

using namespace System;

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
	namespace UI {
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {
		ref class Model;

public ref class Renderer
{
public:
	Renderer(IntPtr handle);

	~Renderer(void);

	void Render();

	void Update(Model^ model);

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::Graphics::ICamera* camera;
	Crystal::UI::ViewModel3d* viewModel3d;
	Crystal::Shader::PointRenderer* pointRenderer;
	Crystal::Shader::WireFrameRenderer* wireFrameRenderer;
};
	}
}