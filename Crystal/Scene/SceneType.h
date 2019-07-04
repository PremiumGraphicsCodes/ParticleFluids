#pragma once

namespace Crystal {
	namespace Model {

enum class SceneType
{
	None = 0,
	Root = 0x01,
	ParticleSystemScene = 0x02,
	WireFrameScene = 0x04,
	PolygonMeshScene = 0x08,
	VolumeScene = 0x10,
	LightScene = 0x20,
	MaterialScene = 0x40,
	TextureScene = 0x80,
	All = 0xFF,
};
	}
}