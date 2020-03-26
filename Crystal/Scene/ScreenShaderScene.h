#pragma once

#include "../Scene/PointShader.h"
#include "../Scene/LineShaderScene.h"
#include "../Scene/SmoothShaderScene.h"

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

class ScreenShaderScene : private UnCopyable
{
public:
	ScreenShaderScene()
	{
	}

	~ScreenShaderScene() {}

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

	void add(ParticleSystemScene* scene);

	void add(WireFrameScene* scene);

	void add(PolygonMeshScene* scene);

	void add(TextureScene* scene) { this->textureScenes.push_back(scene); }

	void add(MaterialScene* scene) { this->materialScenes.push_back(scene); }

	void add(LightScene* scene) { this->lightScenes.push_back(scene); }

	PointShader* getPointRenderer() { return &pointRenderer; }

	LineShaderScene* getLineRenderer() { return &wireRenderer; }

	SmoothShaderScene* getSmoothRenderer() { return &smoothRenderer; }

	Graphics::Camera* getCamera() { return camera; }

private:
	PointShader pointRenderer;
	LineShaderScene wireRenderer;
	SmoothShaderScene smoothRenderer;

	Mask mask;

	Graphics::Camera* camera;

	Shader::TextureObject texture;
	std::unique_ptr< Shader::FrameBufferObject > frameBufferObject;

	std::vector<PointShaderBuffer> pointBuffers;
	std::vector<LineShaderBuffer> lineBuffers;
	std::vector<SmoothShaderBuffer> pmScenes;
	std::vector<TextureScene*> textureScenes;
	std::vector<MaterialScene*> materialScenes;
	std::vector<LightScene*> lightScenes;
};
	}
}