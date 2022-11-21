#include <iostream>
#include <time.h>
#include <crtdbg.h>
#include "list.cpp"
#include "stack.cpp"
#include "queue.cpp"
#include "array.cpp"
#include "bst.cpp"
#include "heap.cpp"

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

	EB::Array<int>* arr = list3.to_array();

	for (int i = 0; i < arr->count(); i++)
		std::cout << arr->at(i) << " ";
	std::cout << std::endl;

	list4 = arr->to_list();

	for (int i = 0; i < list4->count(); i++)
		std::cout << list4->at(i) << " ";
	std::cout << std::endl;

	delete arr;
	delete list4;
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

void array_test()
{
	int src[] = { 0,1,2,3,4,5 };
	EB::Array<int> arr = EB::Array<int>(src, sizeof(src) / 4);

	arr.insert(0, -1);
	arr.add(6);
	arr.remove_at(7);
	arr.remove_all([](int x)->bool {return x >= 4; });

	for (int i = 0; i < arr.count(); i++)
		std::cout << arr.at(i) << " ";
	std::cout << std::endl;

	auto arr2 = EB::Array<int>(src, sizeof(src) / 4);
	arr.append(arr2);

	for (int i = 0; i < arr.count(); i++)
		std::cout << arr.at(i) << " ";
	std::cout << std::endl;

	auto arr3 = arr.subarray(1, 4);

	for (int i = 0; i < arr3->count(); i++)
		std::cout << arr3->at(i) << " ";
	std::cout << std::endl;

	delete arr3;
}

void bst_test()
{
	EB::BST<int> bst = EB::BST<int>();

	for (int i = 0; i < 100; i++)
	{
		bst.insert(i % 2 == 1 ? i * 2 + 1 : i / 2);
	}

	EB::BST<int> bst2 = EB::BST<int>(bst);

	bst.order(EB::INORDER);
	std::cout << std::endl;
	
	for (int i = 110; i < 150; i++)
	{
		std::cout << (bst.remove(i)? "T" : "F") << " ";
	}
	std::cout << std::endl;

	bst.remove_all([](int data)->bool {return data > 10 && data < 30; });

	bst.order(EB::INORDER);
	std::cout << std::endl;

	bst.remove_all();
	
	bst.order(EB::INORDER);
	std::cout << std::endl;

	bst2.order(EB::INORDER);
	std::cout << std::endl;

	EB::BST<int> bst3 = EB::BST<int>(true);

	for (int i = 0; i < 10; i++)
	{
		bst3.insert(i);
	}

	bst3.order(EB::PREORDER);
	std::cout << std::endl;

	bst3.order(EB::INORDER);
	std::cout << std::endl;

	EB::BST<int> bst4 = EB::BST<int>(true);

	for (int i = 0; i < 10; i++)
	{
		bst4.insert(i);
	}

	bst4.remove_all([](int i)->bool {return i > 4 && i < 8; });

	bst4.order(EB::PREORDER);
	std::cout << std::endl;

	bst4.order(EB::INORDER);
	std::cout << std::endl;


}

void heap_test()
{
	EB::Heap<int> heap = EB::Heap<int>([](int x, int y)->bool {return x < y; });
	
	for (int i = 0; i < 10000; i++)
	{
		heap.insert(i % 2 == 0 ? i * 4 : i * 3);
	}

	EB::Array<int>* sorting = heap.heap_sort();

	while (!heap.is_empty())
	{
		std::cout << heap.remove_top() << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < sorting->count(); i++)
	{
		std::cout << sorting->at(i) << " ";
	}
	std::cout << std::endl;

	delete sorting;
}

int main()
{
	list_test();
	// stack_test();
	// queue_test();
	// array_test();
	// bst_test();
	// heap_test();

	_CrtDumpMemoryLeaks();
}