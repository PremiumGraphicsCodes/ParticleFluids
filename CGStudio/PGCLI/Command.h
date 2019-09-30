#pragma once

namespace PG {
	namespace CLI {
		ref class RepositoryAdapter;

public ref class Command
{
public:
	Command::Command(System::String^ name);

	void SetArg(System::String^ name, System::Object^ value);

	void Execute(RepositoryAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

	static System::Object^ Get(RepositoryAdapter^ objects, System::String^ name);
};


	}
}