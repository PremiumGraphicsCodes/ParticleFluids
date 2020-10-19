#include "stdafx.h"
//#include "OpenVDBCommand.h"
//
//#include "../../FluidStudio/OpenVDBCommand/OpenVDBCommandFactory.h"
//
//#include "../../Crystal/Scene/World.h"
//#include "Converter.h"
//#include "AnyConverter.h"
//#include "WorldAdapter.h"
//
//using namespace PG::CLI;
//
//namespace {
//	std::unique_ptr<Crystal::Command::ICommand> instance;
//}
//
//OpenVDBCommand::OpenVDBCommand()
//{}
//
//OpenVDBCommand::OpenVDBCommand(System::String^ name)
//{
//	const auto& str = Converter::toCpp(name);
//	::instance = Crystal::OpenVDB::OpenVDBCommandFactory::create(str);
//}
//
//void OpenVDBCommand::Create(System::String^ name)
//{
//	const auto& str = Converter::toCpp(name);
//	::instance = Crystal::OpenVDB::OpenVDBCommandFactory::create(str);
//}
//
//generic <class T>
//	void OpenVDBCommand::SetArg(System::String^ name, T value)
//	{
//		const auto& str = PG::CLI::Converter::toCpp(name);
//		const auto v = AnyConverter::toCpp(value, T::typeid);
//		::instance->setArg(str, v);
//	}
//
//	bool OpenVDBCommand::Execute(WorldAdapter^ objects)
//	{
//		return ::instance->execute(objects->instance);
//	}
//
//	generic <class T>
//		T OpenVDBCommand::GetResult(System::String^ name)
//		{
//			const auto& str = msclr::interop::marshal_as<std::string>(name);
//			auto result = ::instance->getResult(str);
//			return (T)(AnyConverter::fromCpp(result));
//		}
//
//		void OpenVDBCommand::Clear()
//		{
//			::instance.reset();
//			//::instance.clear();
//		}