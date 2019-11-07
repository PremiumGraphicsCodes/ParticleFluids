#include "stdafx.h"
#include "AnyConverter.h"
#include "Converter.h"

using namespace PG::CLI;

std::any AnyConverter::toCpp(System::Object^ object)
{
	auto type = object->GetType();
	if (type == int::typeid) {
		const auto a = (int)(object);
		return std::any(a);
	}
	else if (type == float::typeid) {
		const auto a = (float)(object);
		return std::any(a);
	}
	else if (type == double::typeid) {
		const auto a = (double)(object);
		return std::any(a);
	}
	else if (type == bool::typeid) {
		const auto a = (bool)(object);
		return std::any(a);
	}
	else if (type == System::String::typeid) {
		const auto str = Converter::toCpp((System::String^)object);
		return std::any(str);
	}
	else if (type == Core::Math::Vector2d::typeid) {
		auto v = (Core::Math::Vector2d^)(object);
		auto vv = Converter::toCpp2d(v);
		return std::any(vv);
	}
	else if (type == Core::Math::Vector3d::typeid) {
		auto v = (Core::Math::Vector3d^)(object);
		auto vv = Converter::toCpp(v);
		return std::any(vv);
	}
	else if (type == Core::Math::Matrix4d::typeid) {
		auto v = (Core::Math::Matrix4d^)(object);
		auto vv = Converter::toCpp(v);
		return std::any(vv);
	}
	else if (type == Core::Graphics::ColorRGBA::typeid) {
		auto v = (Core::Graphics::ColorRGBA^)(object);
		auto vv = Converter::toCpp(v);
		return std::any(vv);
	}
	else {
		auto values = (System::Collections::Generic::IEnumerable<Object^>^)object;
		auto first = System::Linq::Enumerable::FirstOrDefault(values);
		if (first->GetType() == PG::Core::Math::Vector3d::typeid) {
			std::vector<Crystal::Math::Vector3dd> dest;
			for each (Core::Math::Vector3d ^ v in values) {
				dest.push_back(Converter::toCpp(v));
			}
			return std::any(dest);
		}
		else if (first->GetType() == Core::Math::Line3d::typeid) {
			std::vector<Crystal::Math::Line3dd> dest;
			for each (Core::Math::Line3d^ l in values) {
				dest.push_back( Converter::toCpp(l) );
			}
			return std::any(dest);
		}
	}

	return std::any(0);
}

System::Object^ AnyConverter::fromCpp(std::any any)
{
	auto& type = any.type();
	if (type == typeid(int)) {
		return std::any_cast<int>(any);
	}
	else if (type == typeid(bool)) {
		return std::any_cast<bool>(any);
	}
	else if (type == typeid(Crystal::Math::Vector3df)) {
		const auto& v = std::any_cast<Crystal::Math::Vector3df>(any);
		return Converter::fromCpp(v);
	}
	else if (type == typeid(Crystal::Math::Vector3dd)) {
		const auto& v = std::any_cast<Crystal::Math::Vector3dd>(any);
		return Converter::fromCpp(v);
	}
	else if (type == typeid(Crystal::Math::Matrix4df)) {
		const auto& v = std::any_cast<Crystal::Math::Matrix4df>(any);
		return Converter::fromCpp(v);
	}
	else if (type == typeid(std::string)) {
		const auto& v = std::any_cast<std::string>(any);
		return Converter::fromCpp(v);
	}
	else if (type == typeid(std::vector<int>)) {
		const auto& v = std::any_cast<std::vector<int>>(any);
		auto dest = gcnew System::Collections::Generic::List<int>();
		for (int i = 0; i < v.size(); ++i) {
			dest->Add(v[i]);
		}
		return dest;
	}
	else if (type == typeid(std::vector<std::string>)) {
		const auto& v = std::any_cast<std::vector<std::string>>(any);
		auto dest = gcnew System::Collections::Generic::List<System::String^>();
		for (int i = 0; i < v.size(); ++i) {
			dest->Add( Converter::fromCpp(v[i]) );
		}
		return dest;
	}
	else if (type == typeid(Crystal::Scene::SceneType)) {
		const auto& v = std::any_cast<Crystal::Scene::SceneType>(any);
		return Converter::fromCpp(v);
	}
	else {
		assert(false);
	}

	return nullptr;
}
