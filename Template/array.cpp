#pragma once
#include <stdlib.h>
#include <string.h>

namespace EB
{
	template <typename T>
	class Array
	{
	private:
		T* values;
		size_t count;
	
	public:
		Array(size_t count)
		{
			this->values = new T[count];
			this->count = count;
		}
		Array(T* values, size_t length)
		{
			this->values = new T[length];
			this->count = length;

			memcpy(this->values, values, length * sizeof(T));
		}
		Array(const EB::Array<T>& arr)
		{
			this->values = new T[arr.count];
			this->count = arr.count;

			memcpy(this->values, arr.values, arr.count * sizeof(T));
		}

		~Array()
		{
			delete this->values;
		}

	public:

	};
}