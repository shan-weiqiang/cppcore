#include "cpp/core/switch.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace cpp::core;

TEST(SwitchTypeTest, Constructor)
{
	SwitchType<int, int> a{7};
	SwitchType<int, int>{4}.Case(3, []() -> int { return 3; }).Default(6);
	SwitchType<int, void>{4}.Case(2, []() {}).Default([]() {});
}

TEST(SwitchTypeTest, CaseFn)
{
	auto ret = SwitchType<std::string, int>{"hello"}
				   .Case("hello", []() { return 10; })
				   .Case("nihao", []() { return 20; })
				   .get();
	ASSERT_EQ(ret, 10);
}

TEST(SwitchTypeTest, CaseGiven)
{
	auto ret = SwitchType<std::string, std::vector<std::string>>{"hello"}
				   .Case("hello", std::vector<std::string>{"dog", "cat"})
				   .Case("nihao", std::vector<std::string>{"animal"})
				   .get();
	auto benchmark = std::vector<std::string>{"dog", "cat"};
	ASSERT_EQ(ret, benchmark);
}

TEST(SwitchTypeTest, Default)
{
	auto ret = SwitchType<std::string, std::vector<std::string>>{"hello"}
				   .Case("niaho",
						 []() -> std::vector<std::string> {
							 return {"dog", "cat"};
						 })
				   .Default([]() -> std::vector<std::string> {
					   return {"shanghai", "beijing"};
				   });
	auto benchmark = std::vector<std::string>{"shanghai", "beijing"};
	ASSERT_EQ(ret, benchmark);

	auto ret1 =
		SwitchType<std::string, std::vector<std::string>>{"hello"}
			.Case("hello",
				  []() -> std::vector<std::string> { return std::vector<std::string>{"dog"}; })
			.Default(std::vector<std::string>{"cat"});
	auto benchmark1 = std::vector<std::string>{"dog"};
	ASSERT_EQ(ret1, benchmark1);
}

TEST(SwitchVoid, VOID)
{

	std::string ret;
	SwitchType<std::string, void>{"hello"}
		.Case("hello", [&ret]() { ret = "dog"; })
		.Default([&ret]() { ret = "cat"; });
	ASSERT_EQ(ret, "dog");
	SwitchType<std::string, void>{"hello"}
		.Case("helo", [&ret]() { ret = "dog"; })
		.Default([&ret]() { ret = "cat"; });
	ASSERT_EQ(ret, "cat");
}

TEST(Switch, SwitchClause)
{
	std::string ret;
	Switch("hello")
		.Case("hello", [&ret]() { ret = "dog"; })
		.Case("world", [&ret]() { ret = ""; })
		.Default([&ret]() { ret = "cat"; });
	ASSERT_EQ(ret, "dog");
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}