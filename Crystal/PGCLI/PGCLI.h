#pragma once

using namespace System;

namespace PGCLI {

	public ref class OpenGLSimpleAdapter
	{
	public:
		OpenGLSimpleAdapter(HDC dc);
		~OpenGLSimpleAdapter(void);
		void Render();

		void BeginRender(void);

		void EndRender(void);

		void BeginRender(HDC hdc);
		void EndRender(HDC hdc);
		void EndRenderNoSwap(void);
		void EndRenderNoSwap(HDC hdc);
	internal:
		HDC m_hdc;
		HGLRC m_hglrc;
	};

}
