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

	~Camera(void);

internal:
	Crystal::Graphics::ICamera* instance;
};
	}
}