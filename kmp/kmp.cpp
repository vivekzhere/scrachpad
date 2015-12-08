#include <iostream>
#include <vector>
#include <string>

using namespace std;

class kmpMatcher {
	string pattern;
	vector<int> transissionFn;
	
	public:
	void printMachine() {
		cout<<"Pattern : "<<pattern<<endl;
		cout<<"Fn      : ";
		for (int i = 0; i < transissionFn.size(); i++)
			cout<<transissionFn[i]<<" ";
		cout<<endl;

	}
	kmpMatcher (string p) {
		int i, j;
		pattern = p;
		transissionFn.push_back(-1);
		for (i = -1, j = 0; j < pattern.length(); j++) {
			while(i >= 0 && pattern[i] != pattern[j])
				i = transissionFn[i];
			i++;
			transissionFn.push_back(i);
		}
	}

};
int main() {
	kmpMatcher m("abcabcdeab");
	m.printMachine();
	return 0;
}
