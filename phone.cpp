#include "phone.hpp"

/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt).
Es produeix un error si name no és un identificador legal. */
phone::phone(nat num, const string& name, nat compt) throw(error){
/*
revisa que en el string del nombre no haya ningun caracter invalido y lo crea en caso contrario matematico generara un error 
coste=1
*/
	unsigned int x=name.length();
	for (unsigned int i = 0; i < x; ++i) {
		if( name[i]== '<' or name[i]=='|'  or name[i]=='\0') {
			throw (error(ErrNomIncorrecte));
		}
	}
	_name=name;
	_num=num;
	_compt=compt;
};


/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone::phone(const phone& T) throw(error){
/*
genera una copia con cada uno de los argumentos de T
coste 1
*/
	_name=T.nom();
	_num=T.numero();
	_compt=T.frequencia();

}
phone& phone::operator=(const phone& T) throw(error){
/*
retorna un phone nuevo que posee todos los elementos de T
coste 1
*/
	_name=T.nom();
	_num=T.numero();
	_compt=T.frequencia();
	return *this;
}
phone::~phone() throw(){
/*
realiza la destruccion por defecto
coste 1
*/
}

/* Retorna el número de telèfon. */
nat phone::numero() const throw(){
/*retorna el natural referente al numero de telefono del phone
coste 1
*/
	return _num;
}

/* Retorna el nom associat al telèfon, eventualment l'string buit. */
string phone::nom() const throw(){
/*
retorna el string referente al apartado del nombre 
coste 1
*/
	return _name;
}

/* Retorna el número de vegades que s'ha trucat al telèfon. */
nat phone::frequencia() const throw(){
/*
retorna el apartado del contador de la estructura
coste 1
*/	
	return _compt;
}

/* Operador de preincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una referència a aquest telèfon. */
phone& phone::operator++() throw(){
        /*
        aumenta el contador de llamadas del telefono y lo retorna
        coste 1
        */
	++_compt;
	return *this;
}

/* Operador de postincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una còpia d'aquest telèfon sense incrementar. */
phone phone::operator++(int) throw(){
/*
crea un nuevo telefono copia del antiguo, suma el contador del viejo y retorna el nuevo
coste 1
*/
	phone a(this->numero(),this->nom(),this->frequencia());
	++_compt;
	return a;
}

/* Operadors de comparació.  L'operador > retorna cert, si i només si, el
telèfon sobre el que s'aplica el mètode és més freqüent que el
telèfon T, o a igual freqüència, el nom associat al telèfon és
major en ordre lexicogràfic que el nom associat a T.
La resta d'operadors es defineixen consistentment respecte a >. */
bool phone::operator==(const phone& T) const throw(){
/*
revisa que todos los apartados, uno por uno
coste 1
*/
	if(this->nom()==T.nom() and this->frequencia()==T.frequencia())
		return true;
	return false;
}
bool phone::operator!=(const phone& T) const throw(){
/*
llama a la operacion que es su contraria y retorna el negado
coste 1
*/
	return !(*this==T);
}
bool phone::operator<(const phone& T) const throw(){
/*
revisa que elemento prioritario a elemento prioritario siendo la escala frequencia sucedida por nombre para revisar si efectivamente es menor
coste 1
*/		
	if(this->frequencia()<T.frequencia()){
		return true;
	}else if(this->frequencia()==T.frequencia()){
		if(this->nom()<T.nom()){
			return true;
		}
	}
	return false;
}

bool phone::operator>(const phone& T) const throw(){
	/*
	realiza la operacion menor que invertida para realizar un mayor que y retornar el booleano
	coste 1
	*/
	return (T<*this);
}

bool phone::operator<=(const phone& T) const throw(){
/*
realiza el negado de su contrario matematico y retorna el boleano
coste 1
*/
	return !(*this>T);
}

bool phone::operator>=(const phone& T) const throw(){
/*
realiza el negado de su contrario matematico y retorna el boleano
coste 1
*/	
	
	return !(*this<T);
}

/* Caràcters especials no permesos en un nom de telèfon. */
static const char DELETECHAR = '<';
static const char ENDCHAR = '|';
static const char ENDPREF = '\0';

