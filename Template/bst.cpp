#pragma once
#include <iostream>

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
		bool is_self_balaced;

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

	public:
		BST(bool avl = false)
		{
			this->root = 0;
			this->is_self_balaced = avl;
		}
		BST(T* values, size_t length, bool avl = false)
		{
			this->root = 0;
			insert(values, length);
			this->is_self_balaced = avl;
		}

		~BST()
		{
		}

		bool insert(T value)
		{
			if (!this->root)
			{
				this->root = new Node(value);
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
								if (location->left)
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
		void remove_all(bool (*condition)(T value) = [](T value)->bool {return true; })
		{
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
