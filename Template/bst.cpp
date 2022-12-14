#pragma once
#include <iostream>

namespace EB
{
	template <typename T>
	class Queue;

	const int INORDER = 0;
	const int PREORDER = 1;
	const int POSTORDER = 2;

	template <typename T>
	class BST
	{
	private:
		class Node
		{
		public:
			Node* left, * right;
			T data;

			Node(T data)
			{
				this->left = 0;
				this->right = 0;
				this->data = data;
			}
		};

	private:
		Node* root;
		size_t size;
		bool avl_mode;

		void inorder(Node* root)
		{
			if (root)
			{
				inorder(root->left);
				std::cout << root->data << " ";
				inorder(root->right);
			}
		}
		void preorder(Node* root)
		{
			if (root)
			{
				std::cout << root->data << " ";
				preorder(root->left);
				preorder(root->right);
			}
		}
		void postorder(Node* root)
		{
			if (root)
			{
				postorder(root->left);
				postorder(root->right);
				std::cout << root->data << " ";
			}
		}
		void condition_order(Node* root, Queue<T>* queue, bool (*condition)(T data))
		{
			if (root)
			{
				if (condition(root->data))
				{
					queue->enque(root->data);
				}
				condition_order(root->left, queue, condition);
				condition_order(root->right, queue, condition);
			}
		}

	private:
		inline long long max(long long x, long long y) { return x > y ? x : y; }
		long long height(Node* node)
		{
			if (!node)
			{
				return -1;
			}
			else
			{
				return max(height(node->left), height(node->right)) + 1;
			}
		}

		Node* single_left(Node* x)
		{
			Node* w = x->right;
			x->right = w->left;
			w->left = x;
			return w;
		}
		Node* single_right(Node* w)
		{
			Node* x = w->left;
			w->left = x->right;
			x->right = w;
			return x;
		}
		Node* check_violation(Node* node)
		{
			long long balance = height(node->left) - height(node->right);

			if (balance > 1)
			{
				if (node->left->left)
				{
					// LL
					// printf("LL violation\n");
					node = single_right(node);
				}
				else if (node->left->right)
				{
					// LR
					// printf("LR violation\n");
					node->left = single_left(node->left);
					node = single_right(node);
				}
			}
			else if (balance < -1)
			{
				if (node->right->right)
				{
					// RR
					// printf("RR violation\n");
					node = single_left(node);
				}
				else if (node->right->left)
				{
					// RL
					// printf("RL violation\n");
					node->right = single_right(node->right);
					node = single_left(node);
				}
			}

			return node;
		}
		void avl_violation(Node*& root)
		{
			if (root)
			{
				root = check_violation(root);
				avl_violation(root->left);
				avl_violation(root->right);
			}
		}

		bool (*condition)(T x, T y) = [](T x, T y)->bool { return x < y; };

	public:
		BST(bool avl_mode = false)
		{
			this->root = 0;
			this->size = 0;
			this->avl_mode = avl_mode;
		}
		BST(T* values, size_t length, bool avl_mode = false)
		{
			this->root = 0;
			this->size = 0;
			this->avl_mode = avl_mode;
			insert(values, length);
		}
		BST(const BST<T>& bst)
		{
			this->avl_mode = bst.avl_mode;

			Queue<T>* queue = new Queue<T>();
			condition_order(bst.root, queue, [](T data)->bool { return true; });

			while (!queue->is_empty())
			{
				insert(queue->deque());
			}

			delete queue;
		}

		~BST()
		{
			remove_all();
		}

		bool insert(T value)
		{
			if (!this->root)
			{
				this->root = new Node(value);
				this->size++;

				return true;
			}
			else
			{
				Node* location = this->root;

				while (true)
				{
					if (this->condition(value, location->data))
					{
						if (location->left)
						{
							location = location->left;
						}
						else
						{
							location->left = new Node(value);
							this->size++;

							if (this->avl_mode)
							{
								avl_violation(this->root);
							}

							return true;
						}
					}
					else if (this->condition(location->data, value))
					{
						if (location->right)
						{
							location = location->right;
						}
						else
						{
							location->right = new Node(value);
							this->size++;

							if (this->avl_mode)
							{
								avl_violation(this->root);
							}

							return true;
						}
					}
					else
					{
						return false;
					}
				}
			}
		}
		bool insert(T* values, size_t length)
		{
			bool result = true;

			for (int i = 0; i < length; i++)
			{
				result &= insert(values[i]);
			}

			return result;
		}

		T remove(T value)
		{
			Node* location = this->root;
			Node* parent = 0;

			while (true)
			{
				if (location)
				{
					if (this->condition(location->data, value))
					{
						parent = location;
						location = location->right;
					}
					else if (this->condition(value, location->data))
					{
						parent = location;
						location = location->left;
					}
					else
					{
						if (location->left && location->right)
						{
							Node* max = location->left;

							while (max->right)
							{
								max = max->right;
							}

							location->data = max->data;
							parent = location;
							location = location->left;

							value = max->data;
						}
						else
						{
							if (this->root == location)
							{
								if (this->size == 1)
								{
									this->root = 0;
								}
								else if (location->left)
								{
									this->root = location->left;
								}
								else if (location->right)
								{
									this->root = location->right;
								}
							}
							else if (location->right)
							{
								if (parent->left == location)
								{
									parent->left = location->right;
								}
								else if (parent->right == location)
								{
									parent->right = location->right;
								}
							}
							else if (location->left)
							{
								if (parent->left == location)
								{
									parent->left = location->left;
								}
								else if (parent->right == location)
								{
									parent->right = location->left;
								}
							}
							else
							{
								if (parent->left == location)
								{
									parent->left = 0;
								}
								else if (parent->right == location)
								{
									parent->right = 0;
								}
							}

							T result = location->data;

							delete location;
							this->size--;

							if (this->avl_mode && this->root)
							{
								avl_violation(this->root);
							}

							return result;
						}
					}
				}
				else
				{
					throw "NotFound";
				}
			}
		}
		size_t remove_all(bool (*condition)(T value) = [](T value)->bool {return true; })
		{
			Queue<T>* queue = new Queue<T>();
			size_t count = 0;

			condition_order(this->root, queue, condition);

			while (!queue->is_empty())
			{
				remove(queue->deque());
				count++;
			}
			delete queue;

			return count;
		}

		T find(T value)
		{
			Node* location = this->root;

			while (true)
			{
				if (location)
				{
					if (this->condition(location->data, value))
					{
						location = location->right;
					}
					else if (this->condition(value, location->data))
					{
						location = location->left;
					}
					else
					{
						return location->data;
					}
				}
				else
				{
					throw "NotFound";
				}
			}
		}
		void order(int tag)
		{
			switch (tag)
			{
			case INORDER:
				inorder(this->root);
				break;
			case PREORDER:
				preorder(this->root);
				break;
			case POSTORDER:
				postorder(this->root);
				break;
			default:
				break;
			}
		}

		size_t count()
		{
			return this->size;
		}
	};
}
