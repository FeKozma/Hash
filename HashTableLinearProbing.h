#ifndef HASHTABLE_H
#define HASHTABLE_H

template <typename HashElement>
class HashTableLinear
{
private:
	// internal datastructure
	HashElement ** arr;
	bool* removed;
	int nrOfCollisions;
	int hashTableSize;
	int nrElements;
	int myHash(const HashElement& elem) const 
	{ 
		static Hash<HashElement> hashFunc; 
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
public:
	HashTableLinear(int hashTableSize = 17);
	HashTableLinear(const HashTableLinear& aTable);
	virtual ~HashTableLinear();
	HashTableLinear& operator=(const HashTableLinear& aTable);
	int contains(const HashElement& elem) const; // returns index or -1
	bool insert(const HashElement& elem);
	bool remove(const HashElement& elem);
	HashElement& get(int index) const;
	void makeEmpty();
	double loadFactor() const;
	int getNrOfElements() const;
	int getNrOfCollisions() const;
	void resetNrOfCollisions();
	
};

#endif

template<typename HashElement>
inline HashTableLinear<HashElement>::HashTableLinear(int hashTableSize)
{
	this->nrElements = 0;
	this->nrOfCollisions = 0;
	this->hashTableSize = hashTableSize;
	this->arr = new HashElement*[hashTableSize];
	for (int i = 0; i < this->hashTableSize; ++i)
	{
		arr[i] = nullptr;
	}

	removed = new bool[hashTableSize];

}

template<typename HashElement>
inline HashTableLinear<HashElement>::HashTableLinear(const HashTableLinear & aTable)
{
	this->nrElements = aTable.nrElements;
	this->nrOfCollisions = aTable.nrOfCollisions;
	this->hashTableSize = aTable.hashTableSize;
	this->arr = new HashElement*[this->hashTableSize];
	for (int i = 0; i < this->hashTableSize; i++)
	{
		if (aTable.arr[i] != nullptr)
		{
			this->arr[i] = new HashElement(aTable.get(i));
		}
		else
		{
			this->arr[i] = nullptr;
		}
	}

	removed = new bool[hashTableSize];

}

template<typename HashElement>
inline HashTableLinear<HashElement>::~HashTableLinear()
{
	for (int i = 0; i < this->hashTableSize; ++i)
	{
		if (this->arr[i] != nullptr)
		{
			delete arr[i];
		}
	}
	delete[] arr;
	delete[] removed;
}

template<typename HashElement>
inline HashTableLinear<typename HashElement> & HashTableLinear<HashElement>::operator=(const HashTableLinear & aTable)
{
	if (this != &aTable)
	{
		for (int i = 0; i < this->hashTableSize; ++i)
		{
			delete arr[i];
		}
		delete[] arr;
		delete[] removed;

		this->nrOfCollisions = aTable.nrOfCollisions;
		this->hashTableSize = aTable.hashTableSize;
		this->arr = new HashElement*[this->hashTableSize];
		for (int i = 0; i < this->hashTableSize; i++)
		{
			if (aTable.arr[i] != nullptr)
			{
				this->arr[i] = new HashElement(aTable.get(i));
			}
			else
			{
				arr[i] = nullptr;
			}
		}

		removed = new bool[aTable.hashTableSize];
		for (int i = 0; i < aTable.hashTableSize; ++i)
		{
			this->removed[i] = aTable.removed[i];
		}

	}
	return *this;
}

template<typename HashElement>
inline int HashTableLinear<HashElement>::contains(const HashElement & elem) const
{
	int hashPos = myHash(elem);
	bool conntinue = true;
	int retVal = -1;

	int max = (hashPos - 1) % this->hashTableSize;
	if (max < 0)
	{
		max = this->hashTableSize - 1;
	}

	for (int i = hashPos; i != max && conntinue; i = (i + 1) % this->hashTableSize)
	{
		if (this->arr[i] != nullptr && this->get(i) == elem)
		{
			retVal = hashPos;
			conntinue = false;
		}
		else if(this->arr[i] == nullptr && !this->removed[i])
		{
			conntinue = false;
		}
	}
	if (!retVal && conntinue)
	{
		if (this->arr[max] != nullptr && this->get(max) == elem)
		{
			retVal = max;
		}
	}
	
	
	return retVal;
}

template<typename HashElement>
inline bool HashTableLinear<HashElement>::insert(const HashElement & elem)
{
	bool retVal = false;
	int pos = myHash(elem);
	int max = (pos - 1) % this->hashTableSize;
	if (max < 0)
	{
		max = this->hashTableSize - 1;
	}
	for (int i = pos; i != max && !retVal; i = (i + 1) % this->hashTableSize)
	{
		if (arr[i] == nullptr && !retVal)
		{
			if (pos != i)
			{
				this->nrOfCollisions++;
			}
			arr[i] = new HashElement(elem);
			this->nrElements++;
			retVal = true;
		}
	}
	if (!retVal)
	{
		if (arr[max] == nullptr)
		{
			if (pos != max)
			{
				this->nrOfCollisions++;
			}
			arr[max] = new HashElement(elem);
			this->nrElements++;
			
			retVal = true;
		}
	}
	
	return retVal;
}

template<typename HashElement>
inline bool HashTableLinear<HashElement>::remove(const HashElement & elem)
{
	bool retVal = false;
	int pos = myHash(elem);
	int samePos = pos;
	for (int i = pos; i != (pos - 1) % this->hashTableSize; i = (i + 1) % this->hashTableSize)
	{
		if (arr[i] != nullptr && this->get(i) == elem)
		{
			if (pos != samePos)
			{
				this->nrOfCollisions--;
			}
			delete arr[i];
			arr[i] = nullptr;
			retVal = true;
			i = (pos - 2) % this->hashTableSize;

			this->removed[i] = true;
		}
	}
	return retVal;
}

template<typename HashElement>
inline HashElement & HashTableLinear<HashElement>::get(int index) const
{

	return arr[index][0];
}

template<typename HashElement>
inline void HashTableLinear<HashElement>::makeEmpty()
{
	this->nrElements = 0;
	for (int i = 0; i < this->hashTableSize; ++i)
	{

		if (arr[i] != nullptr)
		{
			delete arr[i];
		}
		
		arr[i] = nullptr;

	}
	this->nrOfCollisions = 0;
	for (int i = 0; i < this->hashTableSize; ++i)
	{
		this->removed[i] = false;
	}
}

template<typename HashElement>
inline double HashTableLinear<HashElement>::loadFactor() const
{

	return double(this->nrElements)/this->hashTableSize;
}

template<typename HashElement>
inline int HashTableLinear<HashElement>::getNrOfElements() const
{
	return nrElements;
}

template<typename HashElement>
inline int HashTableLinear<HashElement>::getNrOfCollisions() const
{
	return this->nrOfCollisions;
}

template<typename HashElement>
inline void HashTableLinear<HashElement>::resetNrOfCollisions()
{
	this->nrOfCollisions = 0;
}
