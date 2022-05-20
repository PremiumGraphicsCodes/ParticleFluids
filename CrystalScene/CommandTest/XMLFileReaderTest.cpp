#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/XMLFileReader.h"

using namespace Crystal::Command;

namespace {

	class LBFactory : public ILabeledValueFactory
	{
		std::unique_ptr<LabeledValueTree> create(const std::string& name) const override
		{
			if (name == "Tree")
			{
				auto tree = std::make_unique<LabeledValueTree>("Tree");
				tree->add( new LabeledValue<int>("Int", 1));
				tree->add( new LabeledValue<double>("Double", 3.14));
				return std::move(tree);
			}
			else if (name == "Tree2")
			{
				auto tree2 = std::make_unique<LabeledValueTree>("Tree2");
				tree2->add( new LabeledValue<float>("Float", 3.14f));
				tree2->add(new LabeledValue<std::string>("Text", "Hello"));
				return std::move(tree2);
			}
		}
	};
}

TEST(XMLFileReaderTest, TestRead)
{
	LBFactory factory;

	XMLFileReader reader;
	const auto isOk = reader.read("./TestFiles/test.xml", factory);
	EXPECT_TRUE(isOk);
}