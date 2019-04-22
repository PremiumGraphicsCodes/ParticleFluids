#pragma once

namespace Crystal {
	namespace Model {

enum class ObjectType
{
	None = 0,
	ParticleSystemObject = 0x01,
	WireFrameObject = 0x02,
	PolygonMeshObject = 0x04,
	LightObject = 0x08,
	MaterialObject = 0x10,
	TextureObject = 0x20,
	All = 0xFF,
};
	}
}