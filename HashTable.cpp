#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int S;
    int *arr1;
    int input;
    float alpha;       //alpha is load factor

public:
    HashTable(int x)
    {
        S = x;
        arr1 = new int[S];
        alpha = 0.8;
        input = 0;
        

        for (int i = 0; i < S; i++)
        {
            arr1[i] = -1;
        }
    }


    int resize(int S_current)    
        int no = S_current * 2;
        while (Check_prime(no) != true)
        {
            no += 1;
        }
        return no;
    }
    
    bool Check_prime(int no)      
    {
        int c = 0;      
        for (int i = 1; i <= no; i++)
        {
            if (no % i == 0)
            {
                c += 1;
            }
        }
        return c == 2;
    }

    void Resizing()
    {
        int newsz = resize(S);       
        int *arr2 = new int[newsz];

        for (int i = 0; i < newsz; i++)
        {
            arr2[i] = -1;
        }

        for (int i = 0; i < S; i++)
        {
            if (arr1[i] != -1)
            {
                int key = arr1[i];
                int index = key % newsz;

                int j = 0;
                while (arr2[(index + j * j) % newsz] != -1 && j <= ((newsz + 1) / 2))
                {
                    j += 1;
                }
                int pos = (index + j * j) % newsz;
                if (arr2[pos] == -1)
                    arr2[pos] = key;
                else
                    cout << "Max probing limit reached!" << endl;
            }
        }

        delete[] arr1; 
        arr1 = arr2;
        S = newsz;
    }

    void insert(int key)
    {
        float new_alpha = input / (float)S; 
        if (new_alpha >= alpha)
        {
            Resizing();         
        }

        int index = key % S;
        int i = 0;
        while (arr1[(index + i * i) % S] != -1 && i <= ((S + 1) / 2))
        {
            if (arr1[(index + i * i) % S] == key)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i += 1;
        }
        int pos = (index + i * i) % S;
        if (arr1[pos] == -1)
            {arr1[pos] = key;
            input += 1;}
        else
        {
            cout << "Max probing limit reached!" << endl;
            return;
        }
    }


    int search(int key)            
    {
        int index = key % S;
        int i = 0;

        while (arr1[(index + i * i) % S] != key && i <= ((S + 1) / 2))
        {
            if (arr1[(index + i * i) % S] == -1)
            {
                return -1;
            }
            i++;
        }
        if (arr1[(index + i * i) % S] == key)
            return (index + i * i) % S;
        else
            return -1;
    }
    
    void remove(int key)
    {
        int x = search(key);        
        if (x != -1)
        {
            arr1[x] = -1;
            input--;
        }
        else
            cout << "Element not found" << endl;
    }

    void printTable()
    {
        for (int i = 0; i < S; i++) 
        {
            if (arr1[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << arr1[i] << " ";
            }
        }
        cout << endl;
    }
};
