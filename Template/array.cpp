#pragma once
#include <stdlib.h>

namespace EB
{
	template <typename T>
	class List;
	template <typename T>
	class Heap;

	template <typename T>
	class Array
	{
	private:
		T* values;
		size_t size;
	
	private:
		void swap(T& x, T& y)
		{
			T temp = x;
			x = y;
			y = temp;
		}

	public:
		Array(size_t count = 0, T init_value = (T)0)
		{
			this->values = new T[count];
			for (int i = 0; i < count; i++)
			{
				this->values[i] = init_value;
			}
			this->size = count;
		}
		Array(T* values, size_t length)
		{
			this->values = new T[length];
			this->size = length;

			memcpy(this->values, values, length * sizeof(T));
		}
		Array(const Array<T>& arr)
		{
			this->values = new T[arr.size];
			this->size = arr.size;

			memcpy(this->values, arr.values, arr.size * sizeof(T));
		}

		~Array()
		{
			delete this->values;
		}

		void insert(size_t index, T value)
		{
			if (index >= 0 && index <= this->size)
			{
				if (this->values = (T*)realloc(this->values, sizeof(T) * (this->size + 1)))
				{
					this->size++;

					for (size_t i = this->size - 1; i > index; i--)
					{
						this->values[i] = this->values[i - 1];
					}
					this->values[index] = value;
				}
				else
				{
					throw "MemoryLeaks";
				}
			}
			else
			{
				throw "OutOfIndex";
			}
		}
		void add(T value)
		{
			if (this->values = (T*)realloc(this->values, sizeof(T) * (this->size + 1)))
			{
				this->size++;

				this->values[this->size - 1] = value;
			}
			else
			{
				throw "MemoryLeaks";
			}
		}
		void append(Array<T>& connecting)
		{
			if (this->values = (T*)realloc(this->values, sizeof(T) * (this->size + connecting.size)))
			{
				for (size_t i = this->size; i < this->size + connecting.size; i++)
				{
					this->values[i] = connecting.values[i - this->size];
				}

				this->size += connecting.size;
			}
			else
			{
				throw "MeomoryLeaks";
			}
		}

		T& at(size_t index)
		{
			if (index >= 0 && index < this->size)
			{
				return this->values[index];
			}
			else
			{
				throw "OutOfIndex";
			}
		}

		T remove_at(size_t index)
		{
			if (index >= 0 && index < this->size)
			{
				T result = this->values[index];

				for (size_t i = index; i < this->size - 1; i++)
				{
					this->values[i] = this->values[i + 1];
				}

				this->size--;
				
				return result;
			}
			else
			{
				throw "OutOfIndex";
			}
		}
		void remove_all(bool (*condition)(T x) = [](T x)->bool {return true; })
		{
			for (int i = 0; i < this->size; i++)
			{
				if (condition(at(i)))
				{
					remove_at(i);
					i--;
				}
			}
		}
		
		size_t index_of(T value)
		{
			for (int i = 0; i < this->size; i++)
			{
				if (value == this->values[i])
				{
					return i;
				}
			}

			throw "NotFound";
		}
		size_t find(bool (*condition)(T x))
		{
			for (int i = 0; i < count(); i++)
			{
				if (condition(at(i)))
				{
					return i;
				}
			}

			throw "NotFound";
		}
		size_t count()
		{
			return this->size;
		}

		Array<T>* subarray(size_t start, size_t end)
		{
			if (start >= 0 && end <= this->size)
			{
				Array<T>* result = new Array<T>(end - start);

				for (size_t i = start; i < end; i++)
				{
					result->values[i - start] = this->values[i];
				}

				return result;
			}
			else
			{
				throw "OutOfIndex";
			}
		}

		List<T>* to_list()
		{
			List<T>* result = new List<T>(this->values, this->size);
			
			return result;
		}

		Array<T>* sort()
		{
			Heap<T>* heap = new Heap<T>(this->values, this->size, [](T x, T y)->bool {return x > y; });
			
			return heap->heap_sort();
		}
	};
}