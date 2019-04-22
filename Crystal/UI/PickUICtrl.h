#include <memory>
#include "../Graphics/ICamera.h"
#include "Canvas.h"
#include "IUICtrl.h"

#include "../Model/ObjectType.h"

#include <functional>

namespace Crystal {
	namespace UI {
		class Repository;

class PickUICtrl : public IUICtrl
{
public:
	PickUICtrl(Repository* model, Canvas* canvas, const Model::ObjectType& type);

	virtual ~PickUICtrl() {}

	virtual void onLeftButtonDown(const Math::Vector2df& position) override;

	virtual void onLeftButtonUp(const Math::Vector2df& position) override;

	virtual void onLeftDragging(const Math::Vector2df& position) override;

	virtual void onRightButtonDown(const Math::Vector2df& position) override;

	virtual void onRightButtonUp(const Math::Vector2df& position) override;

	virtual void onRightDragging(const Math::Vector2df& position) override;

	virtual void onWheel(const float dx) override;

	void setFunction(const std::function<void(int, int)>& func) { this->function = func; }

private:
	Repository* model;
	Canvas* canvas;
	std::function<void(int, int)> function;
	const Model::ObjectType& type;
};
	}
}
