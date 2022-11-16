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

		Node*& find_max(Node* node)
		{
			if (node->left == 0)
			{
				return node;
			}
			else
			{
				node = node->left;

				while (true)
				{
					if (node->right != 0)
					{
						node = node->right;
					}
					else if (node->left != 0)
					{
						node = node->left;
					}
					else
					{
						return node;
					}
				}
			}
		}

		void inorder(Node* root)
		{
			if (root != 0)
			{
				inorder(root->left);
				std::cout << root->data << " ";
				inorder(root->right);
			}
		}
		void preorder(Node* root)
		{
			if (root != 0)
			{
				std::cout << root->data << " ";
				preorder(root->left);
				preorder(root->right);
			}
		}
		void postorder(Node* root)
		{
			if (root != 0)
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
		}
		BST(T* values, bool avl = false)
		{
			this->root = 0;
		}

		~BST()
		{
		}

		bool insert(T value)
		{
			if (this->root == 0)
			{
				this->root = new Node(value);
				return true;
			}
			else
			{
				if (this->root->data > value)
				{
					this->root = this->root->left;
					return true;
				}
				else if (this->root->data < value)
				{
					this->root = this->root->right;
					return true;
				}
				else
				{
					return false;
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
		}
		void remove_all(bool (*condition)(T value) = [](T value)->bool {return true; })
		{
		}

		bool find(T value)
		{
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