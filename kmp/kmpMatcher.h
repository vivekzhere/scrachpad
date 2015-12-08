#ifndef KMPMATCHER_H
#define KMPMATCHER_H
#include <vector>
#include <string>
using namespace std;

class kmpMatcher {
	string pattern; /* Pattern to me matched */
	vector<int> nextStateOnFailure; /* On a match the state of the machine just increments.
				      But on failure the next state need to calculated so that,
				      we can make use of the already matched portion of the string.
				      */
	
	void preProcessPattern();
public:
	kmpMatcher (string p);
	void printMachine();
	bool parseForPattern(string s);
};
#endif
