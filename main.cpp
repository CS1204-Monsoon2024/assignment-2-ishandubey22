#include "HashTable.cpp"
#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int capacity;
    int *table;
    int elementCount;
    float loadFactor;

public:
    HashTable(int size)
    {
        capacity = size;
        table = new int[capacity];
        loadFactor = 0.8;
        elementCount = 0;

        for (int i = 0; i < capacity; i++)
        {
            table[i] = -1;
        }
    }

    int nextPrime(int currentCapacity)
    {
        int candidate = currentCapacity * 2;
        while (!isPrime(candidate))
        {
            candidate++;
        }
        return candidate;
    }

    bool isPrime(int number)
    {
        int divisorCount = 0;
        for (int i = 1; i <= number; i++)
        {
            if (number % i == 0)
            {
                divisorCount++;
            }
        }
        return divisorCount == 2;
    }

    void rehash()
    {
        int newSize = nextPrime(capacity);
        int *newTable = new int[newSize];

        for (int i = 0; i < newSize; i++)
        {
            newTable[i] = -1;
        }

        for (int i = 0; i < capacity; i++)
        {
            if (table[i] != -1)
            {
                int val = table[i];
                int pos = val % newSize;

                int j = 0;
                while (newTable[(pos + j * j) % newSize] != -1 && j <= ((newSize + 1) / 2))
                {
                    j++;
                }
                int finalPos = (pos + j * j) % newSize;
                if (newTable[finalPos] == -1)
                    newTable[finalPos] = val;
                else
                    cout << "Probing limit exceeded!" << endl;
            }
        }

        delete[] table;
        table = newTable;
        capacity = newSize;
    }

    void insert(int val)
    {
        float currentLoadFactor = elementCount / (float)capacity;
        if (currentLoadFactor >= loadFactor)
        {
            rehash();
        }

        int idx = val % capacity;
        int i = 0;
        while (table[(idx + i * i) % capacity] != -1 && i <= ((capacity + 1) / 2))
        {
            if (table[(idx + i * i) % capacity] == val)
            {
                cout << "No duplicate keys allowed" << endl;
                return;
            }
            i++;
        }
        int finalIdx = (idx + i * i) % capacity;
        if (table[finalIdx] == -1)
        {
            table[finalIdx] = val;
            elementCount++;
        }
        else
        {
            cout << "Probing limit exceeded!" << endl;
            return;
        }
    }

    int find(int val)
    {
        int idx = val % capacity;
        int i = 0;

        while (table[(idx + i * i) % capacity] != val && i <= ((capacity + 1) / 2))
        {
            if (table[(idx + i * i) % capacity] == -1)
            {
                return -1;
            }
            i++;
        }
        if (table[(idx + i * i) % capacity] == val)
            return (idx + i * i) % capacity;
        else
            return -1;
    }

    void erase(int val)
    {
        int position = find(val);
        if (position != -1)
        {
            table[position] = -1;
            elementCount--;
        }
        else
            cout << "Value not found" << endl;
    }

    void displayTable()
    {
        for (int i = 0; i < capacity; i++) 
        {
            if (table[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
