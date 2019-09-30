#pragma once

#include "ICommand.h"

namespace Crystal {
	namespace Command {

class CameraFitCommand : public ICommand
{
public:
	struct Args : IArgs {};

	struct Results : IResults {};

	CameraFitCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;
};

class CameraXYCommand : public ICommand
{
public:
	struct Args : IArgs {};

	struct Results : IResults {};

	CameraXYCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;

};

class CameraYZCommand : public ICommand
{
public:
	struct Args : IArgs {};

	struct Results : IResults {};

	CameraYZCommand() :
		ICommand(&args, &results)
	{}

	void execute(Scene::World* world) override;

private:
	Args args;
	Results results;

};


	}
}