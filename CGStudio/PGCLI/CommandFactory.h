#pragma once

namespace Crystal {
	namespace Command {
		class ICommand;
	}
}

namespace PG {
	namespace CLI {
		ref class EachCommand;

public interface class ICommandFactory
{
	std::unique_ptr<Crystal::Command::ICommand> Create(System::String^ name);
};

public ref class CommandFactory : ICommandFactory
{
public:
	virtual std::unique_ptr<Crystal::Command::ICommand> Create(System::String^ name);
};

	}
}