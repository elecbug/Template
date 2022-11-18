#pragma once
#include <iostream>
#include "queue.cpp";

namespace EB
{
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

			Node(T data = 0)
			{
				this->left = 0;
				this->right = 0;
				this->data = data;
			}
		};

	private:
		Node* root;
		size_t size;

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
		void remove_order(Node* root, Queue<T>* queue, bool (*condition)(T data))
		{
			if (root)
			{
				if (condition(root->data))
				{
					queue->enque(root->data);
				}
				remove_order(root->left, queue, condition);
				remove_order(root->right, queue, condition);
			}
		}

	public:
		BST()
		{
			this->root = 0;
			this->size = 0;
		}
		BST(T* values, size_t length)
		{
			this->root = 0;
			insert(values, length);
			this->size = 0;
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
					if (location->data > value)
					{
						if (location->left)
						{
							location = location->left;
						}
						else
						{
							location->left = new Node(value);
							this->size++;

							return true;
						}
					}
					else if (location->data < value)
					{
						if (location->right)
						{
							location = location->right;
						}
						else
						{
							location->right = new Node(value);
							this->size++;

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

		bool remove(T value)
		{
			Node* location = this->root;
			Node* parent = 0;

			while (true)
			{
				if (location)
				{
					if (location->data < value)
					{
						parent = location;
						location = location->right;
					}
					else if (location->data > value)
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

							delete location;
							this->size--;

							return true;
						}

					}
				}
				else
				{
					return false;
				}
			}
		}
		size_t remove_all(bool (*condition)(T value) = [](T value)->bool {return true; })
		{
			Queue<T>* queue = new Queue<T>();
			size_t count = 0;

			remove_order(this->root, queue, condition);

			while (!queue->is_empty())
			{
				remove(queue->deque());
				count++;
			}
			delete queue;

			return count;
		}

		bool find(T value)
		{
			Node* location = this->root;

			while (true)
			{
				if (location)
				{
					if (location->data < value)
					{
						location = location->right;
					}
					else if (location->data > value)
					{
						location = location->left;
					}
					else
					{
						return true;
					}
				}
				else
				{
					return false;
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
	};
}
