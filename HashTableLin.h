#ifndef HASHTABLELIN_H_
#define HASHTABLELIN_H_

#include <vector>

class HashTableLin
{
private:
	// must contain this private field
	std::vector<int> table;
	int HashTableSize = 0;
	int MaxNumberOfKeys = 0;
	int NumberOfKeys = 0;
	double MaxLoad;
	// define other private fields to store:
	// 1. the size of the table
	// 2. the number of keys stored in the table
	// 3. the maximum load factor allowed

public:
	float NumberOfProbes = 0;
	bool ActivateProbeCounting = false;
	// required constructor
	HashTableLin(int maxNum, double load);

	// required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	static std::vector<double> simProbeUnsuccess(); // for bonus

	// used for testing
	std::vector<int> getTable() {
		return table;
	};
	//Helper functions
	int HashFunction(int x);
	int GetNextPrime(int n);
private:
	// required methods
	void rehash();
};

#endif /* HASHTABLELIN_H_ */
