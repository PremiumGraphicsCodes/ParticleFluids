#include "gtest/gtest.h"

#include "../IO/PLYFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PLYFileReaderTest, TestReadASCII)
{
	PLYFileReader reader;
	const auto isOk = reader.readASCII("PLYWriteTestASCII.ply");
	EXPECT_TRUE(isOk);
}

TEST(PLYFileReaderTest, TestReadBinary)
{
	PLYFileReader reader;
	const auto isOk = reader.readBinary("PLYWriteTestBinary.ply");
	EXPECT_TRUE(isOk);
}