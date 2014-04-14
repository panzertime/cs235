//
//  main.cpp
//  lab4
//
//  Created by Arthur Hatfield on 27/02-2014.
//  Copyright (c) 2014 Arthur Hatfield. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <list>
#include <set>
#include "Student.h"


// works FINE
void selectionSort(vector<Student> src){
    unsigned dim = src.size();
    
    for(unsigned i = 0; i < dim - 1; i++){
        unsigned min = i;
        for(unsigned j = i + 1; j < dim; j++){
            if (src[j] < src[min]){
                min = j;
            }
        }
        Student temp;
        temp = src[i];
        src[i] = src[min];
        src[min] = temp;
    }
}

void insertionSort(vector<Student> src){
    int dim = src.size();
    
    for(int i = 1; i < dim; i++){
        Student t = src[i];
        int j = i;
        while (j > 0 && t < src[j-1]) {
            src[j] = src[j - 1];
            j--;
        }
        src[j] = t;
    }
}

int linearSearch(const vector<Student>& src, Student targ){
    unsigned dim = src.size();

    for (unsigned i = 0 ; i < dim ; i++){
        if (src[i] == targ){
            return i;
        }
    }
    return -1;
}   // return < 0 means not found

vector<string> populateTemp(const char* file){
	vector<string> toPopulate;
	ifstream readIn;		//make all the things i need to populate my vectors
	string sget;
    
	readIn.open(file); 		//open student file
    
	while(getline(readIn, sget)){
		toPopulate.push_back(sget);	//making temp vector from which to populate student vector
	}
    
	readIn.close();				//close this file
	return toPopulate;
}

template <typename vex>
vex vquarter(vex& src) {
    vex out;
    for (unsigned i = 0 ; i <= ((src.size() - 1) / 4); i ++){
        out.push_back(src.at(i));
    }
    return out;
}

template <typename vex>
vex vhalf(vex& src) {
    vex out;
    for (unsigned i = 0 ; i <= ((src.size() - 1) / 2); i ++){
        out.push_back(src.at(i));
    }
    return out;
}

int selSort(vector <Student> & src){
	selectionSort(src);
	int c = Student::compared();
	Student::compareReset();
	return c;
}

int insSort(vector <Student> & src){
	Student::compareReset();
	insertionSort(src);
	int c = Student::compared();
	Student::compareReset();
	return c;
}

// 		works fine
void doSelSort(vector <Student> src, ofstream & tow){
	vector<Student> q = vquarter(src);
	vector<Student> h = vhalf(src);
    tow << "Selection Sort" << endl;
    tow << "size: " << q.size() << "   ";
    int c = selSort(q);
    tow << "compares: " << c << endl;

    tow << "size: " << h.size() << "   ";
    tow << "compares: " << selSort(h) << endl;

    tow << "size: " << src.size() << "   ";
    tow << "compares: " << selSort(src)  << endl;
}

void doInsertionSort(vector <Student> src, ofstream & tow){
    vector<Student> q = vquarter(src);
    vector<Student> h = vhalf(src);
    tow << "Insertion Sort" << endl;
    tow << "size: " << q.size() << "   ";
    tow << "compares: " << insSort(q) << endl;

    tow << "size: " << h.size() << "   ";
    tow << "compares: " << insSort(h) << endl;

    tow << "size: " << src.size() << "   ";
    tow << "compares: " << insSort(src) << endl;
}

void doLibrarySort(vector <Student> src, ofstream & tow){
    vector<Student> q = vquarter(src);
    vector<Student> h = vhalf(src);

    tow << "std::sort" << endl;
    tow << "size: " << q.size() << "   ";
    sort(q.begin(), q.end());
    tow << "compares: " << Student::compared() << endl;
    Student::compareReset();

    tow << "size: " << h.size() << "   ";
    sort(h.begin(), h.end());
    tow << "compares: " << Student::compared() << endl;
    Student::compareReset();

    tow << "size: " << src.size()  << "   ";
    sort(src.begin(), src.end());
    tow << "compares: " << Student::compared() << endl;
    Student::compareReset();
}

//		works fine
void doListSort(vector <Student> & src, ofstream & tow){

    vector<Student> q = vquarter(src);
    vector<Student> h = vhalf(src);

	list<Student> alist;
	list<Student> qlist;
	list<Student> hlist;

	for (auto i : src){
		alist.push_back(i);
	}
	for (auto i : q){
		qlist.push_back(i);
	}
	for (auto i : h){
		hlist.push_back(i);
	}

	tow << "std::list.sort" << endl;
	tow << "size: " << qlist.size() << "   ";
	qlist.sort();
	tow << "compares: " << Student::compared() << endl;
	Student::compareReset();

	tow << "size: " << hlist.size() << "   ";
	hlist.sort();
	tow << "compares: " << Student::compared() << endl;
	Student::compareReset();

	tow << "size: " << alist.size()  << "   ";
	alist.sort();
	tow << "compares: " << Student::compared() << endl;
	Student::compareReset();
}

