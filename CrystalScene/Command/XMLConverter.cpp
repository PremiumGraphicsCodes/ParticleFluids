#include "XMLConverter.h"
#include <cassert>

using namespace Crystal::Command;

tinyxml2::XMLText* XMLConverter::toXML(tinyxml2::XMLDocument* doc, const std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(bool)) {
        const auto v = std::any_cast<bool>(value);
        return doc->NewText(std::to_string(v).c_str());
    }
    if (type == typeid(int)) {
        const auto v = std::any_cast<int>(value);
        return doc->NewText(std::to_string(v).c_str());
    }
    if (type == typeid(float)) {
        const auto v = std::any_cast<int>(value);
        return doc->NewText(std::to_string(v).c_str());
    }
    if (type == typeid(double)) {
        const auto v = std::any_cast<double>(value);
        return doc->NewText(std::to_string(v).c_str());
    }
    if (type == typeid(std::string)) {
        const auto v = std::any_cast<std::string>(value);
        return doc->NewText(v.c_str());
    }
    /*
    if (type == typeid(std::vector<int>)) {
        return std::any_cast<std::vector<int>>(value);
    }
    if (type == typeid(Math::Vector2df)) {
        return std::any_cast<Math::Vector2df>(value);
    }
    if (type == typeid(std::vector<Math::Vector2df>)) {
        return std::any_cast<std::vector<Math::Vector2df>>(value);
    }
    if (type == typeid(Math::Vector2dd)) {
        return std::any_cast<Math::Vector2dd>(value);
    }
    if (type == typeid(std::vector<Math::Vector2dd>)) {
        return std::any_cast<std::vector<Math::Vector2dd>>(value);
    }
    if (type == typeid(Math::Vector3df)) {
        return std::any_cast<Math::Vector3df>(value);
    }
    if (type == typeid(Math::Vector3dd)) {
        return std::any_cast<Math::Vector3dd>(value);
    }
    if (type == typeid(std::vector<Math::Vector3dd>)) {
        return std::any_cast<std::vector<Math::Vector3dd>>(value);
    }
    if (type == typeid(Graphics::ColorRGBAf)) {
        return std::any_cast<Graphics::ColorRGBAf>(value);
    }
    */
    assert(false);
    return {};
}

tinyxml2::XMLElement* XMLConverter::toXML(tinyxml2::XMLDocument* doc, const IArgs& args)
{
    auto e = doc->NewElement("");
    for (auto a : args.args) {
        doc->NewElement(a->name.c_str());
        auto x = toXML(doc, a->value);
    }
    return e;
}
