#include "stdafx.h"

#include "../../Crystal/Scene/PointRenderer.h"
#include "../../Crystal/Scene/LineRenderer.h"
#include "../../Crystal/Scene/SmoothRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "Renderer.h"
#include "WorldAdapter.h"

#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/Renderer.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Scene/ViewModel.h"

#pragma once

using namespace PG::CLI;

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Scene;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )

Renderer::Renderer(IntPtr handle, WorldAdapter^ repository) {
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
		return;
	}

	wglMakeCurrent(0, 0);

	this->repository = repository;

	//Crystal::Math::Vector3dd v;
	return;
}

Renderer::~Renderer(void)
{
}

bool Renderer::Build(WorldAdapter^ repository)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	//wglMakeCurrent(this->m_hdc, 0);

	repository->instance->init();
	repository->instance->getRenderer()->build();

	wglMakeCurrent(0, 0);


	return true;
}

bool Renderer::Render(int width, int height, WorldAdapter^ repository)
{
	if (wglMakeCurrent(this->m_hdc, this->m_hglrc)) {
		repository->instance->getRenderer()->render(width, height, repository->instance->getViewModel());
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
		return true;
	}
	return false;
}

void Renderer::Update(WorldAdapter^ model)
{
	model->instance->updateViewModel();
	//viewModel3d->add(model->instance.)
}

bool Renderer::Bind()
{
	return wglMakeCurrent(this->m_hdc, this->m_hglrc);
}

bool Renderer::UnBind()
{
	return wglMakeCurrent(this->m_hdc, 0);
}