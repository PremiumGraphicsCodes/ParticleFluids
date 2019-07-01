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
	VolumeObject = 0x10,
	LightObject = 0x20,
	MaterialObject = 0x40,
	TextureObject = 0x80,
	All = 0xFF,
};
	}
}