/*
 * Grade.cpp
 *
 *  Created on: Jan 22, 2014
 *      Author: hatfiaw
 */

#include "Grade.h"
#include <fstream>
#include <map>

using namespace std;

Grade::Grade() {
	course = "";
	id = 0;
	grade = "";

	values["A"]=4;			//make a reference table for computing GPAs
	values["A-"]=3.7;
	values["B+"]=3.4;
	values["B"]=3.0;
	values["B-"]=2.7;
	values["C+"]=2.4;
	values["C"]=2;
	values["C-"]=1.7;
	values["D+"]=1.4;
	values["D"]=1;
	values["D-"]=0.7;

}

Grade::~Grade() {
	// TODO Auto-generated destructor stub
}

	void Grade::setCourse(string newCourse){
		course = newCourse;
	}

	void Grade::setID(int newID){
		id = newID;
	}

	void Grade::setGrade(string newGrade){
		grade = newGrade;
	}

	int Grade::getID(){
		return id;
	}

	void Grade::print(ofstream& where){
		where << id << "    " << grade << "    " << course << endl;
	}

	float Grade::gpa(){
		return values[grade];			//bad values are automatically 0!
	}

	bool Grade::operator < (Grade g) const {
		return id < g.id ||
		      (id == g.id && course < g.course) ||
		      (id == g.id && course == g.course && grade < g.grade);
		  }




