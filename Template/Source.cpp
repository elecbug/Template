#include <iostream>
#include <crtdbg.h>
#include "list.cpp"
#include "stack.cpp"
#include "queue.cpp"

void list_test()
{
	EB::List<int> list = EB::List<int>(7);

	for (int i = 0; i < 10; i++)
		list.insert(list.count(), i);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	list.remove_at(1);

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	list.insert(list.count(), -1);
	list.at(0) = 8;

	for (int i = 0; i < list.count(); i++)
		std::cout << list.at(i) << " ";
	std::cout << std::endl;

	std::cout << list.index_of([](int x)->bool { return x == -1; }) << std::endl;
	std::cout << list.index_of(8) << std::endl;

	EB::List<int> list2 = EB::List<int>(9, 10);
	list2.add(30);
	
	list2.append(list);

	for (int i = 0; i < list2.count(); i++)
		std::cout << list2.at(i) << " ";
	std::cout << std::endl;

	EB::List<int>* list4 = list2.sublist(5, 15);

	for (int i = 0; i < list4->count(); i++)
		std::cout << list4->at(i) << " ";
	std::cout << std::endl;

	delete list4;

	list2.remove_all([](int x)->bool {return x > 5; });
	
	for (int i = 0; i < list2.count(); i++)
		std::cout << list2.at(i) << " ";
	std::cout << std::endl;

	EB::List<int> list3 = EB::List<int>(list2);

	for (int i = 0; i < list3.count(); i++)
		std::cout << list3.at(i) << " ";
	std::cout << std::endl;
}

void stack_test()
{
	EB::Stack<int> stack = EB::Stack<int>();

	for (int i = 0; i < 10; i++)
		stack.push(i);

	for (int i = 0; i < 5; i++)
		std::cout << stack.pop() <<" ";
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
		stack.push(i);

	std::cout << stack.top() << std::endl;

	for (int i = 0; i < 15; i++)
		std::cout << stack.pop() << " ";
	std::cout << std::endl;

}

void queue_test()
{
	EB::Queue<int> queue = EB::Queue<int>();

	for (int i = 0; i < 10; i++)
		queue.enque(i);

	for (int i = 0; i < 5; i++)
		std::cout << queue.deque() << " ";
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
		queue.enque(i);

	std::cout << queue.peek() << std::endl;

	for (int i = 0; i < 15; i++)
		std::cout << queue.deque() << " ";
	std::cout << std::endl;

}

int main()
{
	list_test();
	// stack_test();
	// queue_test();
	_CrtDumpMemoryLeaks();
}