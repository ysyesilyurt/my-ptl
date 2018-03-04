#ifndef _PTL_HASHTABLE_HPP_
#define _PTL_HASHTABLE_HPP_

#define EMPTY_INDEX (-1)
#define MARKED_INDEX (-99)
#define EMPTY_KEY ""
#define MAX_LOAD_FACTOR 0.65

#include <iostream>
#include <string>
#include <vector>

namespace ptl {
	class HashTable {

	private:

		std::pair<std::string, int> *table;
		int n; // Current number of the existing entries in hash table
		int table_size;
		int h1_param;
		int h2_param;

		void expand_table();
		int hash_function(std::string &key, int i) const;
		int h1(int key) const;
		int h2(int key) const;
		int convertStrToInt(const std::string &key) const;
		bool isPrime(int n) const;
		int nextPrimeAfter(int n) const;
		int firstPrimeBefore(int n) const;

	public:

		HashTable(int table_size, int h1_param, int h2_param);
		~HashTable();

		int get(std::string key, int nth, std::vector<int> &path) const;
		int insert(std::string key, int original_index);
		int remove(std::string key, int nth);
		double getLoadFactor() const;
		void printTable() const;
	};

	HashTable::HashTable(int table_size, int h1_param, int h2_param) {
		n = 0;
		HashTable::table_size = table_size;
		HashTable::h1_param = h1_param;
		HashTable::h2_param = h2_param;
		table = new std::pair<std::string, int>[table_size];
		for (int i = 0; i < table_size; ++i) {
			table[i] = std::make_pair(EMPTY_KEY, EMPTY_INDEX);
		}
	}

	HashTable::~HashTable() {
		table_size = 0;
		n = 0;
		h1_param = 0;
		h2_param = 0;
		delete[] table;
	}

	int HashTable::get(std::string key, int nth, std::vector<int> &path) const {
		int occurence = 0, flag = 0, i = 0;
		while (true) {
			int hash = hash_function(key, i);

			if (flag)//check for first cell
				path.push_back(hash);

			if (table[hash].first == key) {
				occurence++;
				if (occurence == nth)
					return table[hash].second;
				i++;
				flag = 1;
			}

			else if (table[hash].second == EMPTY_INDEX)
				return -1;

			else if (i >= table_size - 1)
				return -1;

			else {
				i++;
				flag = 1;
			}
		}
	}

	int HashTable::insert(std::string key, int original_index) {
		if (getLoadFactor() > MAX_LOAD_FACTOR)
			expand_table();

		int countofProbing = 0, flag = 0, i = 0;
		while (true) {
			int hash = hash_function(key, i);

			if (flag != 0)//check for first cell
				countofProbing++;

			if (table[hash].first == EMPTY_KEY) {
				table[hash] = std::make_pair(key, original_index);
				n++;
				break;
			}

			else if (table[hash].first == key) {
				if (original_index < table[hash].second) {
					int neworgi_index = table[hash].second;
					table[hash].second = original_index;
					original_index = neworgi_index;
				}
			}
			i++;
			flag = 1;
		}
		return countofProbing;
	}

	int HashTable::remove(std::string key, int nth) {
		int occurence = 0, i = 0;
		while (true) {
			int hash = hash_function(key, i);

			if (table[hash].first == key) {
				occurence++;
				if (occurence == nth) {
					table[hash] = std::make_pair(EMPTY_KEY, MARKED_INDEX);
					n--;
					return i;
				}
			}

			else if (table[hash].second == EMPTY_INDEX)
				return -1;

			else if (i >= table_size - 1)
				return -1;

			i++;
		}
	}

	double HashTable::getLoadFactor() const {
		return (double) n / table_size;
	}	

	void HashTable::expand_table() {
		int oldtablesize = table_size;
		table_size = nextPrimeAfter(2 * table_size);
		h2_param = firstPrimeBefore(table_size);
		std::pair<std::string, int> *oldtable = table;
		table = new std::pair<std::string, int>[table_size];
		n = 0;
		for (int i = 0; i < table_size; ++i) {
			table[i] = std::make_pair(EMPTY_KEY, EMPTY_INDEX);
		}
		for (int i = 0; i < oldtablesize; ++i) {
			if (oldtable[i].second != EMPTY_INDEX) {
				insert(oldtable[i].first, oldtable[i].second);
			}
		}

		delete[] oldtable;
	}

	int HashTable::hash_function(std::string &key, int i) const {
		int convertedKey = convertStrToInt(key);
		return (h1(convertedKey) + i * h2(convertedKey)) % table_size;
	}

	int HashTable::h1(int key) const {
		int popcount = 0;
		while (key != 0) {
			if (key % 2) {
				popcount++;
				key /= 2;
			} else
				key /= 2;
		}
		int res = h1_param * popcount;
		return res;
	}

	int HashTable::h2(int key) const {
		int modofKey = key % h2_param;
		int res = h2_param - modofKey;
		return res;
	}

