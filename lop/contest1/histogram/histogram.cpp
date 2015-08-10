#include <iostream>
#include <stack>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int main ()
{
	ull n, i, item, max_area, cur_area;
	stack<ull> stk;
	vector<ull> his;

	cin>>n;
	while(n) {
		for (i = 0; i < n; i++) {
			cin>>item;
			his.push_back(item);
		}

		i = 0;
		max_area = 0;
		while (i < n) {
			if (stk.empty() || his[stk.top()] <= his[i])
				stk.push(i++);
			else {
				item = stk.top();
				stk.pop();
				cur_area = his[item] * (stk.empty() ? i : (i - 1 - stk.top()));
				
				if (cur_area > max_area)
					max_area = cur_area;
			}
		}
		
		while (!stk.empty()) {
			item = stk.top();
			stk.pop();
			cur_area = his[item] * (stk.empty() ? i : (i - 1 - stk.top()));
			
			if (cur_area > max_area)
				max_area = cur_area;
		}

		cout<<max_area<<endl;
		his.clear();

		cin>>n;
	}

	return 0;
}
