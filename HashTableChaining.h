#ifndef HASHTABLE_H
#define HASHTABLE_H
/*
A critical statistic for a hash table is the load factor, defined as

load factor = n/k

where

n is the number of entries occupied in the hash table.
k is the number of buckets.
*/



template <typename HashElement>
class HashTableChaining
{
private:

	
	class node
	{
	public:
		HashElement val;
		node *next;
		node* getNext() {
			return next;
		}
		node()
		{
			this->next = nullptr;
		}
		node(const node * rhs) {
			
				const node *walker = rhs;
 				this->val = walker->val;
				node *follower = this;
				walker = walker->next;

				while (walker != nullptr)
				{
					follower->next = new node(walker->val);
					walker = walker->next;
					follower = follower->next;

				}
			
		}
		node(HashElement val)
		{
			this->val = val;
			this->next = nullptr;
		}
		bool add(HashElement val)
		{
			bool ret;
			if (this->val == val)
			{
				ret = false;
			}
			else if (next == nullptr)
			{
				if (this->val == "")
				{
					this->val = val;
					ret = true;
				}
				else {
					this->next = new node(val);
					ret = true;
				}

			}
			else
			{
				this->next->add(val);
				ret = true;

				
			}
			return ret;
		}
		HashElement getFirst() {
			return this->val;
		}
		bool removeNotFirst(HashElement val)
		{
			
			bool retVal = false;
			if (this->next->val == val)
			{
				retVal = true;
				node *newNode = this->next;
				delete next;
				this->next = newNode;
			}
			else
			{
				if (this->next->next != nullptr)
				{
					retVal = this->next->removeNotFirst(val);
				}
			}
			return retVal;
		}
		~node()
		{
			
			
			deallocate();
			
			
		}
		void deallocate()
		{/*
			node* walker = this;
			node* follower = this;
			while (walker != nullptr && walker != NULL)
			{
 				walker = walker->next;
				delete follower;
				follower = walker;
			}*/
			if (this->next != nullptr && this->next != NULL)
			{
				delete next;
			}

		
		}
		/*void resetCollisionMaýbe() {
			if (this->next != nullptr)
			{
				this->next.deallocate();
			}
			this->next = nullptr;
		}
		*/
		int getIfExists(HashElement val, int pos = 0)
		{
			int retVal = pos;
			if (this->val != val)
			{

				retVal++;
				if (this->next != nullptr)
				{
					return this->next->getIfExists(val, retVal);
				}
				else
				{ 
					return -1;
				}
			}
			else
			{
				return retVal;
			}

		}

		bool getIfOccupied()
		{
			bool retVal = false;
			if (this->val != NULL)
			{
				retVal = true;
			}
			return retVal;
		}
		int getNrOfElem()
		{
			int retVal;
			if (this->next != nullptr)
			{
				retVal = next->getNrOfElem() + 1;
			}
			else
			{
				retVal = 1;
			}
			return retVal;
		}
		node& operator=(const node & aNode) 
		{
			if (*this != aNode)
			{
				deallocate();
				node walker = aNode;
				next = new node(walker.val);
				node *follower = next;
				node *walker2 = walker.next;

				while (walker2 != nullptr)
				{
					follower->next = new node(walker2->val);
					walker2 = walker2->next;
					follower = follower->next;

				}
			}
			return *this;
		}
	

		bool equal(const node & aNode)
		{
			bool retVal = false;
			Element walker = aElement;
			Element follower = this;

			while (follower.val == walker.val && retVal == false)
			{
				if (walker.next == nullptr || follower.next == nullptr)
				{
					if (walker.next == nullptr && follower.next == nullptr)
					{
						retVal = true;
					}
				}
				follower = follower.next;
				walker = walker.next;
			}
			return retVal;
		}
		bool operator==(const node & aNode) {
			return this->equal(aNode);
		}
		bool operator!=(const node & aNode)
		{
			return !(this->equal(aNode));
		}
		
	};
	

	// internal datastructure
	node **arr;
	int nrOfCollisions;
	int hashTableSize;
	int nrElements;
	int myHash(const HashElement& elem) const
	{
		static Hash<HashElement> hashFunc;
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}

public:
	HashTableChaining(int hashTableSize = 17);
	HashTableChaining(const HashTableChaining& aTable);
	virtual ~HashTableChaining();
	HashTableChaining& operator=(const HashTableChaining& aTable);
	int contains(const HashElement& elem) const; // returns index or -1
	bool insert(const HashElement& elem);
	bool remove(const HashElement& elem);
	//index? what should i return?
	HashElement& get(int index) const;
	void makeEmpty();
	double loadFactor() const;
	int getNrOfElements() const;
	int getNrOfCollisions() const;
	//reset? why?
	void resetNrOfCollisions();
	
};

#endif

