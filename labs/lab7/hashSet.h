#include <string>
using namespace std;

template <typename ItemType>

class hashSet {


	set[];
	LinkedList <ItemType>* table;
	int tableSize;
	int size;


	void add(const ItemType& item) {



	}

	void remove(const ItemType& item) {



	}

	bool find(const ItemType& item) {

		return false;

	}

	unsigned hashCode(string & s){
		unsigned hashIndex = 0;
		for(auto c : s){
			hashIndex = hashIndex * 31;
			hashIndex = hashIndex + (unsigned) c;
		}
		return hashIndex % size;
	}


};
