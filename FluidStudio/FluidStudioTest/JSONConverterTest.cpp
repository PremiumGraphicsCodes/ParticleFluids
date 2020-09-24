#include "pch.h"

#include "../FluidStudio/JSONConverter.h"
#include "../ThirdParty/nlohmann/include/json.hpp"

using json = nlohmann::json;

using namespace Crystal::Math;
using namespace Crystal::FS;

TEST(JSONConverterTest, TestToJSON)
{
	{
		const json actual = JSONConverter::toJSON(1);
		const json expected( 1 );
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON(9.9f);
		const json expected( 9.9f );
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON(99.9);
		const json expected( 99.9 );
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON(std::string("Hello"));
		const json expected( "Hello" );
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON(Vector3df(1,2,3));
		const json expected( {1,2,3} );
		EXPECT_EQ(expected, actual);
	}

	{
		const json actual = JSONConverter::toJSON(Vector3dd(1,2,3));
		const json expected( {1,2,3} );
		EXPECT_EQ(expected, actual);
	}


	{
		const Box3d box(Vector3dd(1, 2, 3), Vector3dd(11, 12, 13));
		const json actual = JSONConverter::toJSON(box);
		const json expected =
		{
			{ "min", {1,2,3} },
			{ "max", {11,12,13} }
		};
		EXPECT_EQ(expected, actual);
	}
}

TEST(JSONConverterTest, TestFromJSON)
{
	{
		const json j(1);
		const auto v = JSONConverter::fromJSON<int>(j);
		EXPECT_EQ(1, v);
	}

	{
		const json j(9.9f);
		const auto v = JSONConverter::fromJSON<float>(j);
		EXPECT_EQ(9.9f, v);
	}

	{
		const json j("Hello");
		const auto v = JSONConverter::fromJSON<std::string>(j);
		EXPECT_EQ("Hello", v);
	}

	{
		const json j = {1,2,3};
		const auto v = JSONConverter::fromJSON<Vector3df>(j);
		EXPECT_EQ(Vector3df(1, 2, 3), v);
	}


	{
		const json j = {1,2,3};
		const auto v = JSONConverter::fromJSON<Vector3df>(j);
		EXPECT_EQ(Vector3df(1, 2, 3), v);
	}

	{
		const json j =
		{
			{ "min", {1,2,3} },
			{ "max", {11,12,13} }
		};
		const auto v = JSONConverter::fromJSON<Box3d>(j);
		const Box3d expected(Vector3dd(1, 2, 3), Vector3dd(11, 12, 13));
		EXPECT_TRUE(expected.isSame(v, 1.0e-12));
	}
}