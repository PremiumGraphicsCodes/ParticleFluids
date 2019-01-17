#include "stdafx.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/WireFrameRenderer.h"
#include "../Shader/SmoothRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "Renderer.h"
#include "ModelAdapter.h"
#include "CameraAdapter.h"

#include "../UI/Model.h"
#include "../Math/Vector3d.h"
#include "../Graphics/OrthogonalCamera.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../UI/ViewModel3d.h"

#pragma once

using namespace PG::CLI;

using namespace Crystal::Math;
using namespace Crystal::Graphics;

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

	camera = gcnew CameraAdapter();
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(1);
	}

	pointRenderer = new Crystal::Shader::PointRenderer();
	//Crystal::Graphics::PointBuffer buffer;
	//buffer.add(Vector3dd(0, 0, 0), ColorRGBAf(0, 0, 0, 0), 1.0f);
	//pointRenderer->setBuffer(buffer);
	if (!pointRenderer->build()) {
		assert(false);
	}

	pointIdRenderer = new Crystal::Shader::PointRenderer();
	if (!pointIdRenderer->build()) {
		assert(false);
	}

	wireFrameRenderer = new Crystal::Shader::WireFrameRenderer();
	if(!wireFrameRenderer->build()) {
		assert(false);
	}

	triangleMeshRenderer = new Crystal::Shader::SmoothRenderer();
	if (!triangleMeshRenderer->build()) {
		assert(false);
	}

	wglMakeCurrent(0, 0);

	//Crystal::Math::Vector3dd v;
	return;
}

Renderer::~Renderer(void)
{
	delete triangleMeshRenderer;
	delete wireFrameRenderer;
	delete pointIdRenderer;
	delete pointRenderer;
}

void Renderer::Render(int width, int height)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pointRenderer->render(*(camera->instance));

	glFlush();
	wglMakeCurrent(this->m_hdc, 0);
	SwapBuffers(this->m_hdc);
}

namespace {
	void fitCamera(ICamera* camera, const Box3d& boundingBox)
	{
		const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
		camera->setNear(dist * 0.1f);
		camera->setFar(dist * 10.0f);
		camera->setTarget(boundingBox.getCenter());
		camera->moveTo(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0));
	}
}

void Renderer::Update(ModelAdapter^ model)
{
	const auto& vm = model->instance->toViewModel();
	pointRenderer->setBuffer(vm.getPointBuffer());
	::fitCamera(camera->instance, model->instance->getBoundingBox());
	//viewModel3d->add(model->instance.)
}

PG::Core::ObjectId Renderer::Pick(PG::Core::Math::Vector2d^ position)
{
	PG::Core::ObjectId id;
	id.parentId = 0;
	id.childId = 0;
	return id;
}
