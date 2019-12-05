#include "gtest/gtest.h"

#include "../Graphics/ColorHSV.h"

using namespace Crystal::Graphics;

TEST(ColorHSVTest, TestToColorRGBA)
{
	{
		const ColorHSV hsv(0.0, 0.0, 0.0);
		const auto rgb = hsv.toColorRGBf();
		EXPECT_TRUE(ColorRGBf(0.0, 0.0, 0.0) == rgb);
	}

	{
		const ColorHSV hsv(360.0, 1.0, 1.0);
		const auto rgb = hsv.toColorRGBf();
		EXPECT_TRUE(ColorRGBf(1.0, 0.0, 0.0) == rgb);
	}
}