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

	void Move(PG::Core::Math::Vector3d^ vector);

	void MoveTo(PG::Core::Math::Vector3d^ position);

	void Rotate(double azimuth, double elevation);

	void SetRotation(PG::Core::Math::Matrix3d^ matrix);

	void Zoom(double s);


internal:
	Crystal::Graphics::ICamera* instance;
};
	}
}