#pragma once

#include "../Graphics/DrawableId.h"

#include "../Scene/TriangleRenderer.h"
#include "../Shader/FrameBufferObject.h"

#include "../Scene/PointRenderer.h"
#include "../Scene/LineRenderer.h"

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
	explicit SceneIdRenderer() :
		pointIdRenderer(-1, "PointShader"),
		lineIdRenderer(-1, "LineShader"),
		triangleIdRenderer(-1, "TriangleShader")
	{
	}

	~SceneIdRenderer() {}

	bool build();

	void render(Graphics::ICamera* camera, const Scene::SceneIdViewModel& vm);

	Graphics::DrawableID getId(const double x, const double y);

	Graphics::DrawableID getIdInTexCoord(const int x, const int y);

	//Shader::TextureObject* getTexture() { return texture; }

private:
	Scene::PointRenderer pointIdRenderer;
	Scene::LineRenderer lineIdRenderer;
	Scene::TriangleRenderer triangleIdRenderer;

	Shader::TextureObject texture;

	Shader::FrameBufferObject frameBufferObject;

	Graphics::ICamera* camera;
};
	}
}