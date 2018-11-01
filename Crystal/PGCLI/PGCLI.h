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

namespace PGCLI {

	public ref class OpenGLSimpleAdapter
	{
	public:
		OpenGLSimpleAdapter(IntPtr handle);

		~OpenGLSimpleAdapter(void);

		void Render();

	internal:
		HDC m_hdc;
		HGLRC m_hglrc;
		Crystal::Graphics::ICamera* camera;
		Crystal::Shader::PointRenderer* pointRenderer;
	};

}
