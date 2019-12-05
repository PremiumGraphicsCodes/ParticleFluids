#include "gtest/gtest.h"

#include "../Graphics/ColorHSV.h"

using namespace Crystal::Graphics;

TEST(ColorHSVTest, TestToColorRGBA)
{
	const ColorHSV hsv(0.0, 0.0, 0.0);
	const auto rgba = hsv.toColorRGBA();
	EXPECT_TRUE(ColorRGBAf(0.0, 0.0, 0.0, 1.0) == rgba);
}