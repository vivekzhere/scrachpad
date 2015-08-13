#include <queue>
#include <stdio.h>

#define mod_b 1000000007
using namespace std;

typedef unsigned long long ull;

int main ()
{
	int t, n;
	ull sum, item;
	int a, b, c;

	scanf("%d", &t);

	while (t-- > 0) {
		priority_queue<ull> max_heap;
		priority_queue<ull, vector<ull>, greater<ull> > min_heap;
		scanf("%d %d %d %d", &a, &b, &c, &n);

		max_heap.push(1);
		sum = 1;
		for (int i = 2; i <= n; i++) {
			item = ((a * max_heap.top()) + (b * i) + c);
			if (item >= mod_b)
				item %= mod_b;

			if (!min_heap.empty() && item <= min_heap.top())
				max_heap.push(item);
			else
				min_heap.push(item);

			if (max_heap.size() > (min_heap.size() + 1)) {
				min_heap.push(max_heap.top());
				max_heap.pop();
			} else if (max_heap.size() < min_heap.size()) {
				max_heap.push(min_heap.top());
				min_heap.pop();
			}

			sum = sum + item;
			if (sum >= mod_b)
				sum %= mod_b;
		}
		printf("%lld\n", sum);
	}
	return 0;
}
