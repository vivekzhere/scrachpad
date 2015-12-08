#include "kmpMatcher.h"
#include <iostream>

kmpMatcher::kmpMatcher (string p) {
	pattern = p;
	preProcessPattern();
}

/* Pre process the pattern to calulate the next state on fallure for each state.
 * nextStateOnFailure[0] = -1
 * nextStateOnFailure[j] = i | if i is the largest integer such that i < j and
 *				pattern[j - 1] = pattern[i - 1]
 *				pattern[j - 2] = pattern[i - 2]
 *				. . .
 *				pattern[j - i] = pattern[0]
 *			    0 | if no such i exist 
 */
void kmpMatcher::preProcessPattern() {
	int i, j;

	nextStateOnFailure.resize(pattern.length() + 1);
	nextStateOnFailure[0] = -1;
	
	for (i = -1, j = 0; j < pattern.length(); j++) {
		while(i >= 0 && pattern[i] != pattern[j])
			i = nextStateOnFailure[i];
		i++;
		nextStateOnFailure[j + 1] =  i;
	}
}

void kmpMatcher::printMachine() {
	cout<<"Pattern : "<<pattern<<endl;
	cout<<"Fn      : ";
	for (int i = 0; i < nextStateOnFailure.size(); i++)
		cout<<nextStateOnFailure[i]<<" ";
	cout<<endl;

}

bool kmpMatcher::parseForPattern(string s) {
	int state, i, m;
	m = pattern.length();
	state = i = 0;
	while (i < s.length()) {
		while (state == m || (state >= 0 && pattern[state] != s[i]))
			state = nextStateOnFailure[state];
		state++;
		i++;
		if (state == m)
			return true;
	}
	return false;
}
