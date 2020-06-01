#pragma once

using namespace System;

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
	namespace UI {
		class ViewModel3d;
		class Renderer;
	}
}

namespace PG {
	namespace CLI {
		ref class WorldAdapter;
		ref class CameraAdapter;

public ref class Renderer
{
public:
	Renderer(IntPtr handle, WorldAdapter^ repository);

	~Renderer(void);

	bool Build(WorldAdapter^ model);

	bool Render(int width, int height, WorldAdapter^ repository);

	void Update(WorldAdapter^ model);

	bool Bind();

	bool UnBind();

	void ShowOffScreen(bool showOffScreen);

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::UI::ViewModel3d* viewModel3d;
	WorldAdapter^ repository;
};
	}
}