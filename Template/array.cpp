#pragma once
#include <stdlib.h>

namespace EB
{
	template <typename T>
	class Array
	{
	private:
		T* values;
		size_t size;
	
	public:
		Array(size_t count)
		{
			this->values = new T[count];
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

	public:
		void insert(size_t index, T value)
		{
			if (index >= 0 && index <= this->size)
			{
				this->values = (T*)realloc(this->values, sizeof(T) * (this->size + 1));
				this->size++;

				for (int i = this->size - 1; i > index; i--)
				{
					this->values[i] = this->values[i - 1];
				}
				this->values[index] = value;
			}
			else
			{
				throw "OutOfIndex";
			}
		}
		void add(T value)
		{
			this->values = (T*)realloc(this->values, sizeof(T) * (this->size + 1));
			this->size++;

			this->values[this->size - 1] = value;
		}
		void append(Array<T>& connecting)
		{
			this->values = (T*)realloc(this->values, sizeof(T) * (this->size + connecting.size));

			for (int i = this->size; i < this->size + connecting.size; i++)
			{
				this->values[i] = connecting.values[i - this->size];
			}

			this->size += connecting.size;
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

				for (int i = index; i < this->size - 1; i++)
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

			return -1;
		}
		size_t index_of(bool (*condition)(T x))
		{
			for (int i = 0; i < count(); i++)
			{
				if (condition(at(i)))
				{
					return i;
				}
			}

			return -1;
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

				for (int i = start; i < end; i++)
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
	};
}