#pragma once
#include <stdlib.h>

namespace EB
{
	template <typename T>
	class List;

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
		size_t middle(size_t* points)
		{
			if (at(points[0]) > at(points[1]) && at(points[0]) > at(points[2]))
			{
				return at(points[1]) > at(points[2]) ? points[1] : points[2];
			}
			else if (at(points[1]) > at(points[0]) && at(points[1]) > at(points[2]))
			{
				return at(points[0]) > at(points[2]) ? points[0] : points[2];
			}
			else
			{
				return at(points[0]) > at(points[1]) ? points[0] : points[1];
			}
		}
		void parted_qsort(size_t start, size_t end, bool (*condition)(T x, T y))
		{
			if (start < end)
			{
				size_t f_start = start, f_end = end;
				size_t points[] = { start, (start + end) / 2, end };
				size_t point = middle(points);

				swap(at(point), at(end));

				T& pivot = at(end);
				end--;

				while (start <= end)
				{
					while (condition(at(start), pivot))
					{
						start++;
					}
					while (condition(pivot, at(end)))
					{
						end--;
					}
					swap(at(start), at(end));
				}
				swap(at(start), at(end));
				swap(pivot, at(end + 1));

				parted_qsort(f_start, end, condition);
				parted_qsort(end + 2, f_end, condition);
			}
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

		void qsort(bool (*condition)(T x, T y) = [](T x, T y)->bool {return x < y; })
		{
			parted_qsort(0, this->size - 1, condition);
		}
	};
}