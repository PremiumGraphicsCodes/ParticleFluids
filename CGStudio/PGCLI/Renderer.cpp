#include "stdafx.h"

#include "../../Crystal/Scene/PointRenderer.h"
#include "../../Crystal/Scene/LineRenderer.h"
#include "../../Crystal/Scene/SmoothRenderer.h"

#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 


#include "Renderer.h"
#include "RepositoryAdapter.h"
#include "CameraAdapter.h"

#include "../../Crystal/Scene/World.h"
#include "../../Crystal/Scene/Renderer.h"
#include "../../Crystal/Math/Vector3d.h"
#include "../../Crystal/Graphics/OrthogonalCamera.h"
#include "../../Crystal/Graphics/PerspectiveCamera.h"
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

	this->repository = repository;

	//Crystal::Math::Vector3dd v;
	return;
}

Renderer::~Renderer(void)
{
}

bool Renderer::Build(RepositoryAdapter^ repository)
{
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	//wglMakeCurrent(this->m_hdc, 0);

	repository->instance->init();
	repository->instance->getRenderer()->build();

	wglMakeCurrent(0, 0);


	return true;
}

bool Renderer::Render(int width, int height, RepositoryAdapter^ repository, CameraAdapter^ camera)
{
	if (wglMakeCurrent(this->m_hdc, this->m_hglrc)) {
		repository->instance->getRenderer()->render(width, height, repository->instance->getViewModel());
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
	model->instance->updateViewModel();
	::fitCamera(camera->instance, model->instance->getBoundingBox());
	//viewModel3d->add(model->instance.)
}

PG::Core::ObjectId Renderer::Pick(PG::Core::Math::Vector2d^ position, int mergin)
{
	PG::Core::ObjectId result;
	wglMakeCurrent(this->m_hdc, this->m_hglrc);
	auto selectedId = repository->instance->getRenderer()->getObjectIdRenderer()->getId(position->X, position->Y);
	wglMakeCurrent(this->m_hdc, 0);

	PG::Core::ObjectId id;
	id.parentId = selectedId.getParentId();
	id.childId = selectedId.getChildId();
	return id;
/*
	model->instance->findObjectById(idTex);
	if (idTex.getParentId() == Crystal::Scene::SceneType::ParticleSystemScene) {

	}

	const auto texWidth = idTex->getTexture()->getWidth();
	const auto texHeight = idTex->getTexture()->getHeight();

	const auto positionInTexCoordX = texWidth * position->X;
	const auto positionInTexCoordY = texHeight * position->Y;
	for (int x = -mergin; x <= mergin; ++x) {
		for (int y = -mergin; y <= mergin; ++y) {
			const auto xx = positionInTexCoordX + x;
			const auto yy = positionInTexCoordY + y;
			const auto id = instance->getObjectIdRenderer()->getIdInTexCoord(xx, yy, *idTex->getTexture());

			if (id.getParentId() != 0) {
				result.parentId = id.getParentId();
				result.childId = id.getChildId();
			}
		}
	}
	*/

	return result;
}