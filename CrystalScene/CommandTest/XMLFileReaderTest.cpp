#include "pch.h"
#include "gtest/gtest.h"

#include "../Command/XMLFileReader.h"

using namespace Crystal::Command;

namespace {

	class LBFactory : public ILabeledValueFactory
	{
		std::unique_ptr<PropertyTree> create(const std::string& name) const override
		{
			if (name == "Tree")
			{
				auto tree = std::make_unique<PropertyTree>("Tree");
				tree->add( new Property<int>("Int", 1));
				tree->add( new Property<double>("Double", 3.14));
				return std::move(tree);
			}
			else if (name == "Tree2")
			{
				auto tree2 = std::make_unique<PropertyTree>("Tree2");
				tree2->add( new Property<float>("Float", 3.14f));
				tree2->add(new Property<std::string>("Text", "Hello"));
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