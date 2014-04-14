/*
 * Grade.h
 *
 *  Created on: Jan 22, 2014
 *      Author: hatfiaw
 */

#ifndef GRADE_H_
#define GRADE_H_
#include <string>
#include <map>

using namespace std;

class Grade {
public:
	Grade();
	virtual ~Grade();

	void setCourse(string);
	void setID(int);
	void setGrade(string);

	int getID();
	void print(ofstream&);

	float gpa();

	bool operator < (Grade) const;

	string course;
	int id;
	string grade;
	map<string,float> values;

};


#endif /* GRADE_H_ */
