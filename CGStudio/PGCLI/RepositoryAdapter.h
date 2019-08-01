#pragma once

using namespace System;

namespace Crystal {
	namespace Scene {
		class RootScene;
	}
	namespace UI {
		class ViewModel3d;
	}
}

namespace PG {
	namespace CLI {
		ref class SceneAdapter;

public ref class RepositoryAdapter
{
public:
	RepositoryAdapter();

	~RepositoryAdapter(void);

	void Clear();

	void Init();

	bool Import(System::String^ filename);

	bool Export(System::String^ filename);

	SceneAdapter^ GetSceneAdapter();

	SceneAdapter^ GetItemAdapter();

private:
internal:
	Crystal::Scene::RootScene* instance;
};

	}
}
