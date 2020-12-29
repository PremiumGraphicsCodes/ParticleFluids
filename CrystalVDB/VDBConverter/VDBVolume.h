#pragma once

#include <memory>

#include "../../Crystal/Scene/IShapeScene.h"

#include "../../Crystal/Util/UnCopyable.h"
#include "../../Crystal/Math/Box3d.h"

namespace Crystal {
	namespace Shape {
		class IParticleSystem;
	}
	namespace VDB {
		class VolumeImpl;

class VDBVolume : public Scene::IShapeScene
{
public:
	VDBVolume();

	explicit VDBVolume(VolumeImpl* impl);

	explicit VDBVolume(const float value);

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	void setValue(const std::array<int,3>& index, const float value);

	float getValue(const std::array<int, 3> index);

	~VDBVolume();

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	VolumeImpl* getImpl() const { return impl; }

	int getActiveVoxelCount() const;

	void translate(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

	Scene::IPresenter* getPresenter() {
		return nullptr;
	}//presenter.get(); };

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	//Math::Box3d getBoundingBox() const override;


private:
	VolumeImpl* impl;
};
	}
}