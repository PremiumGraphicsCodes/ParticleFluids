#include "stdafx.h"

#include "../Shader/PointRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "PGCLI.h"

#include "../Math/Vector3d.h"
#include "../Graphics/OrthogonalCamera.h"

#pragma once

using namespace PGCLI;

using namespace Crystal::Math;
using namespace Crystal::Graphics;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )


OpenGLSimpleAdapter::OpenGLSimpleAdapter(IntPtr handle) {
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

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	camera = new Crystal::Graphics::OrthogonalCamera();
	pointRenderer = new Crystal::Shader::PointRenderer();
	Crystal::Graphics::PointBuffer buffer;
	buffer.add(Vector3dd(0, 0, 0), ColorRGBAf(0, 0, 0, 0), 1.0f);
	pointRenderer->setBuffer(buffer);
	if (!pointRenderer->build()) {
		assert(false);
	}

	wglMakeCurrent(0, 0);

	//Crystal::Math::Vector3dd v;
	return;
}

OpenGLSimpleAdapter::~OpenGLSimpleAdapter(void)
{
	delete camera;
	delete pointRenderer;
}

void OpenGLSimpleAdapter::Render()
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	glViewport(0, 0, 512, 512);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pointRenderer->render(*camera);

	glFlush();
	wglMakeCurrent(this->m_hdc, 0);
	SwapBuffers(this->m_hdc);
}
