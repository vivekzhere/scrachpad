#include <iostream>
using namespace std;

int main ()
{
	int item[6];
        
	cin>>item[0]>>item[1]>>item[2]>>item[3]>>item[4]>>item[5];
 
	if ((item[0] != 0 && item[3] == item[0] && item[1] == 0 && item[2] == 0 && item[4] == 0 && item[5] == 0) ||
			(item[1] != 0 && item[4] == item[1] && item[0] == 0 && item[2] == 0 && item[3] == 0 && item[5] == 0) ||
			(item[2] != 0 && item[5] == item[2] && item[0] == 0 && item[1] == 0 && item[3] == 0 && item[4] == 0))
		cout<<"Losing"<<endl;
	else
		cout<<"Winning"<<endl;

  return 0;
}
