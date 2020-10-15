#pragma once

namespace PG {
	namespace CLI {
		ref class WorldAdapter;

public ref class PhysicsCommand
{
public:
	PhysicsCommand();

	PhysicsCommand(System::String^ name);

	void Create(System::String^ name);

	generic <class T>
	void SetArg(System::String^ name, T value);

	bool Execute(WorldAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

private:
	Command^ command;
};


	}
}