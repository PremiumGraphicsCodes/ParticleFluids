#pragma once

#include "../Scene/PointRenderer.h"
#include "../Scene/LineRenderer.h"
#include "../Scene/SmoothRenderer.h"

#include "../Shader/FrameBufferObject.h"
#include "../Shader/TextureObject.h"

//#include "TextureObjectRepository.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class GLObjectFactory;
	}
	namespace Scene {
		class ParticleSystemScene;
		class WireFrameScene;
		class PolygonMeshScene;
		class TextureScene;
		class MaterialScene;
		class LightScene;
		class SceneViewModel;

class SceneRenderer : private UnCopyable
{
public:
	SceneRenderer()
	{
	}

	~SceneRenderer() {}

	bool build(Shader::GLObjectFactory& factory);

	void render(Graphics::Camera* camera);

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

	void add(ParticleSystemScene* scene) { this->particleScenes.push_back(scene); }

	void add(WireFrameScene* scene) { this->wfScenes.push_back(scene); }

	void add(PolygonMeshScene* scene) { this->pmScenes.push_back(scene); }

	void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	void add(LightScene* scene) { this->lightScenes.push_back(scene); }

	PointRenderer* getPointRenderer() { return &pointRenderer; }

	LineRenderer* getLineRenderer() { return &wireRenderer; }

	SmoothRenderer* getSmoothRenderer() { return &smoothRenderer; }

	Graphics::Camera* getCamera() { return camera; }

private:
	PointRenderer pointRenderer;
	LineRenderer wireRenderer;
	SmoothRenderer smoothRenderer;

	Mask mask;

	Graphics::Camera* camera;

	Shader::TextureObject texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;

	std::vector<ParticleSystemScene*> particleScenes;
	std::vector<WireFrameScene*> wfScenes;
	std::vector<PolygonMeshScene*> pmScenes;
	std::vector<TextureScene*> textureScenes;
	std::vector<MaterialScene*> materialScenes;
	std::vector<LightScene*> lightScenes;
};
	}
}