#pragma once

namespace Crystal {
	namespace Model {

enum class ObjectType
{
	None = 0,
	ParticleSystemObject = 1,
	WireFrameObject = 2,
	PolygonMeshObject = 4,
	LightObject = 8,
	MaterialObject = 16,
	TextureObject = 32,
};
	}
}