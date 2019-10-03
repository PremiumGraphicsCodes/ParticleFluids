#pragma once

namespace PG {
	namespace CLI {
		ref class WorldAdapter;

public ref class Command
{
public:
	Command::Command(System::String^ name);

	void Create(System::String^ name);

	void SetArg(System::String^ name, System::Object^ value);

	void SetArg(System::String^ name, int value);

	void SetArg(System::String^ name, double x, double y);


	//void SetArg(System::String^ name, double x, double y, double z);

	void Execute(WorldAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

	static System::Object^ Get(WorldAdapter^ objects, System::String^ name);

	static System::Object^ Get(WorldAdapter^ objects, int id, System::String^ name);

	static void Set(WorldAdapter^ objects, System::String^ name, System::Object^ value);
};


	}
}