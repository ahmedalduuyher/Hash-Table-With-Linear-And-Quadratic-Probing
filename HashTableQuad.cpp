#include "HashTableQuad.h"
#include <iostream>
using namespace std;

//Helper Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int HashTableQuad::GetNextPrime(int n)
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

int HashTableQuad::QuadProbing(int x, int y)
{
	return (x + (y * y)) % HashTableSize;
}
//Time complexity of Theta(1), Space complexity of Theta(1)
//Helper Functions ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

HashTableQuad::HashTableQuad(int maxNum, double load)
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

void HashTableQuad::insert(int n)
{
	int QuadraticProbing = 0;
	int increment = QuadProbing(n, QuadraticProbing);
	int temp3 = increment;
	int counter = 0;
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
		else if (increment == temp3 && counter != 0)
		{
			NumberOfKeys--;
			return;
		}
		else
		{
			if (ActivateProbeCounting == true)
			{
				NumberOfProbes++;
				temp2++;
			}
			counter++;
			QuadraticProbing++;
			increment = QuadProbing(n, QuadraticProbing);
		}
	}
	if ((((double)NumberOfKeys) / ((double)HashTableSize)) > MaxLoad && (ActivateProbeCounting == false))
	{
		rehash();
		int Quadratic2 = 0;
		int increment2 = QuadProbing(n, Quadratic2);
		while (table[increment2] != 0)
		{
			Quadratic2++;
			increment2 = QuadProbing(n, Quadratic2);
		}
		table[increment2] = n;
	}
	else
	{
		table[increment] = n;
	}
}
//Time complexity of O(n^2), Space complexity of O(2n)

void HashTableQuad::rehash()
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
			int QuadraticProbing = 0;
			int increment = QuadProbing(table[i], QuadraticProbing);
			while (temp[increment] != 0)
			{
				QuadraticProbing++;
				increment = QuadProbing(table[i], QuadraticProbing);
			}
			temp[increment] = table[i];
		}
	}
	table = temp;
}
//Time complexity of O(n^2), Space complexity Theta(2n)

bool HashTableQuad::isIn(int n)
{
	int QuadraticProbing = 0;
	int increment = QuadProbing(n, QuadraticProbing);
	while (table[increment] != 0)
	{
		if (table[increment] == n)
			return true;
		else if (table[increment] == 0)
		{
			return false;
		}
		else
		{
			QuadraticProbing++;
			increment = QuadProbing(n, QuadraticProbing);
			continue;
		}
	}
	return false;
}
//Time complexity of Theta(n), Space complexity of Theta(1)

void HashTableQuad::printKeys()
{
	// TODO
}

void HashTableQuad::printKeysAndIndexes()
{
	// TODO
}

int HashTableQuad::getNumKeys() {
	// TODO, change following code after completing this function
	return NumberOfKeys;
}
//Time complexity Theta(1), space complexity theta(1)

int HashTableQuad::getTableSize() {
	// TODO, change following code after completing this function
	return HashTableSize;
}
//Time complexity Theta(1), space complexity theta(1)

double HashTableQuad::getMaxLoadFactor() {
	// TODO, change following code after completing this function
	return MaxLoad;
}
//Time complexity Theta(1), space complexity theta(1)

std::vector<double> HashTableQuad::simProbeSuccess()
{
	vector<double> result(9);
	int x = 0;
	float finalresult = 0;
	for (float i = 0.1; i < 1; i += 0.1)
	{
		for (int k = 0; k < 100; k++)
		{
			HashTableQuad HashTable(100000, i);
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