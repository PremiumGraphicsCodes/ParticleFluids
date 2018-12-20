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
		ref class Camera;

public ref class Renderer
{
public:
	Renderer(IntPtr handle);

	~Renderer(void);

	void Render(int width, int height);

	void Update(Model^ model);

	Camera^ camera;

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::UI::ViewModel3d* viewModel3d;
	Crystal::Shader::PointRenderer* pointRenderer;
	Crystal::Shader::WireFrameRenderer* wireFrameRenderer;
	Crystal::Shader::SmoothRenderer* triangleMeshRenderer;
};
	}
}