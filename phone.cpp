#include "phone.hpp"

/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt).
Es produeix un error si name no és un identificador legal. */
phone::phone(nat num, const string& name, nat compt) throw(error){
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
	_name=T.nom();
	_num=T.numero();
	_compt=T.frequencia();

}
phone& phone::operator=(const phone& T) throw(error){
	_name=T.nom();
	_num=T.numero();
	_compt=T.frequencia();
	return *this;
}
phone::~phone() throw(){
}

/* Retorna el número de telèfon. */
nat phone::numero() const throw(){
	return _num;
}

/* Retorna el nom associat al telèfon, eventualment l'string buit. */
string phone::nom() const throw(){
	return _name;
}

/* Retorna el número de vegades que s'ha trucat al telèfon. */
nat phone::frequencia() const throw(){
	return _compt;
}

/* Operador de preincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una referència a aquest telèfon. */
phone& phone::operator++() throw(){
	++_compt;
	return *this;
}

/* Operador de postincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una còpia d'aquest telèfon sense incrementar. */
phone phone::operator++(int) throw(){
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
	if(this->nom()==T.nom() and this->frequencia()==T.frequencia())
		return true;
	return false;
}
bool phone::operator!=(const phone& T) const throw(){
	return !(*this==T);
}
bool phone::operator<(const phone& T) const throw(){
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
	return (T<*this);
}

bool phone::operator<=(const phone& T) const throw(){
	return !(*this>T);
}

bool phone::operator>=(const phone& T) const throw(){
	return !(*this<T);
}

/* Caràcters especials no permesos en un nom de telèfon. */
static const char DELETECHAR = '<';
static const char ENDCHAR = '|';
static const char ENDPREF = '\0';

