#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class IObject;
	}
}

namespace PG {
	namespace CLI {

public ref class ObjectAdapter
{
public:
	~ObjectAdapter(void);

	int GetId();

	System::String^ GetName();

	void SetName(System::String^ name);

	bool GetVisible();

	void SetVisible(bool visible);

	void Move(PG::Core::Math::Vector3d^ v);

	void Transform(PG::Core::Math::Matrix3d^ m);

	void Transform(PG::Core::Math::Matrix4d^ m);

	//void Scale(PG::Core::Math::Vector3d^ s);

	//void Rotate(double rx, double ry, double rz);

	bool IsSelected();

	void Select();

	void UnSelect();

	void SetSelected(bool b);

	PG::Core::Shape::ShapeType GetType();

internal:
	ObjectAdapter(Crystal::Model::IObject* instance);

	Crystal::Model::IObject* instance;
};

	}
}