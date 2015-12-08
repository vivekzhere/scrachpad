#include <iostream>
#include <map>
using namespace std;
struct node {
	int c, s, f;
};
int main() {
	int N, P, i;
	cin>>N>>P;
	map<int, node> mymap;
	node t;
	map<int, node>::iterator it, it2;

	for (i = 1; i <= N; i++) {
		cin>>t.c>>t.s;
		t.f =0;
		mymap[i] = t;
	}

	for (i = 0; i < N; i++) {
		if (mymap[P].c == 0) {
			cout<<i<<endl;
			break;
		}
		for (it = mymap.begin(); it != mymap.end(); ) {
			if (it->second.f == 0 && it->second.c == 1) {
				it2 = mymap.find(it->second.s);
				it2->second.c--;
				it2->second.s -= it->first;
				if (it2->first > it->first)
					it2->second.f = 1;
				it2 = it;
				it++;
				mymap.erase(it2);
			} else {
				if (it->second.f == 1)
					it->second.f = 0;
				it++;
			}
		}
	}
	return 0;
}
