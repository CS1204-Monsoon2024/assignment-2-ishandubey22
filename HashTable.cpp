#include <iostream>
#include <cmath>
using namespace std;

class CustomHashTable
{
    int capacity;
    int *hashArray;
    int numElements;
    float loadFactor; // Load factor for resizing

public:
    // Constructor for the hash table
    CustomHashTable(int initialSize)
    {
        capacity = initialSize;
        hashArray = new int[capacity];
        loadFactor = 0.8;
        numElements = 0;

        // Set all slots as empty initially
        for (int i = 0; i < capacity; i++)
        {
            hashArray[i] = -1;
        }
    }

    // Resize function to find the next prime number at least twice the current size
    int getNextPrime(int currentSize)
    {
        int nextSize = currentSize * 2;
        while (!isPrime(nextSize))
        {
            nextSize += 1;
        }
        return nextSize;
    }

    // Helper function to check if a number is prime
    bool isPrime(int num)
    {
        if (num <= 1)
            return false;
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    // Function to resize the hash table when load factor threshold is exceeded
    void resizeTable()
    {
        int newCapacity = getNextPrime(capacity); // New capacity after resizing
        int *newArray = new int[newCapacity];

        // Initialize the new array
        for (int i = 0; i < newCapacity; i++)
        {
            newArray[i] = -1;
        }

        // Rehash the elements into the new table
        for (int i = 0; i < capacity; i++)
        {
            if (hashArray[i] != -1)
            {
                int value = hashArray[i];
                int newIndex = value % newCapacity;

                // Apply quadratic probing to find the next available slot
                int offset = 0;
                while (newArray[(newIndex + offset * offset) % newCapacity] != -1 && offset <= ((newCapacity + 1) / 2))
                {
                    offset += 1;
                }
                int finalPos = (newIndex + offset * offset) % newCapacity;
                if (newArray[finalPos] == -1)
                    newArray[finalPos] = value;
                else
                    cout << "Max probing limit reached!" << endl;
            }
        }

        delete[] hashArray; // Free the old memory
        hashArray = newArray;
        capacity = newCapacity;
    }

    // Insert function to add elements to the hash table
    void insertKey(int value)
    {
        float currentLoadFactor = numElements / (float)capacity; // Compute current load factor
        if (currentLoadFactor >= loadFactor)
        {
            resizeTable(); // Trigger resizing if load factor exceeds the threshold
        }

        int startIndex = value % capacity;
        int offset = 0;

        // Use quadratic probing to resolve collisions
        while (hashArray[(startIndex + offset * offset) % capacity] != -1 && offset <= ((capacity + 1) / 2))
        {
            if (hashArray[(startIndex + offset * offset) % capacity] == value)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            offset += 1;
        }

        int finalIndex = (startIndex + offset * offset) % capacity;
        if (hashArray[finalIndex] == -1)
        {
            hashArray[finalIndex] = value;
            numElements += 1;
        }
        else
        {
            cout << "Max probing limit reached!" << endl;
        }
    }

    // Search for an element in the hash table
    int searchKey(int value)
    {
        int startIndex = value % capacity;
        int offset = 0;

        // Apply quadratic probing while searching for the key
        while (hashArray[(startIndex + offset * offset) % capacity] != value && offset <= ((capacity + 1) / 2))
        {
            if (hashArray[(startIndex + offset * offset) % capacity] == -1)
            {
                return -1; // Element not found
            }
            offset++;
        }

        if (hashArray[(startIndex + offset * offset) % capacity] == value)
            return (startIndex + offset * offset) % capacity;
        else
            return -1; // Element not found
    }

    // Function to remove an element from the hash table
    void deleteKey(int value)
    {
        int position = searchKey(value); // Search for the element
        if (position != -1)
        {
            hashArray[position] = -1; // Mark the position as empty
            numElements--;
        }
        else
        {
            cout << "Element not found" << endl;
        }
    }

    // Print the contents of the hash table
    void printHashTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (hashArray[i] == -1)
            {
                cout << "- "; // Empty slot
            }
            else
            {
                cout << hashArray[i] << " "; // Occupied slot
            }
        }
        cout << endl;
    }

    // Destructor to release dynamically allocated memory
    ~CustomHashTable()
    {
        delete[] hashArray;
    }
}; // End of class definition

int main()
{
    CustomHashTable ht(7); // Create hash table with initial size 7

    ht.insertKey(10);
    ht.insertKey(20);
    ht.insertKey(30);
    ht.insertKey(25);
    ht.insertKey(35);

    cout << "Hash Table contents after insertion: ";
    ht.printHashTable();

    ht.deleteKey(25);
    cout << "Hash Table contents after removing 25: ";
    ht.printHashTable();

    return 0;
}
