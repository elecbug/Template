#include <iostream>
#include <crtdbg.h>
#include "list.cpp"

void test()
{
	EB::List<int> list = EB::List<int>(7);

	for (int i = 0; i < 10; i++)
		list.insert(0, i);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";

	list.remove(1);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";

	list.insert(list.count(), -1);
	list.at(0) = 8;

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";

}

int main()
{
	test();
	_CrtDumpMemoryLeaks();
}