#pragma once

#include "SceneIdProvider.h"
#include "PolygonMeshScene.h"
#include "ParticleSystemScene.h"
#include "WireFrameScene.h"
#include "LightScene.h"
#include "MaterialScene.h"

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
	namespace Shader {
		class ShaderObject;
	}
	namespace Scene {
		class Scene;
		class ShaderScene;
		class CameraScene;
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

	WireFrameScene* createWireFrameScene(const std::vector<Math::Line3dd>& lines, const WireFrameAttribute& attribute, const std::string& name);

	WireFrameScene* createWireFrameScene(Shape::WireFrame* wire, const WireFrameAttribute& attribute, const std::string& name);

	PolygonMeshScene* createPolygonMeshScene(Shape::PolygonMesh* mesh, const std::string& name);

	LightScene* createLightScene(const Graphics::PointLight& light, const std::string& name);

	MaterialScene* createMaterialScene(const Graphics::Material& material, const std::string& name);

	//ShaderScene* createShaderScene(const std::string& name);

	//CameraScene* createCameraScene(Graphics::ICamera* camera, const std::string& name);

	TransformScene* createTransformScene(const std::string& name);

	int getNextId() { return idProvider.getNextId(); }

private:
	SceneIdProvider idProvider;
};

	}
}