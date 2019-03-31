#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <math.h>

using namespace std;

int hashFunc1(string name, int tableSize);
int is_prime(int num);
int next_pr(int num);
bool probe(string hashTable[], int tableSize, int key, string line);

void printHashTable(string hashTable[], int tableSize);

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

	int idealSize = (2 * numStudents); //ensure there is enough room in the hashTable
	int tableSize = next_pr(26);	   //ensure size is a prime number, useful for hashing

	cout << "table size: " << tableSize << endl
		 << endl;

	//create hash table array
	//instead of creating a hashtable of objects, we will create a hashtable of strings to illustrate the functionality of our hashing
	string *hashTable = new string[tableSize];

	//retrive next key, and send it to the hash function to calculate an index
	while (getline(in, line))
	{
		//cout << line << endl;
		int key = hashFunc1(line, tableSize);
		
		//check for collisions
		if(hashTable[key] == ""){
			//insert into table if no collision
			hashTable[key] = line;
		}else{
			//there is a collision
			//we must probe
		}
		
	}

	printHashTable(hashTable, tableSize);

	in.close();

	return 0;
}

//In this hash function we are adding up all the ascii values in the first
//and last name to get a sum, then modulo with the table size to get our indexing key
int hashFunc1(string name, int tableSize)
{

	int key = 0;
	int asciiValue;
	int sum;

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
	//cout << "Indexing key: " << key << endl << endl;

	return key;
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

void printHashTable(string HashTable[], int tableSize){

	cout << "***Printing Hash Table:\n";
	for(int i =0; i<tableSize; i++){
		cout << i << " : ";
		cout << HashTable[i] << endl;
	}

}

//performs quadratic probing
//probe the hash table until item is inserted successfully
//returns true if successful, false if unable to probe
bool probe(string hashTable[], int tableSize, int key, string line){

	bool inserted = false;
	int i = 1;
	int index = key;

	while(!inserted){

		if(hashTable[index] != ""){ //there is a collision
			index = (index + i^2) % tableSize;
		}
		else{ //there was no collision, we can now insert into index
			inserted = true;
			hashTable[index] = line;
			break;
		}

		i++;

	}

}