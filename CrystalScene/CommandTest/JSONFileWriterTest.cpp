#include "pch.h"
#include "../Command/JSONConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

TEST(JSONFileWriterTest, TestWriteAny)
{
	std::any a = Vector3dd(0, 1, 2);
	auto j = JSONConverter::toJson(a);
	EXPECT_EQ(j["x"], 0);
	EXPECT_EQ(j["y"], 1);
	EXPECT_EQ(j["z"], 2);
}

TEST(JSONFileWriterTest, TestWriteArgs)
{
	Arg<int> arg("Int", 123);
	JSONConverter::toJson(arg);
}