#include <memory>
namespace Crystal {
	namespace Command {
		class ICommand;
	}
}

namespace PG {
	namespace CLI {

public ref class EachCommand
{
public:
	EachCommand(std::unique_ptr<Crystal::Command::ICommand> instance);
	//void Execute();

internal:
	std::unique_ptr<Crystal::Command::ICommand> getInstance();
};

	}
}
