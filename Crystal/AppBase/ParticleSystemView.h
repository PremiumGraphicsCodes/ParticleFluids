#pragma once

#include "IWindow.h"
#include "imgui.h"

#include "IntView.h"

namespace Crystal {
	namespace Shape {
		class IParticleSystem;
	}
	namespace UI {

class ParticleSystemView : public IWindow
{
public:
	explicit ParticleSystemView(const std::string& name);

	void onShow() override;

	void setValue(Shape::IParticleSystem* value);

private:
	IntView particleCount;
};

	}
}