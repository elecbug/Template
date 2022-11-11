namespace EB
{
	template <typename T>
	class List
	{
	private:
		class Node
		{
		public:
			T value;
			Node* previous;
			Node* next;

			Node(T data = 0)
			{
				this->previous = 0;
				this->next = 0;
				this->value = data;
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
		List(T* data_array, size_t length)
		{
			initailize();

			for (int i = 0; i < length; i++)
			{
				insert(i, data_array[i]);
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

		void insert(size_t index, T data)
		{
			Node* creat = new Node(data);

			creat->next = get(index);
			creat->previous = creat->next->previous;

			creat->next->previous = creat;
			creat->previous->next = creat;

			this->size++;
		}
		void add(T data)
		{
			insert(count(), data);
		}
		void append(List<T>& post)
		{
			for (int i = 0; i < post.count(); i++)
			{
				insert(count(), post.at(i));
			}
		}

		T& at(size_t index)
		{
			return get(index)->value;
		}

		T remove_at(size_t index)
		{
			Node* erase = get(index);
			T result = erase->value;

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

		size_t index_of(T data)
		{
			Node* temp = this->head->next;

			for (int i = 0; i < count(); i++)
			{
				if (temp->value == data)
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

		List<T>& sublist(size_t start, size_t end)
		{
			List<T>* result = new List(0);

			for (int i = start; i < end; i++)
			{
				result->insert(i - start, at(i));
			}

			return *result;
		}
	};
}