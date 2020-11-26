#pragma once

namespace Crystal {
	namespace Scene {

enum class SceneType
{
	None = 0,
	Root = 0x01,
	ParticleSystemScene = 0x02,
	WireFrameScene = 0x04,
	TriangleMeshScene = 0x08,
	PolygonMeshScene = 0x10,
	CSGScene = 0x20,
	LightScene = 0x40,
	MaterialScene = 0x80,
	TextureScene = 0xf0,
	ShaderScene = 0xf1,
	CameraScene = 0xf2,
	TransformScene = 0xf3,
	FaceGroupScene = 0xf4,
	All = 0xFF,
};

static bool isShapeScene(const SceneType& type)
{
	if (type == SceneType::ParticleSystemScene
		|| type == SceneType::WireFrameScene
		|| type == SceneType::TriangleMeshScene
		|| type == SceneType::CSGScene) {
		return true;
	}
	return false;
}
	}
}