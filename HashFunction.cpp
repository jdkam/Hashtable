#include <iostream>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

int hashFunc1(string name, int tableSize);
int is_prime(int num);
int next_pr(int num);

int main() {

	ifstream in("IndexingKeys.txt");

	if (in) {
		cout << "file read successfully!" << endl;
	}
	else
		cout << "ERROR: file could not be read!" << endl;

	string line;
	int numStudents=0;
	while (getline(in, line))
	{
		numStudents++;
	}
	in.clear();
	in.seekg(0); //reset input parser

	cout << numStudents << endl;

	int idealSize = (2 * numStudents);
	int tableSize = next_pr(26); //ensure size is a prime number, useful for hashing

	cout << "table size: " << tableSize << endl;



	//create hash table array
	 int *hashTable = new int[tableSize];

	while (getline(in, line))
	{
		cout << line << endl;
		int key = hashFunc1(line, tableSize);
		
	}




	in.close();

	return 0;
}

int hashFunc1(string name, int tableSize) {

	int key = 0;
	int asciiValue;
	int sum;

	for (int i = 0; i < name.length(); i++) {
		//add up ascii values in string
		if (name[i] != ' ') {
			asciiValue = name[i];
			cout << "key: " << name[i] << " : ";
			cout << asciiValue << endl;
		}
	}

	return key;
}

int next_pr(int num) {
	int c;
	if (num < 2)
		c = 2;
	else if (num == 2)
		c = 3;
	else if (num & 1) {
		num += 2;
		c = is_prime(num) ? num : next_pr(num);
	}
	else
		c = next_pr(num - 1);

	return c;
}

int is_prime(int num) {
	if ((num & 1) == 0)
		return num == 2;
	else {
		int i, limit = sqrt(num);
		for (i = 3; i <= limit; i += 2) {
			if (num % i == 0)
				return 0;
		}
	}
	return 1;
}