#include <gtest/gtest.h>

#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestFromColor)
{
	EXPECT_EQ(DrawableID(0, 0), DrawableID(ColorRGBAf(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 30), DrawableID(ColorRGBAf(30.0f / 255.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 255), DrawableID(ColorRGBAf(1.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 256), DrawableID(ColorRGBAf(0, 1.0f / 255.0f, 0, 0)));
	EXPECT_EQ(DrawableID(0, 256 * 256), DrawableID(ColorRGBAf(0, 0, 1.0f / 255.0f, 0)));
	EXPECT_EQ(DrawableID(1, 256 * 256), DrawableID(ColorRGBAf(0, 0, 1.0f / 255.0f, 1.0f / 255.0f)));
}

TEST(DrawableIDTest, TestFromColorUC)
{
	EXPECT_EQ(DrawableID(0, 0), DrawableID(ColorRGBAuc(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(1, 0), DrawableID(ColorRGBAuc(0, 0, 0, 1)));
	EXPECT_EQ(DrawableID(2, 1), DrawableID(ColorRGBAuc(1, 0, 0, 2)));
	EXPECT_EQ(DrawableID(0, 30), DrawableID(ColorRGBAuc(30, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 255), DrawableID(ColorRGBAuc(255, 0, 0, 0)));
	EXPECT_EQ(DrawableID(0, 256), DrawableID(ColorRGBAuc(0, 1, 0, 0)));
	EXPECT_EQ(DrawableID(0, 256 * 256), DrawableID(ColorRGBAuc(0, 0, 1, 0)));
	EXPECT_EQ(DrawableID(1, 1), DrawableID(ColorRGBAuc(1, 0, 0, 1)));
}

TEST(DrawableIDTest, TestToColor)
{
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), DrawableID(0, 0).toColor());
	EXPECT_EQ(ColorRGBAf(30.0f / 255.0f, 0.0f, 0.0f, 0.0f), DrawableID(0, 30).toColor());
	EXPECT_EQ(ColorRGBAf(1.0f, 0.0f, 0.0f, 0.0f), DrawableID(0, 255).toColor());

	EXPECT_EQ(ColorRGBAf(0.0f, 1.0f / 255.0f, 0.0f, 0.0f), DrawableID(0, 256).toColor());
	EXPECT_EQ(ColorRGBAf(1.0f / 255.0f, 1.0f / 255.0f, 0.0f, 0.0f), DrawableID(0, 257).toColor());
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 1.0f / 255.0f, 0.0f), DrawableID(0, 256 * 256).toColor());
	//EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f / 256.0f), DrawableID(256 * 256 * 256).toColor());
}

TEST(DrawableIDTest, TestGetParentId)
{
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 0)).getParentId());
	EXPECT_EQ(1, DrawableID(ColorRGBAuc(0, 0, 0, 1)).getParentId());
	EXPECT_EQ(2, DrawableID(ColorRGBAuc(1, 0, 0, 2)).getParentId());
}

TEST(DrawableIDTest, TestGetChildId)
{
	EXPECT_EQ(10, DrawableID(0, 10).getChildId());
	EXPECT_EQ(100, DrawableID(10, 100).getChildId());
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 0)).getChildId());
	EXPECT_EQ(0, DrawableID(ColorRGBAuc(0, 0, 0, 1)).getChildId());
	EXPECT_EQ(1, DrawableID(ColorRGBAuc(1, 0, 0, 2)).getChildId());
}