#pragma once

namespace EB
{
	template <typename T>
	class List
	{
	private:
		class Node
		{
		public:
			T data;
			Node* previous;
			Node* next;

			Node(T data = 0)
			{
				this->previous = 0;
				this->next = 0;
				this->data = data;
			}
		};

	private:
		Node* head;
		Node* tail;
		size_t size;

		Node*& get(size_t index)
		{
			if (index >= 0 && index <= this->size / 2)
			{
				Node* result = this->head->next;

				for (int i = 0; i < index; i++)
				{
					result = result->next;
				}

				return result;
			}
			else if (index > this->size / 2 && index <= this->size)
			{
				Node* result = this->tail;

				for (int i = this->size; i > index; i--)
				{
					result = result->previous;
				}

				return result;
			}
			else
			{
				throw "OutOfIndex";
			}
		}

		void initailize()
		{
			this->head = new Node();
			this->tail = new Node();

			this->head->next = this->tail;
			this->tail->previous = this->head;

			this->size = 0;
		}

	public:
		List(size_t count = 0, T init_value = 0)
		{
			initailize();

			for (int i = 0; i < count; i++)
			{
				insert(0, init_value);
			}
		}
		List(T* values, size_t length)
		{
			initailize();

			for (int i = 0; i < length; i++)
			{
				insert(i, values[i]);
			}
		}
		List(const List<T>& list)
		{
			initailize();

			for (Node* temp = list.head->next; temp != list.tail; temp = temp->next)
			{
				add(temp->data);
			}
		}

		~List()
		{
			while (count() != 0)
			{
				remove_at(0);
			}

			delete this->head;
			delete this->tail;
		}

		void insert(size_t index, T value)
		{
			Node* creat = new Node(value);

			creat->next = get(index);
			creat->previous = creat->next->previous;

			creat->next->previous = creat;
			creat->previous->next = creat;

			this->size++;
		}
		void add(T value)
		{
			insert(count(), value);
		}
		void append(List<T>& connecting)
		{
			for (int i = 0; i < connecting.count(); i++)
			{
				insert(count(), connecting.at(i));
			}
		}

		T& at(size_t index)
		{
			return get(index)->data;
		}

		T remove_at(size_t index)
		{
			Node* erase = get(index);
			T result = erase->data;

			erase->previous->next = erase->next;
			erase->next->previous = erase->previous;

			delete erase;

			this->size--;

			return result;
		}
		void remove_all(bool (*condition)(T x) = [](T x)->bool {return true; })
		{
			for (int i = 0; i < count(); i++)
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
			Node* temp = this->head->next;

			for (int i = 0; i < count(); i++)
			{
				if (temp->data == value)
				{
					return i;
				}
				else
				{
					temp = temp->next;
				}
			}

			return -1;
		}
		size_t index_of(bool (*condition)(T x))
		{
			Node* temp = this->head->next;

			for (int i = 0; i < count(); i++)
			{
				if (condition(at(i)))
				{
					return i;
				}
				else
				{
					temp = temp->next;
				}
			}

			return -1;
		}
		size_t count()
		{
			return this->size;
		}

		List<T>* sublist(size_t start, size_t end)
		{
			List<T>* result = new List<T>(0);

			for (int i = start; i < end; i++)
			{
				result->insert(i - start, at(i));
			}

			return result;
		}
	};
}