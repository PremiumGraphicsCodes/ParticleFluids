#pragma once

using namespace System;

namespace Crystal {
	namespace Graphics {
		class ICamera;
	}
}

namespace PG {
	namespace CLI {

ref class RepositoryAdapter;

public ref class CameraAdapter
{
public:
	CameraAdapter();

	~CameraAdapter(void);

	void Move(PG::Core::Math::Vector3d^ vector);

	void MoveTo(PG::Core::Math::Vector3d^ position);

	void Rotate(double azimuth, double elevation);

	void SetRotation(PG::Core::Math::Matrix3d^ matrix);

	void Zoom(double s);

	void PG::CLI::CameraAdapter::Fit(PG::Core::Math::Box3d^ boundingBox);

	PG::Core::Math::Matrix4d^ ModelViewMatrix();

	PG::Core::Math::Matrix4d^ ProjectionMatrix();

internal:
	Crystal::Graphics::ICamera* instance;
};
	}
}