	// Checks if integer n is prime or not
	bool HashTable::isPrime( int n ) const
	{
		if( n%2 == 0 ) return false;
		for( int i=3; i*i<=n; i+=2 )
			if( n%i == 0 )
				return false;
		return true;
	}
	// Finds the first prime number just after integer n
	int HashTable::nextPrimeAfter( int n ) const
	{
		for( int i=n+1; ; i++ )
			if( isPrime(i) )
				return i;
	}

	// Finds the first prime number just before integer n
	int HashTable::firstPrimeBefore (int n) const
	{
		for( int i=n-1; ; i-- )
			if( isPrime(i) )
				return i;
	}

	// Converts given string to an integer that	is used in hashing functions
	int HashTable::convertStrToInt( const std::string &key ) const
	{
		int tableIndex = 0, convertedKey = 0;
		int length = key.length();

		int r=length-1,l=0;
		int m = (l+r)/2;
		convertedKey += ( ((0xfe)/26)*(((unsigned int)key[l])-'a') + 1 );
		convertedKey += ( ((0xfe)/26)*(((unsigned int)key[r])-'a') + 1 )*37;
		convertedKey += ( ((0xfe)/26)*(((unsigned int)key[m])-'a') + 1 )*37*37;

		return convertedKey;
	}

	// Prints hash table data in a table shaped format
	void HashTable::printTable() const
	{
		int nameMaxLength = 0, temp = 0;
		int maxIndex = 0, maxIndexLength = 0;
		int blankDiff = 0, indexLength = 0;

		for (int i = 0; i < table_size; i++)
		{
			if (table[i].first.length() > nameMaxLength)
				nameMaxLength = table[i].first.length();
			if (table[i].second > maxIndex)
				maxIndex = table[i].second;
		}
		if (maxIndex <= 0)
		{
			nameMaxLength = 5;
			maxIndex = 999;
		}
		temp = maxIndex;
		while (temp != 0)
		{
			temp /= 10;
			maxIndexLength++;
		}
		std::cout << "|";
		for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
			std::cout << "-";
		if (maxIndexLength < 2)
			std::cout << "-";
		std::cout << "|" << std::endl;

		std::cout << "| ";
		for (int i = 0; i < (nameMaxLength - 1)/2; ++i)
			std::cout << " ";
		std::cout << "K";
		for (int i = 0; i < (nameMaxLength - 1)/2; ++i)
			std::cout << " ";
		if ((nameMaxLength - 1) %2 != 0)
			std::cout << " ";
		std::cout << " | ";
		for (int i = 0; i < (maxIndexLength - 1)/2; ++i)
			std::cout << " ";
		if ((maxIndexLength - 1) % 2 != 0)
			std::cout << " ";
		std::cout << "I";
		if (maxIndexLength < 2)
			std::cout << " ";
		for (int i = 0; i < (maxIndexLength - 1)/2; ++i)
			std::cout << " ";
		std::cout << " |" << std::endl;

		std::cout << "|";
		for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
			std::cout << "-";
		if (maxIndexLength < 2)
			std::cout << "-";
		std::cout << "|" << std::endl;

		for (int i = 0; i < table_size; i++)
		{
			indexLength = 0;
			blankDiff = nameMaxLength - table[i].first.length();

			std::cout << "|";

			for (int j = 0; j < (blankDiff/2) + 1; j++)
				std::cout << " ";
			std::cout << table[i].first;
			for (int j = 0; j < (blankDiff/2) + 1; j++)
				std::cout << " ";
			if (blankDiff % 2 != 0)
				std::cout << " ";
			std::cout << "|";

			temp = table[i].second;
			while(temp != 0)
			{
				temp /= 10;
				indexLength++;
			}
			blankDiff = maxIndexLength - indexLength;

			for (int j = 0; j < (blankDiff/2) + 1; j++)
				std::cout << " ";
			std::cout << table[i].second;
			for (int j = 0; j < blankDiff/2; j++)
				std::cout << " ";
			if (table[i].second > 0)
				std::cout << " ";
			if (table[i].second == -1 && (maxIndexLength % 2 != 0 && maxIndexLength < 2))
				std::cout << " ";
			else if (table[i].second == -1 && maxIndexLength % 2 == 0)
				std::cout << " ";
			if (blankDiff % 2 != 0 && table[i].second > 0)
				std::cout << " ";
			if (table[i].second > 0 && maxIndexLength < 2)
				std::cout << " ";
			if (table[i].second == -99 && (maxIndexLength % 2 != 0 && maxIndexLength > 1))
				std::cout << " ";
			std::cout << "|" << std::endl;

			std::cout << "|";
			for (int i = 0; i < nameMaxLength + maxIndexLength + 5; ++i)
				std::cout << "-";
			if (maxIndexLength < 2)
				std::cout << "-";
			std::cout << "|" << std::endl;
		}
	}
}

#endif /* _PTL_HASHTABLE_HPP_ */
