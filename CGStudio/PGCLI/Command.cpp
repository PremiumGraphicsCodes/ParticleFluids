#include "stdafx.h"
#include "Command.h"

#include "../../CrystalViewer/Command/Command.h"
#include "../../CrystalViewer/Command/GetCommand.h"
#include "../../CrystalViewer/Command/SetCommand.h"

#include "../../Crystal/Scene/World.h"
#include "Converter.h"
#include "AnyConverter.h"
#include "WorldAdapter.h"

using namespace PG::CLI;

namespace {
	Crystal::Command::Command instance;
}

Command::Command()
{}

Command::Command(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance.create(str);
}

void Command::Create(System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	::instance.create(str);
}

void Command::SetArg(System::String^ name, System::Object^ value)
{
	const auto& str = Converter::toCpp(name);
	const auto v = AnyConverter::toCpp(value);
	::instance.setArg(str, v);
}

void Command::Execute(WorldAdapter^ objects)
{
	::instance.execute(objects->instance);
}

generic <class T>
T Command::GetResult(System::String^ name)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto result = ::instance.getResult(str);
	return (T)(AnyConverter::fromCpp(result));
}

void Command::Clear()
{
	::instance.clear();
}

System::Object^ Command::Get(WorldAdapter^ objects, System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	auto value = Crystal::Command::GetCommand::Get(objects->instance, str);
	auto result = AnyConverter::fromCpp( value );
	return result;
}

System::Object^ Command::Get(WorldAdapter^ objects, int id, System::String^ name)
{
	const auto& str = Converter::toCpp(name);
	auto value = Crystal::Command::GetCommand::Get(objects->instance, id, str);
	return AnyConverter::fromCpp(value);
}

void Command::Set(WorldAdapter^ objects, System::String^ name, System::Object^ value)
{
	const auto& str = msclr::interop::marshal_as<std::string>(name);
	auto v = AnyConverter::toCpp(value);
	Crystal::Command::SetCommand::Set(objects->instance, str, v);
}
