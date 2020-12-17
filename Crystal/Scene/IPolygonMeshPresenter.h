#pragma once

#include "IPresenter.h"

namespace Crystal {
	namespace Scene {
		class PolygonMeshScene;

class IPolygonMeshPresenter : public IPresenter
{
public:
	explicit IPolygonMeshPresenter(PolygonMeshScene* model) :
		model(model)
	{}

	virtual ~IPolygonMeshPresenter() {}

	//PolygonMeshScene* getModel()

protected:
	PolygonMeshScene* model;

};

	}
}