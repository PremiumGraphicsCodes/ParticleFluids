#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"
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

class ObjectIdRenderer : private UnCopyable
{
public:
	explicit ObjectIdRenderer(Graphics::ICamera* camera) :
		pointIdRenderer(-1, "PointShader"),
		camera(camera)
	{
	}

	~ObjectIdRenderer() {}

	bool build(Scene::IScene* scene, Scene::SceneFactory* factory);

	void render(const Shader::TextureObject& texture);

	Graphics::DrawableID getId(const double x, const double y, const Shader::TextureObject& texture);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y, const Shader::TextureObject& texture);

	void setViewModel(const Scene::SceneIdViewModel& vm);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	Scene::PointShaderScene pointIdRenderer;
	Shader::LineRenderer lineIdRenderer;
	Shader::TriangleRenderer triangleIdRenderer;

	Shader::FrameBufferObject frameBufferObject;

	Graphics::ICamera* camera;
};
	}
}