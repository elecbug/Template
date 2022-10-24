namespace EB
{
	template <typename T>
	class List
	{
		class Node 
		{
		private:
			T data;
			Node* front;
			Node* back;

		public: 
			Node(T data = 0)
			{
				this->front = 0;
				this->back = 0;
				this->data = data;
			}

			T& value()
			{
				return this->data;
			}

			Node*& previous() 
			{
				return this->front;
			}

			Node*& next()
			{
				return this->back;
			}
		};

	private:
		Node* head;
		Node* tail;
		size_t size;

		Node*& get(size_t index)
		{
			if (index >= 0 && index <= this->size)
			{
				Node* result = this->head->next();

				for (int i = 0; i < index; i++)
				{
					result = result->next();
				}

				return result;
			}
			else
			{
				throw "OutOfIndex";
			}
		}

	public:
		List(size_t count = 0)
		{
			this->head = new Node();
			this->tail = new Node();

			this->head->next() = this->tail;
			this->tail->previous() = this->head;

			this->size = 0;

			for (int i = 0; i < count; i++)
			{
				insert(0, 0);
			}
		}

		~List()
		{
			while (count() != 0)
			{
				remove(0);
			}

			delete this->head;
			delete this->tail;
		}

		void insert(size_t index, T data)
		{
			Node* creat = new Node(data);

			creat->next() = get(index);
			creat->previous() = creat->next()->previous();

			creat->next()->previous() = creat;
			creat->previous()->next() = creat;

			this->size++;
		}

		T& at(size_t index)
		{
			return get(index)->value();
		}

		T remove(size_t index)
		{
			Node* erase = get(index);
			T result = erase->value();

			erase->previous()->next() = erase->next();
			erase->next()->previous() = erase->previous();

			delete erase;

			this->size--;

			return result;
		}

		size_t count()
		{
			return this->size;
		}
	};
}