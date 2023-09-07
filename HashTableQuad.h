#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_

#include <vector>

class HashTableQuad
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
	HashTableQuad(int maxNum, double load);

	// required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

	//Other Helper functions
	int GetNextPrime(int n);
	int QuadProbing(int x, int y);

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */