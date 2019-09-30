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
		ref class RepositoryAdapter;
		ref class CameraAdapter;

public ref class Renderer
{
public:
	Renderer(IntPtr handle, RepositoryAdapter^ repository);

	~Renderer(void);

	bool Build(RepositoryAdapter^ model);

	bool Render(int width, int height, RepositoryAdapter^ repository, CameraAdapter^ camera);

	void Update(RepositoryAdapter^ model);

	CameraAdapter^ camera;

	PG::Core::ObjectId Pick(PG::Core::Math::Vector2d^ position, int mergin);

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	Crystal::UI::ViewModel3d* viewModel3d;
	RepositoryAdapter^ repository;
};
	}
}