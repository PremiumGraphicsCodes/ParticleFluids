#include "pch.h"
#include "../Command/MockCommand.h"
#include "../Command/JSONConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

TEST(JSONConverterTest, TestToJSONAny)
{
	std::any a = Vector3dd(0, 1, 2);
	auto j = JSONConverter::toJSON(a);
	EXPECT_EQ(j["x"], 0);
	EXPECT_EQ(j["y"], 1);
	EXPECT_EQ(j["z"], 2);
}

/*
TEST(JSONFileConverterTest, TestToJSONArgs)
{
	Arg<int> arg("Int", 123);
	JSONConverter::toJSON(arg);
}
*/

TEST(JSONConverterTest, TestToJsonCommand)
{
	MockCommand command;
	const auto j = JSONConverter::toJSON(command);

	for (auto& el : j.items()) {
		std::cout << el.key() << " : " << el.value() << "\n";
	}
}

TEST(JSONConverterTest, TestFromJSONAny)
{
	{
		nlohmann::json j;
		j["x"] = 0;
		j["y"] = 1;
		j["z"] = 2;
		std::any a(Vector3dd(0, 0, 0));
		JSONConverter::fromJSON(j, a);
		Vector3dd v1(0, 1, 2);
		auto v2 = std::any_cast<Vector3dd>(a);
		EXPECT_EQ(v1, v2);
	}
	{
		nlohmann::json j;
		j["r"] = 0.0f;
		j["g"] = 0.1f;
		j["b"] = 0.2f;
		j["a"] = 0.3f;
		std::any a(ColorRGBAf(0, 0, 0, 0));
		JSONConverter::fromJSON(j, a);
		ColorRGBAf v1(0.0f, 0.1f, 0.2f, 0.3f);
		auto v2 = std::any_cast<ColorRGBAf>(a);
		EXPECT_EQ(v1, v2);
	}
}

/*
TEST(JSONConverterTest, TestFromJSONCommand)
{
	MockCommand command;

	//JSONConverter::fromJSON()
}
*/