# C++23 core types

A group of core types based on C++23. Aims to make code concise and cleaner.

# Types

## Switch Clause

Switch clause which can be used on any type that support `==`. Can be used like this:

```c++
	auto ret = SwitchType<std::string, std::vector<std::string>>{"hello"}
				   .Case("hello", std::vector<std::string>{"dog", "cat"})
				   .Case("nihao", std::vector<std::string>{"animal"})
				   .get();
	auto benchmark = std::vector<std::string>{"dog", "cat"};
	ASSERT_EQ(ret, benchmark);
```

or:

```c++
	std::string ret;
	Switch("hello")
		.Case("hello", [&ret]() { ret = "dog"; })
		.Case("world", [&ret]() { ret = ""; })
		.Default([&ret]() { ret = "cat"; });
	ASSERT_EQ(ret, "dog");
```