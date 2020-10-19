#include "stdafx.h"
#include "Command.h"

#include "../../CrystalViewer/Command/Command.h"
#include "../../CrystalViewer/Command/GetCommand.h"
#include "../../CrystalViewer/Command/SetCommand.h"
#include "../../CrystalViewer/Command/CommandFactory.h"

#include "../../Crystal/Scene/World.h"
#include "Converter.h"
#include "AnyConverter.h"
#include "EachCommand.h"
#include "WorldAdapter.h"

using namespace PG::CLI;

namespace {
	std::unique_ptr<Crystal::Command::ICommand> instance;
	Crystal::Command::CommandFactory factory;
}

Command::Command()
{}

Command::Command(EachCommand^ command)
{
	instance = command->getInstance();
}

Command::Command(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = ::factory.createCommand(str);
}

void Command::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance = ::factory.createCommand(str);
}

generic <class T>
void Command::SetArg(System::String^ name, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value, T::typeid);
	::instance->setArg(str, v);
}

bool Command::Execute(WorldAdapter^ objects)
{
	return ::instance->execute(objects->instance);
}

generic <class T>
T Command::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::instance->getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void Command::Clear()
{
	::instance.reset();
	//::instance.clear();
}

generic <class T>
T Command::Get(WorldAdapter^ objects, System::String^ name)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	auto value = Crystal::Command::GetCommand::Get(objects->instance, str);
	auto result = (T)AnyConverter::fromCpp( value );
	return result;
}

generic <class T>
T Command::Get(WorldAdapter^ objects, System::String^ name, int id)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	auto value = Crystal::Command::GetCommand::Get(objects->instance, id, str);
	return (T)AnyConverter::fromCpp(value);
}

generic <class T>
void Command::Set(WorldAdapter^ objects, System::String^ name, int parentId, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	auto v = AnyConverter::toCpp(value, T::typeid);
	Crystal::Command::SetCommand::Set(objects->instance, parentId, str, v);
}

generic <class T>
void Command::Set(WorldAdapter^ objects, System::String^ name, int parentId, int childId, T value)
{
	const auto& str = PG::CLI::Converter::toCpp(name);
	auto v = AnyConverter::toCpp(value, T::typeid);
	Crystal::Command::SetCommand::Set(objects->instance, parentId, childId, str, v);
}
