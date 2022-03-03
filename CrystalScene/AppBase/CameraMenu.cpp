#include "CameraMenu.h"
#include "Canvas.h"
#include "IMenuItem.h"

#include "../Scene/World.h"
#include "../Command/Command.h"
#include "../Command/CommandFactory.h"
#include "../Command/CameraFitCommand.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;
using namespace Crystal::Command;

namespace {
	class FitMenuItem : public IMenuItem
	{
	public:
		FitMenuItem(const std::string& name, World* model) :
			IMenuItem(name),
			model(model)
		{}

		void onPushed() override {
			CameraFitCommand command;
			command.execute(model);
		}

	private:
		World* model;
	};

	class XYMenuItem : public IMenuItem
	{
	public:
		XYMenuItem(const std::string& name, World* model) :
			IMenuItem(name),
			model(model)
		{}

		void onPushed() override {
			CameraXYCommand command;
			command.execute(model);
		}

	private:
		World* model;
	};

	class YZMenuItem : public IMenuItem
	{
	public:
		YZMenuItem(const std::string& name, World* model) :
			IMenuItem(name),
			model(model)
		{}

		void onPushed() override {
			CameraYZCommand command;
			command.execute(model);
		}

	private:
		World* model;
	};

	class ZXMenuItem : public IMenuItem
	{
	public:
		ZXMenuItem(const std::string& name, World* model) :
			IMenuItem(name),
			model(model)
		{}

		void onPushed() override {
			CameraZXCommand command;
			command.execute(model);
		}

	private:
		World* model;
	};

}

CameraMenu::CameraMenu(const std::string& name, World* model, Canvas* canvas) :
	IMenu(name, model, canvas)
{
	add(new FitMenuItem("Fit", model));
	add(new XYMenuItem("XY", model));
	add(new YZMenuItem("YZ", model));
	add(new ZXMenuItem("XZ", model));
}