template<typename HashElement>
inline HashTableChaining<HashElement>::HashTableChaining(int hashTableSize)
{
	nrElements = 0;
	this->nrOfCollisions = 0;
	this->hashTableSize = hashTableSize;
	this->arr = new node*[hashTableSize];
	for (int i = 0; i < hashTableSize; ++i)
	{
		arr[i] = nullptr;
	}
}

template<typename HashElement>
inline HashTableChaining<HashElement>::HashTableChaining(const HashTableChaining & aTable)
{
	this->nrOfCollisions = aTable.nrOfCollisions;
	this->hashTableSize = aTable.hashTableSize;
	this->nrElements = aTable.nrElements;

	this->arr = new node*[this->hashTableSize];

	for (int i = 0; i < aTable.hashTableSize; ++i)
	{
		if (aTable.arr[i] != nullptr) 
		{
			this->arr[i] = new node(aTable.arr[i]);
		}
		else
		{
			this->arr[i] = nullptr;
		}
	}
}

template<typename HashElement>
inline HashTableChaining<HashElement>::~HashTableChaining()
{
	for (int i = 0; i < this->hashTableSize; i++)
	{
		delete arr[i];
	}
	delete[] arr;
}



template<typename HashElement>
inline HashTableChaining<typename HashElement> & HashTableChaining<HashElement>::operator=(const HashTableChaining & aTable){
	if (this != &aTable)
	{
		this->nrOfCollisions = aTable.nrOfCollisions;
		this->hashTableSize = aTable.hashTableSize;
		this->nrElements = aTable.nrElements;
		
		for (int i = 0; i < this->hashTableSize; ++i)
		{
			delete arr[i];
		}

		delete[] arr;

		arr = new node*[this->hashTableSize];
		for (int i = 0; i < this->hashTableSize; ++i)
		{
			if (aTable.arr[i] != nullptr)
			{
				this->arr[i] = new node(aTable.arr[i]);
			}
			else {
				this->arr[i] = nullptr;
			}
		}
	}
	return *this;
}

template<typename HashElement>
inline int HashTableChaining<HashElement>::contains(const HashElement & elem) const
{
	int elemHash = this->myHash(elem);
	int pos = -1;
	
	if (arr[elemHash] != nullptr)
	{
		pos = arr[elemHash]->getIfExists(elem);
	}
	
	return pos;
}

template<typename HashElement>
inline bool HashTableChaining<HashElement>::insert(const HashElement & elem)
{
	bool retVal = false;

	if (this->contains(elem) == -1)
	{
		retVal = true;

		int pos = myHash(elem);
		if (arr[pos] == nullptr)
		{
			arr[pos] = new node(elem);
			++nrElements;
		}
		else
		{
			if (arr[pos]->getIfExists(elem) == -1)
			{
				arr[pos]->add(elem);
				++nrElements;
			}
			this->nrOfCollisions++;
		}
	}
	return retVal;
}

template<typename HashElement>
inline bool HashTableChaining<HashElement>::remove(const HashElement & elem)
{
	bool retVal = false;
	int pos = myHash(elem);

	if (arr[pos] != nullptr) {
		if (arr[pos]->getFirst() == elem)
		{
			node* temp = arr[pos]->getNext();
			delete arr[pos];

			arr[pos] = temp;
			retVal = true;
			nrElements--;
		}
		else {
			retVal = arr[pos]->removeNotFirst(elem);
			if (retVal)
			{
				this->nrOfCollisions--;
				nrElements--;
			}
			
		}
	}
	return retVal;
}

template<typename HashElement>
inline HashElement & HashTableChaining<HashElement>::get(int index) const
{
	return NULL;
	}

template<typename HashElement>
inline void HashTableChaining<HashElement>::makeEmpty()
{
	nrElements = 0;

	for (int i = 0; i < this->hashTableSize; ++i)
	{
		delete arr[i];
	}
	delete[] arr;

	arr = new node*[this->hashTableSize];
	for (int i = 0; i < this->hashTableSize; ++i)
	{
		arr[i] = nullptr;
	}
	this->resetNrOfCollisions();
}

template<typename HashElement>
inline double HashTableChaining<HashElement>::loadFactor() const
{
	

	return (double(this->nrElements)/this->hashTableSize);
}

template<typename HashElement>
inline int HashTableChaining<HashElement>::getNrOfElements() const
{

	return this->nrElements;
}

template<typename HashElement>
inline int HashTableChaining<HashElement>::getNrOfCollisions() const
{
	/*
	
	int temp;

	int count = 0;
	for (int i = 0; i < this->hashTableSize; ++i)
	{
		if (arr[i] != nullptr)
		{
			temp = arr[i]->getNrOfElem();
			if (temp > 0)
			{
				count += temp - 1;
			}
		}
	}
	return count;*/

	// faster
	return this->nrOfCollisions;
}

template<typename HashElement>
inline void HashTableChaining<HashElement>::resetNrOfCollisions()
{
	this->nrOfCollisions = 0;
}


