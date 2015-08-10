#include <iostream>
#include <string>
using namespace std;

int main ()
{
	string str;
	char c, cur;
	int f, count;

	cin>>str;
	count = f = 1;
	c = cur = str[0];
	
	string::iterator ch;
	for(ch = str.begin()+1; ch != str.end(); ch++)
	{
		if (cur == *ch) {
			count++;
			continue;
		}
		else if (count > f || (count == f && c > cur)) {
			f = count;
			c = cur;
		}
		count = 1;
		cur = *ch;
	}
	if (count > f || (count == f && c > cur)) {
		f = count;
		c = cur;
	}
	cout << c << endl << f << endl;
}
