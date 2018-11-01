#pragma once

using namespace System;

namespace Crystal {
	namespace Shader {
		class PointRenderer;
	}
}

namespace PGCLI {

public ref class Renderer
{
public:
	Renderer(IntPtr handle);

	~Renderer(void);

	void Render();

internal:
	HDC m_hdc;
	HGLRC m_hglrc;
	//Crystal::Shader::PointRenderer* pointRenderer;
};

}
