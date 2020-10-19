#pragma once

namespace PG {
	namespace CLI {
		ref class EachCommand;

public interface class ICommandFactory
{
	EachCommand^ Create(System::String^ name);
};

public ref class CommandFactory : ICommandFactory
{
public:
	virtual EachCommand^ Create(System::String^ name);
};

	}
}