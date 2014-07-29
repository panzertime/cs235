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
#include <map>
#include <algorithm>
#include <string>
#include "Student.h"
#include "Grade.h"

using namespace std;

void populateS(char* file, vector<Student>& into){
	ifstream readIn;		//make all the things i need to populate my vectors
	string sget;

	readIn.open(file); 		//open student file

	while(getline(readIn, sget)){
		Student newStudent;			//new student!
		//string idString = sget;
		int newID = atoi(sget.c_str());
		newStudent.setID(newID);
		getline(readIn, sget);
		newStudent.setName(sget);
		getline(readIn, sget);
		newStudent.setAddress(sget);
		getline(readIn, sget);			
		newStudent.setPhone(sget);
		into.push_back(newStudent);
	}

	readIn.close();				//close this file
}

void populateG(char* file, vector<Grade>& into){
  ifstream readIn;
  string sget;
  readIn.open(file);

  while(getline(readIn, sget)){
		Grade newGrade;				//new Grade!
		newGrade.setCourse(sget);
		getline(readIn, sget);
		int newID = atoi(sget.c_str());
		newGrade.setID(newID);
		getline(readIn, sget);
		newGrade.setGrade(sget);
		into.push_back(newGrade);
	}
}

void printJob(vector<Student>& kids, vector<Grade>& grades, ofstream& where){
	for(auto printable : kids){
		printable.print(where);
	}
	where<<endl;
	where<<endl; 					//whitespace for readability
	if(grades.size() > 0){
	  for(auto printable : grades){
	    printable.print(where);
	  }
	  where<<endl;
	  where<<endl; 					//whitespace for readability
	}
}

void populateQ(char* from, vector<int>& to){
  ifstream readIn;
  string sget;
  readIn.open(from);
  while (getline(readIn, sget)){
	int convert = atoi(sget.c_str());
	to.push_back(convert);
	}
}

//bool nameExists(int id, vector<Student>& lookIn){ for(auto indiv :
//	lookIn){ if(indiv.studentID == id){ return 1; } } return 0; }

//string seekName(int id, vector<Student>& lookIn){ for(auto indiv :
//	lookIn){ if(indiv.studentID == id){ return indiv.getName(); }
//	} return ""; }

string idToName(int& id, vector<Student>& lookIn){
  for(auto indiv : lookIn){
    if(indiv.studentID == id){
      return indiv.getName();
    }
  }
  return "";
}

void search(vector<int>& toSearch, vector<Grade>& findIn, vector<Student>& xRef, ofstream& where){
		float accumulator = 0; 		//default values
		float hits = 0;
		float gpa = 0;
		string queryname = "Unknown";
	
  for (auto query : toSearch){		//actually execute queries, one by one
		
		queryname = idToName(query, xRef);
		hits = 0;
		accumulator = 0;


		if(queryname != ""){	//if name exists, get it
				for (auto gparec : findIn){ //now step thru, find matches, add up 
				  if (gparec.id == query){
				    hits++;
				    accumulator = accumulator + gparec.gpa(); 
				  }
				}

				if(hits != 0){ //prevent divide-by-zero 
				  gpa = accumulator / hits;
				}

				else {gpa = 0;} // probably unnecessary

				where << query << " " << fixed << setprecision(2) << setfill('0') << gpa << " " << queryname << endl; //and... print (to file)!
		}
		

	}
}

void doGPA(map<int, float>& dest, vector<Student>& people, vector<Grade>& data){
  float accumulator;
  float hits;
  for(auto person : people){
    accumulator = 0;
    hits = 0;
    for(auto entry : data){
      if(entry.id == person.studentID){
	accumulator = accumulator + entry.gpa();
	hits++;
      }
    }
    if(hits !=0){
      dest[person.studentID] = (accumulator / hits);
    }
  }
}
    
      
      

int main(int argc, char* argv[]) {
	ofstream out;
	out.open(argv[4]);


	vector<Student> students;
	//map<int, float> GPAs;
	map<int, string> names;

	populateS(argv[1],students);

	sort(students.begin(),students.end());		//sort our students
	for(auto person : students){
	  names[person.studentID] = person.name;
	}//making a map of names


	vector<Grade> grades;

	populateG(argv[2], grades);

	sort(grades.begin(),grades.end());
									//sort our grades
	printJob(students, grades, out);//print our students and grades

	vector<int> queries;			//vector for our queries

	populateQ(argv[3], queries);

	//search(queries, grades, students, out);
	//doGPA(GPAs, students, grades);
	//for(auto q : queries){
	//  if(names.count(q) > 0){
	//    out << q << " " << fixed << setprecision(2) << setfill('0') << GPAs[q] << " " << names[q] << endl; //and... print (to file)!
	//  }
	//}

	float accumulator;
	float hits;
	for(auto q : queries){
	  if(names[q] != ""){
	    accumulator = 0;
	    hits=0;
	    for(auto entry : grades){
	      if(entry.id == q){
		accumulator = accumulator + entry.gpa();
		hits++;
	      }
	    }
	    if(hits != 0){
	      out << q << " " << fixed << setprecision(2) << setfill('0') << accumulator / hits << " " << names[q] << endl; //and... print (to file)
	    }
	    else{
	      out << q << " 0.00 " << names[q] << endl; //and... print (to file)
	    }
	  }
	}
	
	out.close();

	return 0;
}


