#pragma once

#include "../Graphics/DrawableId.h"

#include "../Shader/PointRenderer.h"
#include "../Shader/LineRenderer.h"
#include "../Shader/TriangleRenderer.h"
#include "../Shader/FrameBufferObject.h"

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
		camera(camera)
	{
	}

	~ObjectIdRenderer() {}

	bool build(Scene::IScene* scene, Scene::SceneFactory* factory);

	void init(Scene::IScene* scene, Scene::SceneFactory* factory);

	void render();

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	void setViewModel(const Scene::SceneIdViewModel& vm);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	Shader::PointRenderer pointIdRenderer;
	Shader::LineRenderer lineIdRenderer;
	Shader::TriangleRenderer triangleIdRenderer;

	Shader::FrameBufferObject frameBufferObject;
	Shader::TextureObject* texture;

	Graphics::ICamera* camera;
};
	}
}