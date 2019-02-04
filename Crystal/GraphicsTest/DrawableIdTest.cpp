#include <gtest/gtest.h>

#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestFromColor)
{
	EXPECT_EQ(DrawableID(0, 0), DrawableID(ColorRGBAf(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(30, 0), DrawableID(ColorRGBAf(30.0f / 255.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(255, 0), DrawableID(ColorRGBAf(1.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256, 0), DrawableID(ColorRGBAf(0, 1.0f / 255.0f, 0, 0)));
	EXPECT_EQ(DrawableID(256 * 256, 0), DrawableID(ColorRGBAf(0, 0, 1.0f / 255.0f, 0)));
	EXPECT_EQ(DrawableID(256 * 256, 1), DrawableID(ColorRGBAf(0, 0, 1.0f / 255.0f, 1.0f / 255.0f)));
}

TEST(DrawableIDTest, TestFromColorUC)
{
	EXPECT_EQ(DrawableID(0, 0), DrawableID(ColorRGBAuc(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 1), DrawableID(ColorRGBAuc(0, 0, 0, 1)));
	EXPECT_EQ(DrawableID(1, 2), DrawableID(ColorRGBAuc(1, 0, 0, 2)));
	EXPECT_EQ(DrawableID(30, 0), DrawableID(ColorRGBAuc(30, 0, 0, 0)));
	EXPECT_EQ(DrawableID(255, 0), DrawableID(ColorRGBAuc(255, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256, 0), DrawableID(ColorRGBAuc(0, 1, 0, 0)));
	EXPECT_EQ(DrawableID(256 * 256, 0), DrawableID(ColorRGBAuc(0, 0, 1, 0)));
	EXPECT_EQ(DrawableID(1, 1), DrawableID(ColorRGBAuc(1, 0, 0, 1)));
}

TEST(DrawableIDTest, TestToColor)
{
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), DrawableID(0, 0).toColor());
	EXPECT_EQ(ColorRGBAf(30.0f / 255.0f, 0.0f, 0.0f, 0.0f), DrawableID(30, 0).toColor());
	EXPECT_EQ(ColorRGBAf(1.0f, 0.0f, 0.0f, 0.0f), DrawableID(255, 0).toColor());

	EXPECT_EQ(ColorRGBAf(0.0f, 1.0f / 255.0f, 0.0f, 0.0f), DrawableID(256, 0).toColor());
	EXPECT_EQ(ColorRGBAf(1.0f / 255.0f, 1.0f / 255.0f, 0.0f, 0.0f), DrawableID(257, 0).toColor());
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 1.0f / 255.0f, 0.0f), DrawableID(256 * 256, 0).toColor());
	//EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f / 256.0f), DrawableID(256 * 256 * 256).toColor());
}

TEST(DrawableIDTest, TestGetType)
{
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 0)).getType());
	EXPECT_EQ(1, DrawableID(ColorRGBAuc(0, 0, 0, 1)).getType());
	EXPECT_EQ(2, DrawableID(ColorRGBAuc(1, 0, 0, 2)).getType());
}

TEST(DrawableIDTest, TestGetValue)
{
	EXPECT_EQ(0, DrawableID(0, 10).getValue());
	EXPECT_EQ(100, DrawableID(100, 10).getValue());
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 0)).getValue());
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 1)).getValue());
	EXPECT_EQ(1, DrawableID(ColorRGBAuc(1, 0, 0, 2)).getValue());
}