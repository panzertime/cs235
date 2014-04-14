//============================================================================
// Name        : lab1.cpp
// Author      : RT Hatfield
// Version     :
// Copyright   : this
// Description : lab1: GPA calculator
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "Student.h"
#include "Grade.h"

using namespace std;

vector<string> populateTemp(char* file){
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

 /*vector<string> makeStudent(vector<string> source){
	vector<string>
	Student newStudent;		//new student!
	newStudent.setPhone(source.back());
	source.pop_back();
	newStudent.setAddress(source.back());
	source.pop_back();
	newStudent.setName(source.back());
	source.pop_back();			//copying and destroying info in read
	string idString = source.back();
	int newID = atoi(idString.c_str());
	newStudent.setID(newID);
	source.pop_back();
	destination.push_back(newStudent);
	//add newest student to student vector
}*/
	// makes students but also sigsegs

/*void makeGrade(vector<string>& source, vector<Grade>& destination){
	Grade newGrade;				//new Grade!
	newGrade.setGrade(source.back());
	source.pop_back();
	string idString = source.back();
	int newID = atoi(idString.c_str());
	newGrade.setID(newID);
	source.pop_back();
	newGrade.setCourse(source.back());
	source.pop_back();
	destination.push_back(newGrade);
	//add newest grade to grade vector
}*/
	// makes grades but also sigsegs

void printJob(vector<Student>& kids, vector<Grade>& grades, ofstream& where){
	for(auto printable : kids){
		printable.print(where);
	}
	where<<endl;
	where<<endl; 					//whitespace for readability
	for(auto printable : grades){
		printable.print(where);
	}
	where<<endl;
	where<<endl; 					//whitespace for readability
}

void vectorConvert(vector<string>& from,vector<int>& to){
	for (auto thing : from){
		int convert = atoi(thing.c_str());
		to.push_back(convert);
	}

}

bool nameExists(int id, vector<Student>& lookIn){
	for(auto indiv : lookIn){
		if(indiv.getID() == id){
			return 1;
		}
	}
	return 0;
}

string seekName(int id, vector<Student>& lookIn){
	for(auto indiv : lookIn){
		if(indiv.getID() == id){
			return indiv.getName();
		}
	}
	return "";
}

void search(vector<int>& toSearch, vector<Grade>& findIn, vector<Student>& xRef, ofstream& where){
	for (auto query : toSearch){		//actually execute queries, one by one
		float accumulator = 0; 		//default values
		float hits = 0;
		float gpa = 0;
		string queryname = "Unknown";

		if(nameExists(query, xRef)){	//if name exists, get it
			queryname = seekName(query, xRef);
		}
		else { continue; }				//otherwise skip this guy


		for (auto gparec : findIn){	//now step thru, find matches, add up
			if (gparec.getID() == query){
				hits++;
				accumulator = accumulator + gparec.gpa();
			}
		}

		if(hits != 0){				//prevent divide-by-zero
			gpa = accumulator / hits;
		}

		else {gpa = 0;}				// probably unnecessary

		where << query << "    " << fixed << setprecision(2) << setfill('0') << gpa << "    " << queryname << endl;
									// and... print (to file)!
	}

}

int main(int argc, char* argv[]) {
	ofstream out;
	out.open(argv[4]);


	vector<Student> students;
	vector<string> read;

	//cout << "init" << endl;

	read = populateTemp(argv[1]);	//temporary holder for students

	//cout << "make students" << endl;

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
		students.push_back(newStudent);
	}

	//cout << "sort students" << endl;

	sort(students.begin(),students.end());		//sort our students

	vector<Grade> grades;

	//cout << "populate grades" << endl;

	read = populateTemp(argv[2]);

	//cout << "make grades" << endl;

	while(read.size() >= 3){
		Grade newGrade;				//new Grade!
		newGrade.setGrade(read.back());
		read.pop_back();
		string idString = read.back();
		int newID = atoi(idString.c_str());
		newGrade.setID(newID);
		read.pop_back();
		newGrade.setCourse(read.back());
		read.pop_back();
		grades.push_back(newGrade);
	}

	//cout << "sort grades" << endl;

	sort(grades.begin(),grades.end());
									//sort our grades
	printJob(students, grades, out);//print our students and grades

	vector<int> queries;			//vector for our queries

	vector<string> querytemp;

	querytemp = populateTemp(argv[3]);

	vectorConvert(querytemp, queries);

	search(queries, grades, students, out);

	out.close();

	return 0;
}


