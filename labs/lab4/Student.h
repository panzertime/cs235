/*
 * Student.h
 *
 *  Created on: Jan 17, 2014
 *      Author: hatfiaw
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>

using namespace std;

class Student {
public:
	Student();
	virtual ~Student();
	bool operator < (Student) const;
	bool operator < (int) const;
    bool operator == (Student) const;
    bool operator == (int) const;
	void print(ofstream&); // print function
	void setID(int);		//settors
	void setName(string);
	void setAddress(string);
	void setPhone(string);


	int getID() const; 				//gettors
	string getName();
	string getAddress();
	string getPhone();
    
    static int compareCount;
    static int compared();
    static void compareReset();
    static void compInc();

private:
	int studentID;		// instance variables
	string name;
	string address;
	string phone;


};

#endif /* STUDENT_H_ */
