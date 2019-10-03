#pragma once

using namespace System;

namespace Crystal {
	namespace Scene {
		class World;
	}
	namespace UI {
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {
		ref class SceneAdapter;

public ref class WorldAdapter
{
public:
	WorldAdapter();

	~WorldAdapter(void);

	void Clear();

	void Init();

	//bool Import(System::String^ filename);

	//bool Export(System::String^ filename);

	SceneAdapter^ GetSceneAdapter();

	SceneAdapter^ GetItemAdapter();

internal:
	Crystal::Scene::World* instance;
};

	}
}
