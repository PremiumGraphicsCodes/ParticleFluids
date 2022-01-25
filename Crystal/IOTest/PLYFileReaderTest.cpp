#include "gtest/gtest.h"

#include "../IO/PLYFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PLYFileReaderTest, TestReadASCII)
{
	PLYFileReader reader;
	const auto isOk = reader.read("PLYWriteTestASCII.ply");
	EXPECT_TRUE(isOk);
}