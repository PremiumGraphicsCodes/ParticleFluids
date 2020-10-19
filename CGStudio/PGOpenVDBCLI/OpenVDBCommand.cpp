#include "stdafx.h"
#include "OpenVDBCommand.h"

#include "../../CrystalViewer/Command/Command.h"

//#include "../../Crystal/Scene/World.h"
#include "../PGCLI/Converter.h"
#include "../PGCLI/AnyConverter.h"
//#include "../PGCLI/WorldAdapter.h"

using namespace PG::CLI;

namespace {
	Crystal::Command::Command instance;
}

OpenVDBCommand::OpenVDBCommand()
{}

OpenVDBCommand::OpenVDBCommand(System::String^ name)
{
	command->Create(name);
	//const auto& str = Converter::toCpp(name);
	//::instance.create(str);
}

void OpenVDBCommand::Create(System::String^ name)
{
	command->Create(name);
	//const auto& str = Converter::toCpp(name);
	//::instance.create(str);
}

generic <class T>
void OpenVDBCommand::SetArg(System::String^ name, T value)
{
	command->SetArg(name, value);
	//const auto& str = PG::CLI::Converter::toCpp(name);
	//const auto v = AnyConverter::toCpp(value, T::typeid);
	//::instance.setArg(str, v);
}

bool OpenVDBCommand::Execute(WorldAdapter^ objects)
{
	return command->Execute(objects);
	//return ::instance.execute(objects->instance);
}

generic <class T>
T OpenVDBCommand::GetResult(System::String^ name)
{
	return command->GetResult<T>(name);
	//const auto& str = msclr::interop::marshal_as<std::string>(name);
	//auto result = ::instance.getResult(str);
	//return (T)(AnyConverter::fromCpp(result));
}

void OpenVDBCommand::Clear()
{
	command->Clear();
	//::instance.clear();
}