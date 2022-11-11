#include <iostream>
#include <crtdbg.h>
#include "list.cpp"

void test()
{
	EB::List<int> list = EB::List<int>(7);

	for (int i = 0; i < 10; i++)
		list.insert(list.count(), i);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	list.remove(1);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	list.insert(list.count(), -1);
	list.at(0) = 8;

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	std::cout << list.index_of(-1, [](int x, int y)->bool { return x == y; }) << std::endl;
	std::cout << list.index_of(8) << std::endl;

	EB::List<int> list2 = EB::List<int>(9, 10);
	list2.add(30);
	
	list2.append(list);

	for (int i = 0; i < list2.count(); i++)
		std::cout << list2.at(i) << " ";
	std::cout << std::endl;

	list = list2.sublist(5, 15);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;
}

int main()
{
	test();
	_CrtDumpMemoryLeaks();
}