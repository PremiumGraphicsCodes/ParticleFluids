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

	generic <class T>
	void SetArg(System::String^ name, T value);

	void Execute(WorldAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

	generic <class T>
	static T Get(WorldAdapter^ objects, System::String^ name);

	generic <class T>
	static T Get(WorldAdapter^ objects, System::String^ name, int parentId);

	generic <class T>
	static void Set(WorldAdapter^ objects, System::String^ name, int parentId, T value);

	generic <class T>
	static void Set(WorldAdapter^ objects, System::String^ name, int parentId, int childId, T value);
};


	}
}