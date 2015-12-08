#include <iostream>
#include "kmpMatcher.h"

int main() {
	kmpMatcher m("abcabcdeab");
	m.printMachine();
	if (m.parseForPattern("dggaabcabcabcabcdeabcabc"))
		cout<<"Match"<<endl;
	else
		cout<<"No Match"<<endl;

	return 0;
}
