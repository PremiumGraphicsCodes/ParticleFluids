#pragma once

#include "../Scene/PointRenderer.h"
#include "../Scene/LineRenderer.h"
#include "../Scene/SmoothRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class ParticleSystemScene;
		class WireFrameScene;
		class PolygonMeshScene;
		class SceneViewModel;
	}
	namespace Shader {
		class GLObjectFactory;
	}
	namespace UI {


class SceneRenderer : private UnCopyable
{
public:
	SceneRenderer()
	{
	}

	~SceneRenderer() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera, const Scene::SceneViewModel& vm);

	struct Mask
	{
		Mask() :
			showPoints(true),
			showLines(true),
			showTrianlges(true)
		{}

		bool showPoints;
		bool showLines;
		bool showTrianlges;
	};

	void setMask(const Mask& mask) { this->mask = mask; }

	Mask getMask() const { return mask; }

	Shader::TextureObject getTexture() { return texture; }

	void add(Scene::ParticleSystemScene* scene) { this->particleScenes.push_back(scene); }

	void add(Scene::WireFrameScene* scene) { this->wfScenes.push_back(scene); }

	void add(Scene::PolygonMeshScene* scene) { this->pmScenes.push_back(scene); }

private:
	Scene::PointRenderer pointRenderer;
	Scene::LineRenderer wireRenderer;
	Scene::SmoothRenderer smoothRenderer;

	Mask mask;

	Graphics::Camera* camera;

	Shader::TextureObject texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;

	std::vector<Scene::ParticleSystemScene*> particleScenes;
	std::vector<Scene::WireFrameScene*> wfScenes;
	std::vector<Scene::PolygonMeshScene*> pmScenes;

};
	}
}