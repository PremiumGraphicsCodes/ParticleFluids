#include "stdafx.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "PGCLI.h"

#pragma once

using namespace PGCLI;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )


OpenGLSimpleAdapter::OpenGLSimpleAdapter(HDC dc) {
		if (dc == 0) return;
		m_hdc = dc;
		{
			PIXELFORMATDESCRIPTOR _pfd = {
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL
				| PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
			};
			GLint iPixelFormat;
			if ((iPixelFormat = ChoosePixelFormat(m_hdc, &_pfd)) == 0)
				return;
			if (SetPixelFormat(m_hdc, iPixelFormat, &_pfd) == FALSE)
				return;
		}
		if ((m_hglrc = wglCreateContext(m_hdc)) == 0)
			return; // pure Managed だとランタイムでエラーに 
		if ((wglMakeCurrent(m_hdc, m_hglrc)) == 0)
			return;
		wglMakeCurrent(0, 0);
		return;
	}

OpenGLSimpleAdapter::~OpenGLSimpleAdapter(void)
{}

void OpenGLSimpleAdapter::Render()
{
		wglMakeCurrent(this->m_hdc, this->m_hglrc);
//		po();
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
}

void OpenGLSimpleAdapter::BeginRender(void)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	//	return this->m_hdc;
}

void OpenGLSimpleAdapter::EndRender(void) {
		SwapBuffers(this->m_hdc);
		wglMakeCurrent(NULL, NULL);
}

void OpenGLSimpleAdapter::BeginRender(HDC hdc) {
	wglMakeCurrent(hdc, this->m_hglrc);
}

void OpenGLSimpleAdapter::EndRender(HDC hdc)
{
		SwapBuffers(hdc);
		wglMakeCurrent(NULL, NULL);
}

void OpenGLSimpleAdapter::EndRenderNoSwap(void) {
		wglMakeCurrent(this->m_hdc, 0);
	}

	void OpenGLSimpleAdapter::EndRenderNoSwap(HDC hdc) {
		wglMakeCurrent(hdc, 0);
	}
