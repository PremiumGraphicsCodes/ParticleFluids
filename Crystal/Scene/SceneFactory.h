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

	Scene* createScene(const std::string& name);

	ParticleSystemScene* createParticleSystemScene(const Math::Vector3dd& position, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* createParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const ParticleAttribute& attribute, const std::string& name);

	ParticleSystemScene* createParticleSystemScene(const std::vector<Math::Vector3dd>& positions, const std::vector<ParticleAttribute>& attributes, const std::string& name);

	WireFrameScene* createWireFrameScene(std::unique_ptr<Shape::WireFrame> shape, const WireFrameAttribute& attribute, const std::string& name);

	PolygonMeshScene* createPolygonMeshScene(std::unique_ptr<Shape::PolygonMesh> mesh, const std::string& name);

	LightScene* createLightScene(std::unique_ptr<Graphics::PointLight> light, const std::string& name);

	MaterialScene* createMaterialScene(std::unique_ptr<Graphics::Material> material, const std::string& name);

	TextureScene* createTextureScene(const Graphics::Image& image, const std::string& name);

	//ShaderScene* createShaderScene(const std::string& name);

	//CameraScene* createCameraScene(Graphics::Camera* camera, const std::string& name);

	TransformScene* createTransformScene(const std::string& name);

	FaceGroupScene* createFaceGroupScene(PolygonMeshScene* parent, const std::string& name);

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider materialIdProvider;
	//SceneIdProvider textureIdProvier;
	SceneIdProvider idProvider;
};

	}
}