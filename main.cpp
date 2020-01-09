#include<iostream>
#include<sstream>
using namespace std;

int main(int argc, char const *argv[])
{
	string s;
	string bools;
	string nivel;
	string resultado;
	string correcto;
	while(getline(cin, s)){
		istringstream ss(s);
		ss >> s;
		if(s == "#anterior"){
			getline(cin, bools);
			getline(cin, nivel);
			getline(cin, resultado);
			//preresultado += resultado;
			getline(cin, correcto);
			if(("##" + resultado) != correcto){
				cout << bools << endl;
				cout << nivel << endl;
				cout << resultado << endl;
				cout << correcto << endl;
				cout << endl;
			}
		}
	}
	return 0;
}