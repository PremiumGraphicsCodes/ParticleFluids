#include "PolygonMeshPanel.h"
#include "../Math/Vector3d.h"
#include "../UI/Repository.h"
#include "../UI/Canvas.h"
#include "../Shape/PolygonMeshBuilder.h"
#include "../Graphics/ColorRGBA.h"
#include "imgui.h"
#include "IPopupButton.h"

#include "PMSphereButton.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;
using namespace Crystal::UI;

namespace {

	class PMBoxButton : public IPopupButton
	{
	public:
		PMBoxButton(Repository* model, Canvas* canvas) :
			IPopupButton("PMBox", model, canvas)
		{
		}

		void onShow() override
		{
			ImGui::InputFloat3("Point1", &point1[0]);
			ImGui::InputFloat3("Point2", &point2[0]);
		}

		void onOk() override
		{
			PolygonMeshBuilder builder;
			const Box3d box(point1, point2);
			builder.build(box);
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			material.setSpecular(glm::vec3(0, 1, 0));
			material.setDiffuse(glm::vec3(0, 0, 1));
			getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), material, "Box");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel() override
		{

		}

	private:
		glm::vec3 point1 = { 0,0,0 };
		glm::vec3 point2 = { 1,1,1 };
	};

	class PMPlaneButton : public IPopupButton
	{
	public:
		PMPlaneButton(Repository* model, Canvas* canvas) :
			IPopupButton("PMPlane",model, canvas)
		{
		}

		void onShow() override
		{
		}

		void onOk()
		{
			PolygonMeshBuilder builder;
			builder.build(origin, uvec, vvec);
			Crystal::Graphics::Material material;
			material.setAmbient(glm::vec3(1, 0, 0));
			getModel()->getObjects()->getPolygonMeshes()->addObject(builder.getPolygonMesh(), material, "Plane");
			getCanvas()->setViewModel(getModel()->toViewModel());
			getCanvas()->fitCamera(getModel()->getBoundingBox());
		}

		void onCancel()
		{

		}

	private:
		glm::vec3 origin = { 0, 0, 0 };
		glm::vec3 uvec = { 1, 0, 0 };
		glm::vec3 vvec = { 0, 1, 0 };
	};
}

PolygonMeshPanel::PolygonMeshPanel(const std::string& name, Repository* model, Canvas* canvas) :
	IPanel(name, model, canvas)
{
	add( new PMSphereButton(model, canvas) );
	add( new PMBoxButton(model, canvas) );
	add( new PMPlaneButton(model, canvas) );
}
