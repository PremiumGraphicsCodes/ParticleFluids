#include "pch.h"

#include "../FluidStudio/JSONConverter.h"
#include "../ThirdParty/nlohmann/include/json.hpp"

using json = nlohmann::json;

using namespace Crystal::FS;

TEST(JSONConverterTest, TestToJSON)
{
	{
		const json actual = JSONConverter::toJSON("Int", 1);
		const json expected{ "Int", 1 };
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON("Float", 1.0f);
		const json expected{ "Float", 1.0f };
		EXPECT_EQ(expected, actual);
	}


	{
		const json actual = JSONConverter::toJSON("String", "Hello");
		const json expected{ "String", "Hello" };
		EXPECT_EQ(expected, actual);
	}
}