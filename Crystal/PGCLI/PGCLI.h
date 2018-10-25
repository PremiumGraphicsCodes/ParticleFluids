#pragma once

using namespace System;

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
	};

}
