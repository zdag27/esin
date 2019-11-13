#include "phone.hpp"
/* Construeix un telèfon a partir del seu número (num), el seu nom
(name) i el seu comptador de trucades (compt).
Es produeix un error si name no és un identificador legal. */
phone::phone(nat num, const string& name, nat compt) throw(error){
    cellphone=new node;
    try{
        cellphone->_name=name;
        cellphone->_num=num;
        cellphone->_compt=compt;
        if(cellphone->_name.find(DELETECHAR) or cellphone->_name.find(ENDCHAR)  or cellphone->_name.find(ENDPREF)){
            delete cellphone;
            throw;
        }
    }catch (...){
        delete cellphone;
        throw;
    }
};

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
phone::phone(const phone& T) throw(error){
    cellphone=new node;
    try{
        cellphone->name=T.nom();
        cellphone->num=T.numero();
        cellphone->compt=T.frequencia();
    }
    catch (...) {
        delete cellphone;
        throw;
    }
}
phone& phone::operator=(const phone& T) throw(error){
    delete cellphone;
    cellphone=new node;
    try{
        cellphone->_name=T.nom();
        cellphone->_num=T.numero();
        cellphone->_compt=T.frequencia();
    }
    catch (...) {
        delete cellphone;
        throw;
    }

}
phone::~phone() throw(){
    delete cellphone;
}

/* Retorna el número de telèfon. */
nat phone::numero() const throw(){
    return cellphone->num;
}

/* Retorna el nom associat al telèfon, eventualment l'string buit. */
string phone::nom() const throw(){
    return cellphone->name;
}

/* Retorna el número de vegades que s'ha trucat al telèfon. */
nat phone::frequencia() const throw(){
    return cellphone->compt;
}

/* Operador de preincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una referència a aquest telèfon. */
phone& phone::operator++() throw(){
    ++cellphone->compt;
    return cellphone;
}

/* Operador de postincrement.
Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
retorna una còpia d'aquest telèfon sense incrementar. */
phone phone::operator++(int) throw(){
        phone a(this->numero(),this->nom(),this->frequencia()+1);
}

/* Operadors de comparació.  L'operador > retorna cert, si i només si, el
telèfon sobre el que s'aplica el mètode és més freqüent que el
telèfon T, o a igual freqüència, el nom associat al telèfon és
major en ordre lexicogràfic que el nom associat a T.
La resta d'operadors es defineixen consistentment respecte a >. */
bool phone::operator==(const phone& T) const throw(){
    if(this->nom()==T.nom() and this->numero()==T.numero() and this->frequencia()==T.frequencia())
        return true;
    return false;
}
bool phone::operator!=(const phone& T) const throw(){
    return !(*this==T);
}
bool phone::operator<(const phone& T) const throw(){
   if(this->nom()<T.nom()){
       return true;
   }else if(this->nom()==T.nom()){
       if(this->numero()<T.numero()){
           return true;
       }else if(this->numero()==T.numero()){
           if(this->frequencia()<T.frequencia()){
               return true;
           }
       }
   }
   return false;
}
bool phone::operator>(const phone& T) const throw(){
    if(this->nom()>T.nom()){
        return true;
    }else if(this->nom()==T.nom()){
        if(this->numero()>T.numero()){
            return true;
        }else if(this->numero()==T.numero()){
            if(this->frequencia()>T.frequencia()){
                return true;
            }
        }
    }
    return false;
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


