#pragma once
#include "list.cpp"

namespace EB
{
	template <typename T>
	class Queue : protected List<T>
	{
	public:
		Queue() : List<T>(0)
		{
		}

		void enque(T value)
		{
			this->insert(0, value);
		}

		T deque()
		{
			T result = this->at(this->count() - 1);
			this->remove_at(this->count() - 1);

			return result;
		}

		T peek()
		{
			return this->at(this->count() - 1);
		}

		bool is_empty()
		{
			return this->count() == 0;
		}
	};
}