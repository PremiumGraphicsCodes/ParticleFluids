#pragma once

namespace Crystal {
	namespace Command {
		class ICommand;
	}
}

namespace PG {
	namespace CLI {
		ref class WorldAdapter;
		ref class EachCommand;
		interface class ICommandFactory;

public ref class Command
{
public:
	Command();

	Command(System::String^ name);

	void Create(System::String^ name);

	generic <class T>
	void SetArg(System::String^ name, T value);

	bool Execute(WorldAdapter^ objects);
	
	generic <class T>
	T GetResult(System::String^ name);

	void Clear();

	generic <class T>
	static T Get(WorldAdapter^ objects, System::String^ name);

	generic <class T>
	static T Get(WorldAdapter^ objects, System::String^ name, int parentId);

	void SetFactory(ICommandFactory^ factory) { this->factory = factory; }

private:
	ICommandFactory^ factory;

internal:
	Command(std::unique_ptr<Crystal::Command::ICommand> command);
};


	}
}