#pragma once

using namespace System;

namespace Crystal {
	namespace Scene {
		class Scene;
		class SceneFactory;
	}
}

namespace PG {
	namespace CLI {

public ref class SceneAdapter
{
public:
	~SceneAdapter(void);

	void Clear();

	bool Import(System::String^ filename);

	bool Export(System::String^ filename);

	int AddParticleSystemScene(System::Collections::Generic::List<PG::Core::Math::Vector3d^>^ positions);

	int AddWireFrameScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ lines);

	int AddPolygonMeshScene(System::Collections::Generic::List<PG::Core::Math::Line3d^>^ positions);

internal:
	SceneAdapter(Crystal::Scene::Scene* instance, Crystal::Scene::SceneFactory*factory);

internal:
	Crystal::Scene::Scene* instance;
	Crystal::Scene::SceneFactory* factory;
};

	}
}
