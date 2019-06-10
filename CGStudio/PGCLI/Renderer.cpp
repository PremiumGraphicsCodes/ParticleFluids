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
#include "../../Crystal/UI/ViewModel.h"

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

	auto textures = repository->instance->getShaders()->getTextures();
	{
		Image image1(512, 512);
		const auto mainTextureId = textures->add(image1, "MainTexture");
		auto mainTexture = textures->findObjectById(mainTextureId);
		textures->setOnScreenTexture(mainTexture);

		Image image2(2, 2);
		image2.setColor(0, 0, ColorRGBAuc(255, 0, 0, 0));
		image2.setColor(1, 0, ColorRGBAuc(0, 255, 0, 0));
		image2.setColor(0, 1, ColorRGBAuc(0, 0, 255, 0));
		image2.setColor(1, 1, ColorRGBAuc(255, 255, 255, 0));
		textures->add(image2, "SampleTexture");
	}

	instance = new Crystal::UI::Renderer(camera->instance);
	instance->build(*repository->instance->getShaders()->getShaders(), *textures);

	wglMakeCurrent(0, 0);


	return true;
}

void Renderer::Render(int width, int height, RepositoryAdapter^ repository)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	const auto& textures = *repository->instance->getShaders()->getTextures();
	instance->render(width, height, textures);
	/*
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pointRenderer->render(*(camera->instance));
	wireFrameRenderer->render(*(camera->instance));

	glFlush();
	*/
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

void Renderer::Update(RepositoryAdapter^ model)
{
	auto vm = model->instance->toViewModel();
	instance->setViewModel(vm);
	::fitCamera(camera->instance, model->instance->getBoundingBox());
	//viewModel3d->add(model->instance.)
}

PG::Core::ObjectId Renderer::Pick(PG::Core::Math::Vector2d^ position)
{
	const auto id = instance->getObjectIdRenderer()->getId(position->X, position->Y);
	PG::Core::ObjectId result;
	result.parentId = id.getParentId();
	result.childId = id.getChildId();
	return result;
}

/*
void PickUICtrl::onLeftButtonDown(const Vector2df& position)
{
	const auto x = position.x;
	const auto y = position.y;

	std::cout << x << " " << y << std::endl;

	const auto id = canvas->getRenderer()->getObjectIdRenderer()->getId(x, y);
	const auto parentId = id.getParentId();
	const auto childId = id.getChildId();
	if (parentId == 0) {
		return;
	}
	auto object = model->getObjects()->findObjectById(parentId);
	if (object != nullptr) {
		const bool masked = (int)type && (int)object->getType();
		if (masked) {
			function(parentId, childId);
		}
	}
}
*/