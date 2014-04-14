/*
 * Student.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: hatfiaw
 */

#include "Student.h"
#include <fstream>

using namespace std;

Student::Student() {
	address = "";
	name = "";
	phone = "";
	studentID = 0;
}

Student::~Student() {
	// TODO Auto-generated destructor stub
}

bool Student::operator < (Student s) const { // comparison
		return studentID < s.studentID;
} //I know this was on the class site but I know how it works, so there

void Student::setID(int newID) {
	studentID = newID;
}

void Student::setName(string newName) {
	name = newName;
}

void Student::setAddress(string newAddr) {
	address = newAddr;
}

void Student::setPhone(string newPhone) {
	phone = newPhone;
}

int Student::getID() {
	return studentID;
}

string Student::getName() {
	return name;
}

string Student::getAddress() {
	return address;

}
string Student::getPhone() {
	return phone;
}

void Student::print(ofstream& where) {
	where << name << endl;
	where << studentID << endl;
	where << phone << endl;
	where << address << endl;
}
