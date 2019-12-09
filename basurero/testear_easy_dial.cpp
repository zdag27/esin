#include<iostream>
using namespace std;

int main()
{
	char c;
	while(cin >> c)
		cout << char(int(c)-1) << " - " << int(c) << " - " << char(int(c)+1) << endl;
	return 0;
}