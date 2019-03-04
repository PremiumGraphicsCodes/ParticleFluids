#include "PolygonMeshPanel.h"
#include "../Math/Vector3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "../Graphics/ColorRGBA.h"
#include "imgui.h"
#include "IPopupButton.h"

#include "PMSphereButton.h"
#include "PMBoxButton.h"

#include "Vector3dView.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

namespace {

	class PMPlaneButton : public IPopupButton
	{
	public:
		PMPlaneButton(Repository* model, Canvas* canvas) :
			IPopupButton("PMPlane",model, canvas),
			originView("Origin", Vector3dd(0,0,0)),
			uvecView("UVec", Vector3dd(1,0,0)),
			vvecView("VVec", Vector3dd(0,1,0))
		{
		}

		void onShow() override
		{
			originView.show();
			uvecView.show();
			vvecView.show();
		}

		void onOk()
		{
			PolygonMeshBuilder builder;
			builder.build(originView.getValue(), uvecView.getValue(), vvecView.getValue());
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), material, "PMPlane");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel()
		{

		}

	private:
		Vector3dView originView;
		Vector3dView uvecView;
		Vector3dView vvecView;
	};
}

PolygonMeshPanel::PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new PMSphereButton(model, canvas) );
	add( new PMBoxButton(model, canvas) );
	add( new PMPlaneButton(model, canvas) );
}
