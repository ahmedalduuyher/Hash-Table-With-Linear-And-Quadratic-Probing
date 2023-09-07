#include "HashTableLin.h"
using namespace std;
#include <iostream>

//Helper Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int HashTableLin::GetNextPrime(int n)
{
    for (int i = n; i < 2 * n; i++)
    {
        for (int j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                break;
            }
            else if (j == i / 2)
            {
                return i;
            }
            else
            {
                continue;
            }
        }
    }
    return 0;
}
//Time complexity of O(n^2), Space complexity of Theta(1)
int HashTableLin::HashFunction(int x)
{
    return x % HashTableSize;
}
//Time complexity of Theta(1), Space complexity of Theta(1)
//Helper Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HashTableLin::HashTableLin(int maxNum, double load)
{
    MaxNumberOfKeys = maxNum;
    MaxLoad = load;
    if (MaxNumberOfKeys / MaxLoad <= 2)
    {
        HashTableSize = 2;
        table.resize(HashTableSize, 0);
    }
    else if (MaxNumberOfKeys / MaxLoad < 3)
    {
        HashTableSize = 3;
        table.resize(HashTableSize, 0);
    }
    else
    {
        HashTableSize = (int)(MaxNumberOfKeys / MaxLoad) + 1;
        HashTableSize = GetNextPrime(HashTableSize);
        table.resize(HashTableSize, 0);
    }
}
//Time complexity of O(n^2), Space complexity of Theta(m)

void HashTableLin::insert(int n)
{
    int increment = HashFunction(n);
    NumberOfKeys++;
    float temp2 = 1;
    if (ActivateProbeCounting == true)
    {
        NumberOfProbes++;
    }
    while (table[increment] != 0)
    {
        if (table[increment] == n)
        {
            NumberOfKeys--;
            if (ActivateProbeCounting == true)
                NumberOfProbes = NumberOfProbes - temp2;
            return;
        }
        else if (increment == HashTableSize - 1)
        {
            if (ActivateProbeCounting == true)
            {
                NumberOfProbes++;
                temp2++;
            }
            increment = 0;
        }
        else
        {
            if (ActivateProbeCounting == true)
            {
                NumberOfProbes++;
                temp2++;
            }
            increment++;
        }
    }
    if ((((double)NumberOfKeys) / ((double)HashTableSize)) > MaxLoad && (ActivateProbeCounting == false))
    {
        rehash();
        int increment2 = HashFunction(n);
        while (table[increment2] != 0)
        {
            if (increment2 == HashTableSize - 1)
            {
                increment2 = 0;
            }
            else
            {
                increment2++;
            }
        }
        table[increment2] = n;
    }
    else
    {
        table[increment] = n;
    }
}
//Time complexity of O(n+n+n^2) = O(n^2), Space complexity of O(2n)

void HashTableLin::rehash()
{
    int temp1 = HashTableSize;
    HashTableSize = GetNextPrime(HashTableSize * 2);
    std::vector<int> temp(HashTableSize, 0);
    for (int i = 0; i < temp1; i++)
    {
        if (table[i] == 0)
            continue;
        else
        {
            int increment = HashFunction(table[i]);
            while (temp[increment] != 0)
            {
                if (increment == (HashTableSize - 1))
                    increment = 0;
                else
                    increment++;
            }
            temp[increment] = table[i];
        }
    }
    table = temp;
}
//Time complexity of O(n^2), Space complexity Theta(2n)

bool HashTableLin::isIn(int n)
{
    int increment = HashFunction(n);
    while (table[increment] != 0)
        if (table[increment] == n)
            return true;
        else if (increment == HashTableSize - 1)
        {
            increment = 0;
            continue;
        }
        else if (table[increment] == 0)
        {
            return false;
        }
        else
        {
            increment++;
            continue;
        }
    return false;
}
//Time complexity of Theta(n), Space complexity of Theta(1)

void HashTableLin::printKeys()
{
    // TODO
}

void HashTableLin::printKeysAndIndexes()
{
    // TODO
}

int HashTableLin::getNumKeys() {
    return NumberOfKeys;
}
//Time complexity Theta(1), space complexity theta(1)
int HashTableLin::getTableSize() {
    return HashTableSize;
}
//Time complexity Theta(1), space complexity theta(1)
double HashTableLin::getMaxLoadFactor() {
    return MaxLoad;
}
//Time complexity Theta(1), space complexity theta(1)
std::vector<double> HashTableLin::simProbeSuccess()
{
    int x = 0;
    float finalresult = 0;
    vector<double> result(9);
    for (float i = 0.1; i < 1; i += 0.1)
    {
        for (int k = 0; k < 100; k++)
        {
            HashTableLin HashTable(100000, i);
            for (int j = 0; j < 100000; j++)
            {
                HashTable.ActivateProbeCounting = true;
                HashTable.insert((rand() + 1) * (rand() + 1));
            }
            finalresult = finalresult + (HashTable.NumberOfProbes / ((float)HashTable.getNumKeys()));
            HashTable.NumberOfProbes = 0;
        }
        finalresult = finalresult / 100;
        result[x] = finalresult;
        finalresult = 0;
        x++;
    }
    return result;
}
//Time complexity O(10*n*1000n*n) which is approximately O(n^3), space complexity theta(10 + 1000n))

// for bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}