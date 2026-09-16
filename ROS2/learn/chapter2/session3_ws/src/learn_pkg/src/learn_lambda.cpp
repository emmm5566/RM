//Lambda
// [caoture list](parameters) -> return_type
//	{
//		function body;
//	};

#include <iostream>
#include <algorithm>

int main()
{
	auto add = [](int a, int b) -> int
		{
			return a + b;
		};
	int sum = add(10086, 888);
	auto print_sum = [sum]() -> void
		{
			std::cout << sum << std::endl;
		};
	print_sum();

	return 0;
}