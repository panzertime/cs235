//============================================================================
// Name        : lab2.cpp
// Author      : RT Hatfield
// Version     :
// Copyright   : this
// Description :
//============================================================================

#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <list>
#include <sstream>
#include <vector>

using namespace std;

string pretty(string& targ){		//make strings compatible w/ dictionary
	for (unsigned i = 0; i < targ.length(); i++){
		targ[i] = tolower(targ[i]);	//send characters to lowercase
	}
	string ret;
	for (unsigned i = 0; i < targ.length(); i++){
		if(isalpha(targ.at(i)) || isspace(targ.at(i))){
			ret.push_back(targ.at(i));
		}
		else{
			ret.push_back(' ');
		}
	}
	return ret;
}

set<string> newDict(char* from){
	ifstream src;					//open streams etc.
	src.open(from);

	set<string> dest;
	string s;
	while(getline(src, s)){			//read file into set, word by word
		s = pretty(s);
		dest.insert(s);
	}

	src.close();					//close stream, return set
	return dest;
}

vector<string> lineBreaker(string& s){
	vector<string> v;
	unsigned o = s.find(" ");
	if(o <= (s.length() - 1)){
		string q;
		q = s.substr(0,o);
		s = s.substr(o);
		v.push_back(q);
	}
	for(unsigned i = 0; i < s.size(); i++){
		if(isspace(s[i])){
			i++;					//skip bc it's a space
			string ss = s.substr(i);
			int k = ss.find(" ");
			string sss = ss.substr(0,k);
			v.push_back(sss);
		}
	}
return v;
}

void generateOutput(char* to, map<string, list<int>>& source){
	ofstream dest;
	dest.open(to);

	map<string, list<int>>::iterator i;

	for(i = source.begin(); i != source.end(); i++){
		dest << i->first;
		dest << ":";
		for(auto printable : i->second){
			dest << printable;
			dest << " ";
		}
		dest << endl;
	}

	dest.close();
}

int main(int argc, char* argv[]) {

	set<string> dictionary = newDict(argv[1]);

	ifstream document;

	document.open(argv[2]);

	string wordp;

	map<string, list<int>> errors;

	int lineCounter = 0;

	while(getline(document, wordp)){
		lineCounter++;				//because we want to iterate on every line in the document
//		cout << wordp.length() << " " << wordp << endl;
		wordp = pretty(wordp);
//		cout << wordp.length() << " " << wordp << endl;
		stringstream words;
		words.str(wordp);
		if(wordp.length() > 0){
//			vector<string> words = lineBreaker(wordp);
			string w;
				while(words >> w){		//auto thinks i want a character.

					if(!dictionary.count(w)){

						errors[w].push_back(lineCounter);
											//i am about 75 percent sure this will work.  LET'S HOPE
					}

				}
		}
	}

	generateOutput(argv[3],errors);


	return 0;
}
