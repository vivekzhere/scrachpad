#include <iostream>
#include <vector>
#include <string>

using namespace std;

class kmpMatcher {
	string pattern; /* Pattern to me matched */
	vector<int> transissionFn; /* On a match the state of the machine just increments.
				      But on failure the next state need to calculated so that,
				      we can make use of the already matched portion of the string.
				      */
	
	public:
	void printMachine() {
		cout<<"Pattern : "<<pattern<<endl;
		cout<<"Fn      : ";
		for (int i = 0; i < transissionFn.size(); i++)
			cout<<transissionFn[i]<<" ";
		cout<<endl;

	}
	/* Pre process the pattern to calulate the next state on fallure for each state,
	 *
	 */
	kmpMatcher (string p) {
		int nextState, currentState;
		pattern = p;
		transissionFn.push_back(-1);
		for (nextState = -1, currentState = 0; currentState < pattern.length(); currentState++) {
			while(nextState >= 0 && pattern[nextState] != pattern[currentState])
				nextState = transissionFn[nextState];
			nextState++;
			transissionFn.push_back(nextState);
		}
	}
	bool parseForPattern(string s) {
		int state, i, m;
		m = pattern.length();
		state = i = 0;
		while (i < s.length()) {
			while (state == m || (state >= 0 && pattern[state] != s[i]))
				state = transissionFn[state];
			state++;
			i++;
			if (state == m)
				return true;
		}
		return false;
	}

};
int main() {
	kmpMatcher m("abcabcdeab");
	m.printMachine();
	if (m.parseForPattern("dggaabcabcabcabcdeabcabc"))
		cout<<"Match"<<endl;
	else
		cout<<"No Match"<<endl;

	return 0;
}
