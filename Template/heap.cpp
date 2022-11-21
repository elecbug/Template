#pragma once
#include "array.cpp"

namespace EB
{
	template <typename T>
	class Heap
	{
	private:
		Array<T>* data;
		bool (*condition)(T x, T y);

	private:
		inline size_t parent(size_t index)
		{
			return (index - 1) / 2;
		}
		inline size_t left(size_t index)
		{
			return index * 2 + 1;
		}
		inline size_t right(size_t index)
		{
			return index * 2 + 2;
		}

		inline void swap(T& x, T& y)
		{
			T temp = x;
			x = y;
			y = temp;
		}

		void up_swap(size_t index)
		{
			if (!this->condition(this->data->at(index), this->data->at(parent(index))))
			{
				swap(this->data->at(index), this->data->at(parent(index)));
				up_swap(parent(index));
			}
		}

	public:
		Heap(bool(*condition)(T x, T y) = [](T x, T y)->bool {return x < y; })
		{
			this->data = new Array<T>(0);
			this->condition = condition;
		}
		Heap(T* values, size_t length, bool(*condition)(T x, T y) = [](T x, T y)->bool {return x < y; })
		{
			this->data = new Array<T>(length);
			insert(values, length);
			this->condition = condition;
		}
		Heap(const Heap<T>& heap)
		{
			this->data = new Array<T>(*heap->data);
			this->condition = heap.condition;
		}

		~Heap()
		{
			delete data;
		}

		void insert(T value)
		{
			this->data->add(value);
			up_swap(this->data->count() - 1);
		}
		void insert(T* values, size_t length)
		{
			for (int i = 0; i < length; i++)
			{
				insert(values[i]);
			}
		}
	};
}