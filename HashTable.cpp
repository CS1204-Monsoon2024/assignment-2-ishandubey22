#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int capacity;
    int *hashArray;
    int elementsCount;
    float loadFactor; 

public:
    HashTable(int initialSize)
    {
        capacity = initialSize;
        hashArray = new int[capacity];
        loadFactor = 0.8;
        elementsCount = 0;
        
        fill(hashArray, hashArray + capacity, -1); // Fill array with -1 using standard function
    }

    int nextPrime(int currentSize) 
    {
        int num = currentSize * 2;
        while (!isPrime(num))
        {
            num++;
        }
        return num;
    }
    
    bool isPrime(int num) 
    {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        
        for (int i = 5; i * i <= num; i += 6)
        {
            if (num % i == 0 || num % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    void resizeTable()
    {
        int newSize = nextPrime(capacity); 
        int *tempArray = new int[newSize];
        fill(tempArray, tempArray + newSize, -1); // Fill with -1

        for (int i = 0; i < capacity; i++)
        {
            if (hashArray[i] != -1)
            {
                int key = hashArray[i];
                int index = key % newSize;

                // Quadratic probing to resolve collisions
                int j = 0;
                while (tempArray[(index + j * j) % newSize] != -1 && j <= newSize / 2)
                {
                    j++;
                }
                int pos = (index + j * j) % newSize;
                if (tempArray[pos] == -1)
                    tempArray[pos] = key;
                else
                    cout << "Max probing limit reached!" << endl;
            }
        }

        delete[] hashArray; 
        hashArray = tempArray;
        capacity = newSize;
    }

    void insert(int key)
    {
        float currentLoad = (float)elementsCount / capacity; 
        if (currentLoad >= loadFactor)
        {
            resizeTable(); 
        }

        int index = key % capacity;
        int i = 0;
        while (hashArray[(index + i * i) % capacity] != -1 && i <= capacity / 2)
        {
            if (hashArray[(index + i * i) % capacity] == key)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i++;
        }
        int pos = (index + i * i) % capacity;
        if (hashArray[pos] == -1)
        {
            hashArray[pos] = key;
            elementsCount++;
        }
        else
        {
            cout << "Max probing limit reached!" << endl;
        }
    }

    int search(int key) 
    {
        int index = key % capacity;
        int i = 0;

        while (hashArray[(index + i * i) % capacity] != key && i <= capacity / 2)
        {
            if (hashArray[(index + i * i) % capacity] == -1)
            {
                return -1;
            }
            i++;
        }
        return hashArray[(index + i * i) % capacity] == key ? (index + i * i) % capacity : -1;
    }
    
    void remove(int key)
    {
        int loc = search(key); 
        if (loc != -1)
        {
            hashArray[loc] = -1;
            elementsCount--;
        }
        else
            cout << "Element not found" << endl;
    }

    void printTable()
    {
        for (int i = 0; i < capacity; i++) 
        {
            if (hashArray[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << hashArray[i] << " ";
            }
        }
        cout << endl;
    }
};
