#include "phone.hpp"
  /* Construeix un telèfon a partir del seu número (num), el seu nom
  (name) i el seu comptador de trucades (compt). 
  Es produeix un error si name no és un identificador legal. */
phone(nat num=0, const string& name="", nat compt=0) throw(error){
    _pho=new node;
    try{
        _pho->name=name;
        _pho->num=num;
        _pho->compt=compt;
            for(i=0;i<_pho->name.size();++i){
                if(_pho->name[i]=="<" or _pho->name[i]== "|" or _pho->name[i]=="\0"){
                    delete _pho;
                    throw();
                }
        }
    }
     catch (...) {
            delete _pho;
            throw();
    }
}

  /* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
  phone(const phone& T) throw(error){
        _pho=new node;
        try{
            _pho->name=T->name;
            _pho->num=T->num;
            _pho->compt=T->compt;
        }
        catch (...) {
            delete _pho;
            throw();
         }
  }
  phone& operator=(const phone& T) throw(error){
    delete _pho;
            _pho=new node;
    try{
        _pho->name=T->name;
        _pho->num=T->num;
        _pho->compt=T->compt;
    }
    catch (...) {
        delete _pho;
        throw();
     }
    
  }
  ~phone() throw(){
    delete _pho
  }

  /* Retorna el número de telèfon. */
  nat numero() const throw(){
    return _pho->num;
  }

  /* Retorna el nom associat al telèfon, eventualment l'string buit. */
  string nom() const throw(){
    return _pho->name;
  }

  /* Retorna el número de vegades que s'ha trucat al telèfon. */
  nat frequencia() const throw(){
    return _pho->compt;
 }

  /* Operador de preincrement. 
  Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
  retorna una referència a aquest telèfon. */
  phone& operator++() throw(){
    ++_pho->compt;
  }

  /* Operador de postincrement. 
  Incrementa en 1 el número de vegades que s'ha trucat al telèfon i
  retorna una còpia d'aquest telèfon sense incrementar. */
  phone operator++(int) throw(){
    ++_pho->compt;
  }

  /* Operadors de comparació.  L'operador > retorna cert, si i només si, el
  telèfon sobre el que s'aplica el mètode és més freqüent que el
  telèfon T, o a igual freqüència, el nom associat al telèfon és
  major en ordre lexicogràfic que el nom associat a T. 
  La resta d'operadors es defineixen consistentment respecte a >. */
  bool operator==(const phone& T) const throw();
  bool operator!=(const phone& T) const throw();
  bool operator<(const phone& T) const throw();
  bool operator>(const phone& T) const throw();
  bool operator<=(const phone& T) const throw();
  bool operator>=(const phone& T) const throw();

  /* Caràcters especials no permesos en un nom de telèfon. */
  static const char DELETECHAR = '<';
  static const char ENDCHAR = '|';
  static const char ENDPREF = '\0';

