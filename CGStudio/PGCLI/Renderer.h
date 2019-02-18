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
		ref class ModelAdapter;
		ref class CameraAdapter;

public ref class Renderer
{
public:
	Renderer(IntPtr handle);

	~Renderer(void);

	bool Build(ModelAdapter^ model);

	void Render(int width, int height);

	void Update(ModelAdapter^ model);

	CameraAdapter^ camera;

	PG::Core::ObjectId Pick(PG::Core::Math::Vector2d^ position);

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::UI::ViewModel3d* viewModel3d;
	Crystal::Shader::PointRenderer* pointRenderer;
	Crystal::Shader::PointRenderer* pointIdRenderer;
	Crystal::Shader::WireFrameRenderer* wireFrameRenderer;
	Crystal::Shader::SmoothRenderer* triangleMeshRenderer;
};
	}
}