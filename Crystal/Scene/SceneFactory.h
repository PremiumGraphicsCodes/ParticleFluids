#pragma once

#include "SceneIdProvider.h"
#include "LightScene.h"
#include "MaterialScene.h"
#include "TextureScene.h"
#include "../Math/Line3d.h"

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
	namespace Shader {
		class ShaderObject;
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

	WireFrameScene* createWireFrameScene(Shape::WireFrame* shape, const WireFrameAttribute& attribute, const std::string& name);

	PolygonMeshScene* createPolygonMeshScene(Shape::PolygonMesh* mesh, const std::string& name);

	LightScene* createLightScene(const Graphics::PointLight& light, const std::string& name);

	MaterialScene* createMaterialScene(const Graphics::Material& material, const std::string& name);

	TextureScene* createTextureScene(const Graphics::Image& image, const std::string& name);

	//ShaderScene* createShaderScene(const std::string& name);

	//CameraScene* createCameraScene(Graphics::ICamera* camera, const std::string& name);

	TransformScene* createTransformScene(const std::string& name);

	FaceGroupScene* createFaceGroupScene(PolygonMeshScene* parent, const std::string& name);

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider idProvider;
};

	}
}