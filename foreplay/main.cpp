#include <iostream>
#include "call_registry.hpp"
using namespace std;

int main()
{
	phone a;
	cout << "Phone A: Nom = " << a.nom() << ", Num = " << a.numero() << ", Freq = " << a.frequencia() << "." << endl;

	phone b(123456789,"nombre",149);
	cout << "Phone B: Nom = " << b.nom() << ", Num = " << b.numero() << ", Freq = " << b.frequencia() << "." << endl;
	phone c(b);
	cout << "Phone C: Nom = " << c.nom() << ", Num = " << c.numero() << ", Freq = " << c.frequencia() << "." << endl;
	
	if(a == b){
		cout << "Phone a == Phone b" << endl;
	} else {
		cout << "Phone a != Phone b" << endl;
	}
	if(b == c){
		cout << "Phone b == Phone c" << endl;
	} else {
		cout << "Phone b != Phone c" << endl;
	}

	cout << "Annie are you ";
	call_registry X;
	cout << "ok, are you ok?" << endl;
	X.registra_trucada(a.numero());
	cout << "are you ok Annie?" << endl;
	/*
	*/
	X.assigna_nom(a.numero(), a.nom());
	call_registry Y(X);
	X.elimina(a.numero());


	if(X.conte(a.numero())){
		cout << "X conte " << a.numero() << endl;
	} else {
		cout << "X no conte " << a.numero() << endl;
	}
	
	if(Y.conte(a.numero())){
		cout << "Y conte " << a.numero() << endl;
	} else {
		cout << "Y no conte " << a.numero() << endl;
	}

}