#include <stdio.h>
#include <vector>

#include "vector.h"

struct Test
{
public:
	int value = 0;

	Test()
	{
		printf ("Default Constructor\n");
	}

	Test(int Value) : value(Value)
	{
		printf ("Constructor Of Argument\n");
	}

	Test(const Test& Other)
	{
		value = Other.value;
		printf ("Copy Constructor\n");
	}

	Test(Test&& Other)
	{
		value = Other.value;
		printf("Move Constructor\n");
	}

	Test operator = (const Test& Other)
	{
		value = Other.value;
		printf("Operator = \n");
		return *this;
	}

	Test operator = (Test&& Other)
	{
		value = Other.value;
		printf("Operator rValue = \n");
		return *this;
	}
};

template <typename STL, typename Dt>
void VectorSimulate()
{
	STL test;
	test.reserve(10);
	test.push_back(Dt(1));
	test.push_back(Dt(2));
	test.push_back(Dt(3));
	test.push_back(Dt(4));

	int value = 10;
	test.push_back(value);

	Dt t1 = Dt(20);
	test.push_back(t1);

	STL test2 = test;
	STL test3 = std::move(test2);

	for (auto it = test.begin(); it != test.end(); ++it)
	{
		printf("%d\n", it->value);
	}

	for (auto it = test2.begin(); it != test2.end(); ++it)
	{
		printf("%d\n", it->value);
	}

	for (auto it = test3.begin(); it != test3.end(); ++it)
	{
		printf("%d\n", it->value);
	}
}

int main()
{
	VectorSimulate<std::vector<Test>, Test>();
	printf("\n\n");
	VectorSimulate<mx::vector<Test>, Test>();
}