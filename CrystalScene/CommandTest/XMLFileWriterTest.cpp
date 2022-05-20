#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/XMLFileWriter.h"

using namespace Crystal::Command;

TEST(XMLFileWriterTest, TestWrite)
{
	LabeledValue<int> intValue("Int", 1);
	LabeledValue<double> doubleValue("Double", 3.14);
	LabeledValueTree tree1("Tree");
	tree1.add(&intValue);
	tree1.add(&doubleValue);

	LabeledValue<float> floatValue("Float", 3.14f);
	LabeledValue<std::string> textValue("Text", "Hello");
	LabeledValueTree tree2("Tree2");
	tree2.add(&floatValue);
	tree2.add(&textValue);
	tree1.add(&tree2);

	XMLFileWriter writer;
	const auto isOk = writer.write(tree1, "./TestFiles/test.xml");
	EXPECT_TRUE(isOk);
}