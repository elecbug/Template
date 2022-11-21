#pragma once
#include "array.cpp"

namespace EB
{
	template <typename T>
	class Heap
	{
	protected:
		Array<T>* data;
		size_t size;
		bool (*condition)(T x, T y);

	private:
		size_t parent(size_t index)
		{
			return index > 0 ? (index - 1) / 2 : 0;
		}
		size_t left(size_t index)
		{
			return index * 2 + 1;
		}
		size_t right(size_t index)
		{
			return index * 2 + 2;
		}

		void swap(T& x, T& y)
		{
			T temp = x;
			x = y;
			y = temp;
		}

		void up_swap(size_t index)
		{
			if (this->condition(this->data->at(index), this->data->at(parent(index))) && parent(index) != index)
			{
				swap(this->data->at(index), this->data->at(parent(index)));
				up_swap(parent(index));
			}
		}
		void down_swap(size_t index)
		{
			if (left(index) < this->size && this->condition(this->data->at(left(index)), this->data->at(index)))
			{
				swap(this->data->at(index), this->data->at(left(index)));
				down_swap(left(index));
			}
			if (right(index) < this->size && this->condition(this->data->at(right(index)), this->data->at(index)))
			{
				swap(this->data->at(index), this->data->at(right(index)));
				down_swap(right(index));
			}
		}

	public:
		Heap(bool(*condition)(T root, T leaf) = [](T x, T y)->bool { return x > y; })
		{
			this->data = new Array<T>(0);
			this->size = 0;
			this->condition = condition;
		}
		Heap(T* values, size_t length, bool(*condition)(T root, T leaf) = [](T x, T y)->bool { return x > y; })
		{
			this->data = new Array<T>(0); 
			this->size = 0;
			insert(values, length);
			this->condition = condition;
		}
		Heap(const Heap<T>& heap)
		{
			this->data = new Array<T>(*heap.data);
			this->size = heap.size;
			this->condition = heap.condition;
		}

		~Heap()
		{
			delete this->data;
		}

		void insert(T value)
		{
			this->data->add(value);
			this->size++;

			up_swap(this->data->count() - 1);
		}
		void insert(T* values, size_t length)
		{
			for (int i = 0; i < length; i++)
			{
				insert(values[i]);
			}
		}

		T remove_top()
		{
			if (!is_empty())
			{
				T result = this->data->at(0);

				this->data->at(0) = this->data->at(this->data->count() - 1);
				this->data->remove_at(this->data->count() - 1);
				this->size--;

				down_swap(0);

				return result;
			}
			else
			{
				throw "OutOfIndex";
			}
		}

		size_t count()
		{
			return this->size;
		}
		bool is_empty()
		{
			return this->size == 0;
		}

		Array<T>* heap_sort()
		{
			Array<T>* result = new Array<T>(this->size);
			Heap<T> heap = Heap<T>(*this);

			for (int i = 0; i < this->size; i++)
			{
				result->at(i) = heap.remove_top();
			}

			return result;
		}
	};
}