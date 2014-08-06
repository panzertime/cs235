#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;

template <typename obj>

class hashSet {
	
	public:

	LinkedList<obj>* table;
	//	LinkedList <obj>* and LinkedList <obj>[]
	//	are the same.  Thanks, Unix!
	int tableSize;
	int size;

	hashSet<obj>(){
		tableSize = 0;
		size = 0;
		table = new LinkedList<obj>[tableSize];
	}

/*    meh probably not
	hashSet<obj>(int big){
		tableSize = big;
		size = 0;
		table = new LinkedList<obj>[tableSize];
	}
*/
		/*
		 *	What we end up with is an array of LL's,
		 *	each of which is a bucket.
		 *	Adding / removing affect size, rehashing
		 *	affects tableSize.
		 */

	virtual ~hashSet<obj>() {
		delete[] table;
		}

	void print(ofstream & out) {
		/*
		 *	for each bucket, generate some lists and
		 *	print in eights.  The newline makes this
		 *	slightly less than trivial.
		 *
		 *	Basically, for each bucket,
		 *	then do like position % 8 to stick newlines in
		 */

		 for (int bucket = 0; bucket < tableSize; bucket++) {
		 	for (int at = 0; at < table[bucket].size; at++) {
				if (at % 8 == 0)
					out << endl << "hash " << bucket << ": ";
				out << table[bucket].get(at);
			}
		}
	}

	void clear() {
		delete[] table;
		tableSize = 0;
		size = 0;
		table = new LinkedList<obj>[tableSize];
		// 	why not just delete and recreate the set?
	
	}



	void add(const obj& item) {
		/*	
		 *	Check first for dupes.
		 *	Check loading - rehash if needed.
		 *	Get a hash from the object, then append it 
		 *	to table[hash].
		 */

		if (!find(item)) {
			size++;
			if (size == tableSize)
				upHash();
			unsigned bucket = hashCode(item);
			table[bucket].append(item);
		}
	}

	void remove(const obj& item) {
		/*
		 *	Check for existence.
		 *	Get a hash, then:
		 *	find on the appropriate bucket
		 *	delete from that bucket using index
		 */

		 if(find(item)) {
		 	unsigned bucket = hashCode(item);
			int index = table[bucket].find(item);
			table[bucket].remove(index);
			size--;
			if (((double) size) > (((double) tableSize )* 0.5))
			downHash();	
		}
	}
	
	/*	Rehashing functions work by determining new size,
	 *	creating a new table,
	 *	scanning thru the old table and transferring
	 *	(the tableSize has already been reset in order
	 *	to guarantee a proper hash for the new table)
	 *	then deleting the old table and replacing it.
	 */

	/*	
	 *	Big issue here is actually my LinkedList class, which
	 *	has several limitations.  To begin with, the class
	 * 	was never meant to be used with any sort of iterator,
	 *	which is what I expect with all STL sequential
	 *	containers.  So either I need to add that functionality
	 *	to my LL, which will be more elegant, I guess, and
	 *	also have cooler-looking code, but be a huge pain in the
	 *	ass, as I'll have to basically redo my whole LL class.
	 *	Still an attractive challenge.
	 *	Or I could simply do as I *originally* planned in the
	 *	first place - "pop" from each bucket repeatedly
	 *	and add to the new table.
	 */

	 /*
	  *	lol pop() isn't happening since remove returns void!
	  *	so i can simply get the size of the LL, as it's public,
	  *	and then do a loop with get(index), which returns obj.
	  */
	
	void upHash() {
		int newSize = (size * 2) + 1;
		LinkedList<obj>* newTable = new LinkedList<obj>[newSize];
		int oldSize = tableSize;
		tableSize = newSize;
		for (int bucket = 0 ; bucket < oldSize; bucket++)
			for (int at = 0 ; at < table[bucket].size; at++)
				newTable[hashCode(table[bucket].get(at))].append(table[bucket].get(at));
		delete[] table;
		table = newTable;
	}

	void downHash() {
		int newSize = (size - 1) / 2;
		LinkedList<obj>* newTable = new LinkedList<obj>[newSize];
		int oldSize = tableSize;
		tableSize = newSize;
		for (int bucket = 0 ; bucket < oldSize; bucket++)
			for (int at = 0 ; at < table[bucket].size; at++)
				newTable[hashCode(table[bucket].get(at))].append(table[bucket].get(at));
		delete[] table;
		table = newTable;
	}

	bool find(const obj& item) {
		if (size != 0){
			unsigned bucket = hashCode(item);
			if (table[bucket].find(item) >= 0)
			return true;
		}
		//or fall thru to neg case:
		return false;

	}

	unsigned hashCode(const string & s){
		unsigned hashIndex = 0;
		for(auto c : s){
			hashIndex = hashIndex * 31;
			hashIndex = hashIndex + (unsigned) c;
		}
		return hashIndex % size;
	}


/******** WOAH THIS DOESN'T WORK

hashSet<obj> upHash(hashSet<obj> & old) {
	 *
	 *	make new set with appropriate size
	 *	for each bucket, traverse and delete,
	 *	add item to new set.  
	 *	Delete old set
	 *	Return new set
	 *
	int newSize = (old.size * 2) + 1;
	hashSet<obj> newSet = new hashSet<obj>(newSize);
	for (auto bucket : old)
		for (auto thing : bucket)
			newSet.add(thing);
	return newSet;
	
	}


hashSet<obj> downHash(hashSet<obj> & old) {
	 *
	 *	make new set with appropriate size
	 *	for each bucket, traverse and delete,
	 *	add item to new set.  
	 *	Delete old set
	 *	Return new set
	 *
	int newSize = (old.size - 1) / 2;
	hashSet<obj> newSet = new hashSet<obj>(newSize);
	for (auto bucket : old)
		for (auto thing : bucket)
			newSet.add(thing);
	return newSet;
	
	}

**********************************/

};
