#include <iostream>
#include "phone.cpp"
using namespace std;

int main()
{
	phone a;
	cout << a.nom() << " " << a.numero() << " " << a.frequencia() << " " << endl;
	phone c(123456789,"nombre",149);
	phone b(c);
	cout << b.nom() << " " << b.numero() << " " << b.frequencia() << " " << endl;
	if(b == c){
		cout << "AYUWOKI" << endl;
	}
	return 0;
}