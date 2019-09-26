#pragma once

namespace PG {
	namespace CLI {

public ref class Command
{
public:
	void Create(System::String^ name);

	void SetArg(System::String^ name, System::Object^ value);

	void Execute();

	//System::Object^ GetResult(System::String^ name);

	void Clear();
};

	}
}