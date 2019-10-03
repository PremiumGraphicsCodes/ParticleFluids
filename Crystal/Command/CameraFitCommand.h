#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraFitCommand : public ICommand
{
public:
	void execute(Scene::World* world) override;
};

class CameraXYCommand : public ICommand
{
public:
	void execute(Scene::World* world) override;
};

class CameraYZCommand : public ICommand
{
public:
	void execute(Scene::World* world) override;
};

class CameraZXCommand : public ICommand
{
public:
	void execute(Scene::World* world) override;
};


	}
}