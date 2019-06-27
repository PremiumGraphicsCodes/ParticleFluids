#pragma once

using namespace System;

namespace Crystal {
	namespace Model {
		class IScene;
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

	bool IsSelected();

	void Select();

	void UnSelect();

	void SetSelected(bool b);

	PG::Core::Shape::ShapeType GetType();

	PG::Core::Math::Vector3d^ GetPositionById(int id);

internal:
	ObjectAdapter(Crystal::Model::IScene* instance);

	Crystal::Model::IScene* instance;
};

	}
}