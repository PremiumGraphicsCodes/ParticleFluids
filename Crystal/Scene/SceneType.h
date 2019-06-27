#pragma once

namespace Crystal {
	namespace Model {

enum class SceneType
{
	None = 0,
	ParticleSystemScene = 0x01,
	WireFrameScene = 0x02,
	PolygonMeshScene = 0x04,
	VolumeObject = 0x08,
	LightObject = 0x10,
	MaterialObject = 0x20,
	TextureObject = 0x40,
	All = 0xFF,
};
	}
}