void doLinSearch(vector <Student> & src, vector <int> & query, ofstream & tow){

    vector<Student> q = vquarter(src);
    vector<Student> h = vhalf(src);

    vector<int> qq = vquarter(query);
    vector<int> hq = vhalf(query);

    tow << "Linear Search" << endl;
    tow << "size: " << q.size() << "    ";
    for(auto id : qq){
    	Student s = Student();
    	s.setID(id);
        linearSearch(q, s);
    }
    tow << "compares: " << Student::compared() / q.size() << endl;
    Student::compareReset();

    tow << "size: " << h.size() << "    ";
    for(auto id : hq){
    	Student s = Student();
    	s.setID(id);
        linearSearch(h, s);
    }
    tow << "compares: " << Student::compared() / h.size() << endl;
    Student::compareReset();

    tow << "size: " << src.size() << "    ";
    for(auto id : query){
    	Student s = Student();
    	s.setID(id);
        linearSearch(src, s);
    }
    tow << "compares: " << Student::compared() / src.size() << endl;
    Student::compareReset();
}

void doLibFind(vector <Student> & src, vector <int> & query, ofstream & tow){

    vector<Student> q = vquarter(src);
    vector<Student> h = vhalf(src);


    vector<int> qq = vquarter(query);
    vector<int> hq = vhalf(query);

	tow << "std::find" << endl;
	    tow << "size: " << q.size() << "    ";
	    for(auto id : qq){
	    	Student s = Student();
	    	s.setID(id);
	        find(q.begin(), q.end(), s);
	    }
	    tow << "compares: " << Student::compared() / q.size() << endl;
	    Student::compareReset();

	    tow << "size: " << h.size() << "    ";
	    for(auto id : hq){
	    	Student s = Student();
	    	s.setID(id);
	        find(h.begin(), h.end(), s);
	    }
	    tow << "compares: " << Student::compared() / h.size() << endl;
	    Student::compareReset();

	    tow << "size: " << src.size() << "    ";
	    for(auto id : query){
	    	Student s = Student();
	    	s.setID(id);
	        find(src.begin(), src.end(), s);
	    }
	    tow << "compares: " << Student::compared() / src.size() << endl;
	    Student::compareReset();
}

void doSetFind(vector <Student> & src, vector <int> & query, ofstream & tow){


	vector<Student> q = vquarter(src);
	vector<Student> h = vhalf(src);

    vector<int> qq = vquarter(query);
    vector<int> hq = vhalf(query);

	set<Student> hs;
	set<Student> qs;
	set<Student> as;


	for (auto p : q){
		qs.insert(p);
	}
	for (auto p : h){
		hs.insert(p);
	}
	for (auto p : src){
		as.insert(p);
	}

	Student::compareReset();

	tow << "std::set.find" << endl;
	tow << "size: " << qs.size() << "    ";
	for(auto id : qq){
		Student s = Student();
		s.setID(id);
		qs.find(s);
	}
	tow << "compares: " << Student::compared() / qs.size() << endl;
	Student::compareReset();

	tow << "size: " << hs.size() << "    ";
	for(auto id : hq){\
		Student s = Student();
		s.setID(id);
		hs.find(s);
	}
	tow << "compares: " << Student::compared() / hs.size() << endl;
	Student::compareReset();

	tow << "size: " << as.size() << "    ";
	for(auto id : query){
		Student s = Student();
		s.setID(id);
		as.find(s);
	}
	tow << "compares: " << Student::compared() / as.size() << endl;
	Student::compareReset();

}

int main(int argc, const char * argv[])
{
    vector<Student> all;
    vector<Student> alls;
    vector<int> allq;
    
    ofstream out;
    out.open(argv[3]);



    vector<string> read = populateTemp(argv[1]);
    
	while(read.size()>=4){			//populate student list
		Student newStudent;			//new student!
		newStudent.setPhone(read.back());
		read.pop_back();
		newStudent.setAddress(read.back());
		read.pop_back();
		newStudent.setName(read.back());
		read.pop_back();			//copying and destroying info in read
		string idString = read.back();
		int newID = atoi(idString.c_str());
		newStudent.setID(newID);
		read.pop_back();
		alls.push_back(newStudent);
	}

	for(int i = alls.size() - 1; i >= 0; i--){
		all.push_back(alls.at(i));
	}

    read = populateTemp(argv[2]);
    
    for (auto thing : read){
        int conv = atoi(thing.c_str());
        allq.push_back(conv);  //	was popping back here but not really needed bc loop
    }
    


    
    
    /*                                  Sorts                            */
    
    doSelSort(all, out);

    doInsertionSort(all, out);

    doLibrarySort(all, out);

    doListSort(all, out);



    
    /*                          Searches                                    */
    
    doLinSearch(all, allq, out);
    
    doLibFind(all, allq, out);

    doSetFind(all, allq, out);

    
    return 0;
}

