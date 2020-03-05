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
	ShapeScene = ParticleSystemScene | WireFrameScene | TriangleMeshScene | PolygonMeshScene,
	FaceGroupScene = 0x20,
	LightScene = 0x40,
	MaterialScene = 0x80,
	TextureScene = 0xf0,
	ShaderScene = 0xf1,
	CameraScene = 0xf2,
	TransformScene = 0xf3,
	All = 0xFF,
};
	}
}