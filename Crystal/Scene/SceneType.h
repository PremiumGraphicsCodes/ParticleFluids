#pragma once

namespace Crystal {
	namespace Scene {

enum class SceneType
{
	None = 0,
	Root = 0x01,
	ParticleSystemScene = 0x02,
	WireFrameScene = 0x04,
	PolygonMeshScene = 0x08,
	FaceGroupScene = 0x10,
	LightScene = 0x20,
	MaterialScene = 0x40,
	TextureScene = 0x80,
	ShaderScene = 0xf0,
	CameraScene = 0xf1,
	TransformScene = 0xf2,
	All = 0xFF,
};
	}
}