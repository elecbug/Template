#pragma once

namespace EB
{
	template <typename T>
	class BST;

	template <typename Key, typename Value>
	class Set
	{
	private:
		Key k;
		Value v;
	public:
		Set(Key key = 0, Value value = 0)
		{
			this->k = key;
			this->v = value;
		}

		Key& key()
		{
			return this->k;
		}
		Value& value()
		{
			return this->v;
		}

		friend bool operator < (Set x, Set y)
		{
			return x.key() < y.key();
		}
		friend bool operator > (Set x, Set y)
		{
			return x.key() > y.key();
		}
	};
	
	template <typename Key, typename Value>
	class Map
	{
	private:
		BST<Set<Key, Value>>* key_bst;
	
		void initialize()
		{
			this->key_bst = new BST<Set<Key, Value>>(true);
		}

	public:
		Map()
		{
			initialize();
		}
		Map(Set<Key, Value>* sets, size_t length)
		{
			initialize();

			this->key_bst->insert(sets, length);
		}

		~Map()
		{
			delete this->key_bst;
		}

		void insert(Set<Key, Value> set)
		{
			this->key_bst->insert(set);
		}
		void insert(Key key, Value value)
		{
			insert(EB::Set<Key, Value>(key, value));
		}

		Value& value(Key key)
		{
			return this->key_bst->find(EB::Set<Key, Value>(key, 0)).value();
		}
		void remove(Key key)
		{
			this->key_bst->remove(Set<Key, Value>(key, 0));
		}
	};
}