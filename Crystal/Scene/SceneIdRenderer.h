#pragma once

#include "../Graphics/DrawableId.h"

#include "../Scene/LineShaderScene.h"
#include "../Scene/TriangleShaderScene.h"
#include "../Shader/FrameBufferObject.h"

#include "../Scene/PointShaderScene.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {
		class IScene;
		class SceneFactory;
		class SceneIdViewModel;
	}
	namespace UI {

class SceneIdRenderer : private UnCopyable
{
public:
	explicit SceneIdRenderer(Graphics::ICamera* camera) :
		pointIdRenderer(-1, "PointShader"),
		lineIdRenderer(-1, "LineShader"),
		triangleIdRenderer(-1, "TriangleShader"),
		camera(camera)
	{
	}

	~SceneIdRenderer() {}

	bool build(Scene::IScene* scene, Scene::SceneFactory* factory);

	void render(const Scene::SceneIdViewModel& vm,const Shader::TextureObject& texture);

	Graphics::DrawableID getId(const double x, const double y, const Shader::TextureObject& texture);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y, const Shader::TextureObject& texture);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	Scene::PointShaderScene pointIdRenderer;
	Scene::LineShaderScene lineIdRenderer;
	Scene::TriangleShaderScene triangleIdRenderer;

	Shader::FrameBufferObject frameBufferObject;

	Graphics::ICamera* camera;
};
	}
}