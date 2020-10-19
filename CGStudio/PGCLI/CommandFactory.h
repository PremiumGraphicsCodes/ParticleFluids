#pragma once

namespace PG {
	namespace CLI {
		ref class Command;

public interface class ICommandFactory
{
	Command^ Create(System::String^ name);
};

public ref class CommandFactory : ICommandFactory
{
public:
	virtual Command^ Create(System::String^ name);
};

	}
}