#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <math.h>

using namespace std;

unsigned int hashFunc1(const string &name, int tableSize);
unsigned int hashFunc2(const string &name, int tableSize);

int is_prime(int num);
int next_pr(int num);
bool probe(string hashTable[], int tableSize, int key, string line, int frequencyTable[]);

void printHashTable(string hashTable[], int tableSize);

int getCollision(int table[], int tableSize);

void printFreq(int table[], int tableSize);

int main()
{

	ifstream in("IndexingKeys.txt");

	if (!in)
		cout << "ERROR: file could not be read!" << endl;

	string line;
	int numStudents = 0;
	while (getline(in, line))
	{
		numStudents++;
	}
	in.clear();
	in.seekg(0); //reset input parser

	cout << "Number of Elements: " << numStudents << endl;

	int idealSize = (3 * numStudents);  //ensure there is enough room in the hashTable
	int tableSize = next_pr(idealSize); //ensure size is a prime number, useful for hashing

	cout << "table size: " << tableSize << endl
		 << endl;

	//create hash table array
	//instead of creating a hashtable of objects, we will create a hashtable of strings to illustrate the functionality of our hashing
	string *hashTable = new string[tableSize];
	int numCollisions = 0;

	int *frequencyTable = new int[tableSize];

	while (getline(in, line)) //retrive next key, and send it to the hash function to calculate an index
	{
		cout << line << endl;

		//int key = hashFunc1(line, tableSize);
		int key = hashFunc3(line, tableSize);

		frequencyTable[key]++;
		if (hashTable[key] == "")
		{ //insert into table if no collision

			hashTable[key] = line;
		}
		else
		{

			//there is a collision
			//we must probe
			//numCollisions++;
			cout << "Collision Detected! PROBING.." << endl;
			probe(hashTable, tableSize, key, line, frequencyTable);
		}
	}

	numCollisions = getCollision(frequencyTable, tableSize);

	double rate;
	printHashTable(hashTable, tableSize);
	printFreq(frequencyTable, tableSize);
	cout << "\n\nSUMMARY\n";
	cout << "Number of collisions: " << numCollisions << endl;

	in.close();
	delete[] hashTable;
	delete[] frequencyTable;

	return 0;
}

//In this hash function we are adding up all the ascii values in the first
//and last name to get a sum, then modulo with the table size to get our indexing key
unsigned int hashFunc1(const string &name, int tableSize)
{

	unsigned int key = 0;
	unsigned int asciiValue;
	unsigned int sum;

	for (int i = 0; i < name.length(); i++)
	{
		//add up ascii values in string
		if (name[i] != ' ' && name[i] != 13)
		{
			asciiValue = name[i];
			sum += asciiValue;
		}
	}

	key = sum % tableSize;
	cout << "Indexing key: " << key << endl
		 << endl;

	return key;
}

unsigned int hashFunc2(const string &name, int tableSize)
{

	unsigned int key = 0;
	//unsigned int asciiValue =0;
	//unsigned int sum;
	int index = 1;

	unsigned int hash = 0;
	for (int i = 0; i < name.length(); i++)
	{

		if (name[i] != ' ' && name[i] != 13)
		{
			hash = ((hash * 33 + name[i]));
		}
	}

	key = hash % tableSize;
	cout << "hash" << hash << endl;
	cout << "Indexing key: " << key << endl
		 << endl;

	return key;
}



int getCollision(int table[], int tableSize)
{

	int c = 0;
	int sum = 0;
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] > 1)
		{
			c = table[i] - 1;
			sum += c;
		}
	}

	return sum;
}

int next_pr(int num)
{
	int c;
	if (num < 2)
		c = 2;
	else if (num == 2)
		c = 3;
	else if (num & 1)
	{
		num += 2;
		c = is_prime(num) ? num : next_pr(num);
	}
	else
		c = next_pr(num - 1);

	return c;
}

int is_prime(int num)
{
	if ((num & 1) == 0)
		return num == 2;
	else
	{
		int i, limit = sqrt(num);
		for (i = 3; i <= limit; i += 2)
		{
			if (num % i == 0)
				return 0;
		}
	}
	return 1;
}

void printHashTable(string HashTable[], int tableSize)
{

	cout << "***Printing Hash Table:\n";
	for (int i = 0; i < tableSize; i++)
	{
		cout << i << " : ";
		cout << HashTable[i] << endl;
	}
}

void printFreq(int table[], int tableSize)
{
	cout << "***Printing frequency Table:\n";
	for (int i = 0; i < tableSize; i++)
	{

		if (table[i] != 0)
		{

			cout << i << "   :   ";

			cout << table[i] << endl;
		}
	}
}

//performs quadratic probing
//probe the hash table until item is inserted successfully
//returns true if successful, false if unable to probe
bool probe(string hashTable[], int tableSize, int key, string line, int frequencyTable[])
{

	bool inserted = false;
	int i = 1;
	int index = key;

	while (inserted == false)
	{

		frequencyTable[key]++;
		if (hashTable[index] != "")
		{ //there is a collision
			
			index = (index + i ^ 2) % tableSize;

		}
		else
		{ //there was no collision, we can now insert into index

			inserted = true;
			hashTable[index] = line;
			cout << line << endl;
			cout << "New Indexing key: " << index << endl
				 << endl;

			return true;
		}

		i++;
	}
}

