#pragma once

namespace PG {
	namespace CLI {
		ref class WorldAdapter;

public ref class Command
{
public:
	Command();

	Command(System::String^ name);

	void Create(System::String^ name);

	void SetArg(System::String^ name, System::Object^ value);

	void Execute(WorldAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

	static System::Object^ Get(WorldAdapter^ objects, System::String^ name);

	static System::Object^ Get(WorldAdapter^ objects, System::String^ name, int parentId);

	static System::Object^ Get(WorldAdapter^ objects, System::String^ name, int parentId, int childId);

	static void Set(WorldAdapter^ objects, System::String^ name, System::Object^ value);
};


	}
}