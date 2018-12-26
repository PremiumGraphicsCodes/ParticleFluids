#pragma once

using namespace System;

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
}

namespace PG {
	namespace CLI {

ref class Model;

public ref class Camera
{
public:
	Camera();

	void Move(PG::Core::Math::Vector3d^ vector);

	void MoveTo(PG::Core::Math::Vector3d^ position);

	~Camera(void);

internal:
	Crystal::Graphics::ICamera* instance;
};
	}
}