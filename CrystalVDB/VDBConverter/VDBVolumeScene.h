#pragma once

#include <memory>

#include "../../Crystal/Scene/IShapeScene.h"

#include "../../Crystal/Math/Box3d.h"

#include "VDBVolumePresenter.h"

namespace Crystal {
	namespace VDB {
		class VolumeImpl;

class VDBVolumeScene : public Scene::IShapeScene
{
public:
	VDBVolumeScene();

	explicit VDBVolumeScene(VolumeImpl* impl);

	explicit VDBVolumeScene(const float value);

	VDBVolumeScene(const int id, const std::string& name);

	void setImpl(VolumeImpl* impl) { this->impl = impl; }

	//explicit Volume(std::unique_ptr<VolumeImpl> impl);

	void setValue(const std::array<int,3>& index, const float value);

	float getValue(const std::array<int, 3> index);

	~VDBVolumeScene();

	void fill(const unsigned int coord1, const unsigned int coord2, const float value);

	int getActiveVoxelCount() const;

	void translate(const Math::Vector3dd& v) override {};

	void transform(const Math::Matrix3dd& m) override {};

	void transform(const Math::Matrix4dd& m) override {};

	Scene::IPresenter* getPresenter() { return presenter.get(); };

	Scene::SceneType getType() const { return Scene::SceneType::None; }

	Math::Box3d getBoundingBox() const override;

	VolumeImpl* getImpl() const { return impl; }

private:
	VolumeImpl* impl;
	std::unique_ptr<VDBVolumePresenter> presenter;
};
	}
}