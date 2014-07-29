//
//  main.cpp
//  project 5
//
//  Created by Arthur Hatfield on 21/03-2014.
//  Copyright (c) 2014 Arthur Hatfield. All rights reserved.
//	modified and checked 12 / VII - 2014
//	version 1.01
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[])
{
    ifstream in;
    in.open(argv[1]);
    ofstream out;
    out.open(argv[2]);
	
	string s;
	LinkedList<string> l;
	
	while (in >> s){
		string s1;
		s1 = s;

		string s2;
		string s3;
		if(s1 == "clear"){
			l.clear();
			out<< "clear" << endl;
		}
		else if(s1 == "insert"){
			in >> s2;
			in >> s3;
			int digit = atoi(s2.c_str());
			string data = s3;
			l.insert(digit,data);
			out << s + " " + s2 + " " + s3 << endl;
		}
		else if(s1 == "print"){
			out << s << endl;
			l.print(out);
		}
		else if(s1 == "find"){
			in >> s3;
			string data = s3;
			int i = l.find(data);
			out << "find " << data << " " << i << endl;
		}
		else if(s1 == "remove"){
			in >> s2;
			int digit = atoi(s2.c_str());
			string k = l.remove(digit);
			out << "remove " << digit << " " << k << endl;
		}
	}
    
    
    return 0;
}

