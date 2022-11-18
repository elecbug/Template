#pragma once
#include "list.cpp"

namespace EB
{
	template <typename T>
	class Stack : protected List<T>
	{
	public:
		Stack() : List<T>(0)
		{
		}

		void push(T value)
		{
			this->insert(0, value);
		}

		T pop()
		{
			T result = this->at(0);
			this->remove_at(0);

			return result;
		}

		T top()
		{
			return this->at(0);
		}

		bool is_empty()
		{
			return this->count() == 0;
		}
	};
}