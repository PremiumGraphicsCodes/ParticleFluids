#include "stdafx.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "Renderer.h"

#pragma once

using namespace PGCLI;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )


Renderer::Renderer(IntPtr handle) {
	HWND hWnd = (HWND)handle.ToInt32();
	HDC     dc = ::GetDC(hWnd);
	if (dc == 0) {
		return;
	}
	
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
		if ((iPixelFormat = ChoosePixelFormat(m_hdc, &_pfd)) == 0) {
			return;
		}
		if (SetPixelFormat(m_hdc, iPixelFormat, &_pfd) == FALSE) {
			return;
		}
	}
	if ((m_hglrc = wglCreateContext(m_hdc)) == 0) {
		return; // pure Managed だとランタイムでエラーに 
	}
	if ((wglMakeCurrent(m_hdc, m_hglrc)) == 0) {
		return;
	}

	/*
	this->pointRenderer = new Crystal::Shader::PointRenderer();
	if (!pointRenderer->build()) {
		assert(false);
		return;
	}
	*/

	wglMakeCurrent(0, 0);
	return;
}

Renderer::~Renderer(void)
{
	//delete this->pointRenderer;
}

void Renderer::Render()
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	glViewport(0, 0, 512, 512);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	wglMakeCurrent(this->m_hdc, 0);
	SwapBuffers(this->m_hdc);
}
