#include "stdafx.h"

#include "../../Crystal/Shader/PointRenderer.h"
#include "../../Crystal/Shader/LineRenderer.h"
#include "../../Crystal/Shader/SmoothRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "Renderer.h"
#include "RepositoryAdapter.h"
#include "CameraAdapter.h"

#include "../../Crystal/UI/Repository.h"
#include "../../Crystal/UI/Renderer.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/OrthogonalCamera.h"
#include "../../Crystal/Graphics/PerspectiveCamera.h"
#include "../../Crystal/Scene/ViewModel.h"

#pragma once

using namespace PG::CLI;

using namespace Crystal::Math;
using namespace Crystal::Graphics;

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "User32.lib" )


Renderer::Renderer(IntPtr handle, RepositoryAdapter^ repository) {
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
		return;
	}

	wglMakeCurrent(0, 0);


	//Crystal::Math::Vector3dd v;
	return;
}

Renderer::~Renderer(void)
{
	delete instance;
}

bool Renderer::Build(RepositoryAdapter^ repository)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	//wglMakeCurrent(this->m_hdc, 0);

	auto scene = repository->instance->getObjects();
	auto factory = repository->instance->getObjectFactory();
	{
		Image image1(512, 512);
		scene->addScene( factory->createTextureScene(image1, "OnScreenTexture") );

		Image image2(2, 2);
		image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
		image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
		image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
		image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
		scene->addScene( factory->createTextureScene(image2, "SmoothTexture") );
	}

	instance = new Crystal::UI::Renderer(camera->instance);
	instance->build(*repository->instance->getShaders()->getShaders(), scene, factory);

	wglMakeCurrent(0, 0);


	return true;
}

bool Renderer::Render(int width, int height, RepositoryAdapter^ repository)
{
	if (wglMakeCurrent(this->m_hdc, this->m_hglrc)) {
		instance->render(width, height, repository->instance->getObjects());
		wglMakeCurrent(this->m_hdc, 0);
		SwapBuffers(this->m_hdc);
		return true;
	}
	return false;
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

void Renderer::Update(RepositoryAdapter^ model)
{
	auto vm = model->instance->toViewModel();
	instance->setViewModel(vm);
	::fitCamera(camera->instance, model->instance->getBoundingBox());
	//viewModel3d->add(model->instance.)
}

PG::Core::ObjectId Renderer::Pick(PG::Core::Math::Vector2d^ position, int mergin)
{
	PG::Core::ObjectId result;

	const auto texWidth = instance->getObjectIdRenderer()->getTexture()->getWidth();
	const auto texHeight = instance->getObjectIdRenderer()->getTexture()->getHeight();

	const auto positionInTexCoordX = texWidth * position->X;
	const auto positionInTexCoordY = texHeight * position->Y;
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	for (int x = -mergin; x <= mergin; ++x) {
		for (int y = -mergin; y <= mergin; ++y) {
			const auto xx = positionInTexCoordX + x;
			const auto yy = positionInTexCoordY + y;
			const auto id = instance->getObjectIdRenderer()->getIdInTexCoord(xx, yy);

			if (id.getParentId() != 0) {
				result.parentId = id.getParentId();
				result.childId = id.getChildId();
			}
		}
	}
	wglMakeCurrent(this->m_hdc, 0);

	return result;
}