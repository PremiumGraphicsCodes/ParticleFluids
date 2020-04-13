#pragma once

#include "SceneIdProvider.h"

#include <string>
#include "../Math/Vector3d.h"

#include "../Graphics/Material.h"
#include "../Graphics/PointLight.h"

namespace Crystal {
	namespace Graphics {
		class Image;
		class Camera;
	}
	namespace Shader {
		class ShaderObject;
		class TextureObject;
	}
	namespace Shape {
		class WireFrame;
		class TriangleMesh;
		class PolygonMesh;
	}
	namespace Scene {
		class Scene;
		class IRenderer;
		class CameraScene;
		class ParticleSystemScene;
		struct ParticleAttribute;
		class WireFrameScene;
		struct WireFrameAttribute;
		class TriangleMeshScene;
		class PolygonMeshScene;
		class FaceGroupScene;
		class TransformScene;
		class TextureScene;
		class LightScene;
		class MaterialScene;

class SceneFactory
{
public:
	SceneFactory();

	~SceneFactory();

	void clear();

	int getNextId() { return idProvider.getNextId(); }

private:
	//SceneIdProvider textureIdProvier;
	SceneIdProvider idProvider;
};

	}
}