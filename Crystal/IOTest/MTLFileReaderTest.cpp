#include "gtest/gtest.h"

#include "../Shape/PolygonMesh.h"
#include "../IO/MTLFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST(MTLFileReaderTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "newmtl FrontColor" << std::endl
		<< "Ka 0.0 0.0 0.0" << std::endl
		<< "Kd 1.0 1.0 1.0" << std::endl
		<< "Ks 0.1 0.1 0.1" << std::endl
		<< "illum 0" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	MTLFile expected;
	expected.name = "FrontColor";
	expected.ambient = ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f);
	expected.diffuse = ColorRGBAf(1.0f, 1.0f, 1.0f, 0.0f);
	expected.specular = ColorRGBAf(0.1f, 0.1f, 0.1f, 0.0f);

	const std::vector<MTLFile> expecteds = { expected };
	EXPECT_EQ(expecteds, file.materials);
}

TEST(MTLFileReaderTest, TestReadTexture)
{
	std::stringstream stream;
	stream
		<< "newmtl name" << std::endl
		<< "map_Ka ambient.png" << std::endl
		<< "map_Kd diffuse.png" << std::endl
		<< "map_Ks shininess.png" << std::endl
		<< "bump bump.png" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	MTLFile expected;
	expected.name = "name";
	expected.setAmbientTextureName("ambient.png");
	expected.setDiffuseTextureName("diffuse.png");
	expected.setShininessTextureName("shininess.png");
	expected.setBumpTextureName("bump.png");

	const std::vector<MTLFile> expecteds = { expected };
	EXPECT_EQ(expecteds, file.materials);
}


// from http://paulbourke.net/dataformats/mtl/
TEST(MTLFileReaderTest, TestExample1)
{
	std::stringstream stream;
	stream
		<< "newmtl neon_green" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 0" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	EXPECT_EQ("neon_green", file.materials.front().name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), file.materials.front().diffuse);
	EXPECT_EQ(0, file.materials.front().getIllumination());
}

TEST(MTLFileReaderTest, TestExample2)
{
	std::stringstream stream;
	stream
		<< "newmtl flat_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 1" << std::endl;
	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	EXPECT_EQ(1, file.materials.size());
	EXPECT_EQ("flat_green", file.materials.front().name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), file.materials.front().ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), file.materials.front().diffuse);
	EXPECT_EQ(1, file.materials.front().getIllumination());

}

TEST(MTLFileReaderTest, TestExample3)
{
	std::stringstream stream;
	stream
		<< "newmtl diss_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "d 0.8000" << std::endl
		<< "illum 1" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());

	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("diss_green", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_FLOAT_EQ(0.8f, mtl.getTransparent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample4)
{
	std::stringstream stream;
	stream
		<< "newmtl shiny_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 1" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());

	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("shiny_green", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(1.0, 1.0, 1.0, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample5)
{
	std::stringstream stream;
	stream
		<< "newmtl green_mirror" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 0.0000 1.0000 0.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 3" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));

	EXPECT_EQ(1, file.materials.size());
	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("green_mirror", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.0, 1.0, 0.0, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(3, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample6)
{
	std::stringstream stream;
	stream
		<< "newmtl fake_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.9000 0.9000 0.9000" << std::endl
		<< "d 0.1000" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 4" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("fake_windsh", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0, 0.0, 0.0, 0.0), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0, 0.0, 0.0, 0.0), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.9f, 0.9f, 0.9f, 0.0), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(4, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample7)
{
	std::stringstream stream;
	stream
		<< "newmtl fresnel_blue" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.6180 0.8760 0.1430" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 5" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("fresnel_blue", mtl.name);
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), mtl.ambient);
	EXPECT_EQ(ColorRGBAf(0.0f, 0.0f, 0.0f, 0.0f), mtl.diffuse);
	EXPECT_EQ(ColorRGBAf(0.6180f, 0.8760f, 0.1430f, 0.0f), mtl.specular);
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(5, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample8)
{
	std::stringstream stream;
	stream
		<< "newmtl real_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("real_windsh", mtl.name);
	EXPECT_FLOAT_EQ(1.2f, mtl.getOpticalDensity());
}

TEST(MTLFileReaderTest, TestReadMaterials)
{
	std::stringstream stream;
	stream
		<< "newmtl mat1" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl
		<< "newmtl mat2" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFileReader file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(2, file.materials.size());
	const MTLFile& mtl = file.materials.front();
	EXPECT_EQ("mat1", mtl.name);
	EXPECT_FLOAT_EQ(1.2f, mtl.getOpticalDensity());
	const MTLFile& mtl2 = file.materials.back();
	EXPECT_EQ("mat2", mtl2.name);

}