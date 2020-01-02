#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
	vector <phone> v;
	R.dump(v);
	if (v.size() > 0) {
		_raiz = new node;
		_raiz->cell = v[0];
		_raiz->izq = NULL;
		_raiz->der = NULL;
		_raiz->arr = NULL;
		_raiz->cen = NULL;
		_it=_raiz;

		for (int i=1; i<v.size(); ++i){
			inserta(v[i]);
		}
	} else {
		_raiz = NULL;
	}
};

void easy_dial::inserta(phone p){
	nivell = 0;
	node* it = _raiz;
	// esquerra = ultim node de l'esquerra visitat
	node* esquerra = NULL;
	// dreta = ultim node de la dreta que hem visitat
	node* dreta = NULL;
	node* amunt = NULL;

	// aconseguim el nom del phone que estem insertant i afegim un caracter "#" al final 
	string nom = p.nom() + "#";
	int nivell = 0;
	bool trobat = false;
	// Invariant: trobat es fals mentre no arribem a on s'ha de crear el nou node
	while(!trobat){
		// if = hem trobat a on va el node, finalitzem
		// else = queden més desplaçaments, actualitzem it_anterior
		if (it == NULL){
			trobat = true;
		} else {
			// Moure it
			char lletra_phone = nom[nivell];
			char lletra_arbre = it->cell.nom()[nivell];
			if (lletra_phone == lletra_arbre){
				++nivell;
				amunt = it;
				esquerra = NULL;
				dreta = NULL;
				it = it->cen;
			} else if (lletra_phone < lletra_arbre){
				esquerra = it;
				it = it->izq;
			} else {
				dreta = it;
				it = it->der;
			}
			++nivell;
		}

	} // fi while

	it = new node;
	it->cell = p;
	if (esquerra != NULL) {
		esquerra->izq = it;
	}
	if (dreta != NULL) {
		dreta->der = it;
	}
	if (amunt != NULL){
		it->arr = amunt;
		if (amunt->cen == NULL){
			amunt->cen = it;
		}
	}
	it->cen = NULL;
};

easy_dial::easy_dial(const easy_dial& D) throw(error){
	*this = D;
};

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
	if(_raiz != D._raiz){
		borrar(_raiz);
		if(D._raiz!=NULL){
			_raiz=new node;
			_raiz->izq=NULL;
			_raiz->der=NULL;
			_raiz->arr=NULL;
			_raiz->cen=NULL;
			_raiz->cell=D._raiz->cell;
			copiar(_raiz,D._raiz);
		}
	}
};
void easy_dial::copiar(easy_dial::node* rai,easy_dial::node *it){
	if(it->izq==NULL){
		rai->izq=NULL;
	}else{
		rai->izq=new node;
		rai->izq->arr=rai;
		rai->izq->cell=it->izq->cell;
		copiar(rai->izq,it->izq);
	}

	if(it->cen==NULL){
		rai->cen=NULL;
	}else{
		rai->cen=new node;
		rai->cen->arr=rai;
		rai->cen->cell=it->cen->cell;
		copiar(rai->cen,it->cen);
	}
	
	if(it->der==NULL){
		rai->der=NULL;
	}else{
		rai->der=new node;
		rai->der->arr=rai;
		rai->der->cell=it->der->cell;
		copiar(rai->der,it->der);
	}
};

easy_dial::~easy_dial() throw(){
	borrar(_raiz);
};

void easy_dial::borrar(node *it){
	if (it != NULL){
		borrar(it->izq);
		borrar(it->cen);
		borrar(it->der);
		delete it;
	}
}

string easy_dial::inici() throw(){
	this->nivel = 0;
	_it = _raiz;
	string nom = "";
	if (_it != NULL) {
		nom = _raiz->cell.nom();
	}
	return nom;
};

string easy_dial::seguent(char c) throw(error){
	if (_it != NULL){
		node* aux = _it->cen;
		if(aux != NULL){
			++nivel;
			bool trobat = false;
			while(!trobat){
				if (aux != NULL){
					throw (error(ErrPrefixIndef));
				} else {
					if (c ==aux->cell.nom()[nivel]){
						_it = aux;
						trobat = true;
					} else if (c < aux->cell.nom()[nivel]) {
						aux = aux->izq;
					} else {
						aux = aux->der;
					}
				}
			} 
		} else {
			throw (error(ErrPrefixIndef));
		}
	} else {
		throw (error(ErrPrefixIndef));		
	}
	return(_it->cell.nom());				
	
	/*
	arb *auxi=_it->cen;
	busc(auxi,c);
	if(auxi==NULL){
		throw (error(ErrPrefixIndef));
	}else{
		_it=auxi;
		return(_it->cell.nom());
	}
	*/
};

string easy_dial::anterior() throw(error){
	if (_it != NULL){
		if(_it->arr==NULL){
			throw (error(ErrNoHiHaAnterior));
		}else{
			_it = _it->arr;
			--nivel;
			return(_it->cell.nom());
		}
	} else {
		throw (error(ErrPrefixIndef));		
	}
};

nat easy_dial::num_telf() const throw(error){
	nat tel = 0;
	if(_it != NULL){
		tel = _it->cell.numero();
	} else if (_it == NULL and _raiz != NULL) {
		throw (error(ErrNoExisteixTelefon));
	} else {
		throw (error(ErrPrefixIndef));
	}
	return tel;
};

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
	/*
	arb* it=this->_raiz;
	busca(it, pref);
	if(it==NULL){
		throw(error(ErrPrefixIndef));
	}else{
		add(it,result);
	}
	*/
};

double easy_dial::longitud_mitjana() const throw(){

};
/*
void easy_dial::inserta(phone s,int i,arb* &it){
	bool b=true;
	while(b){
		if(i<s.nom().size()){
			if(it->cen!=NULL){
				if(s.nom()[i]==it->cen->car){
					++i;
					it=it->cen;
				}else if(s.nom()[i]>it->cen->car){
					if(it->cen->der==NULL){
						it->cen->der->car=s.nom()[i];
						it->cen->der->cell=s;
						it->cen->der->izq=NULL;
						it->cen->der->der=NULL;
						it->cen->der->cen=NULL;
						it->cen->der->arr=it;
						b=false;
					}else{
						it=it->cen->der;
					}
				}else{
					if(it->cen->izq==NULL){
						it->cen->izq->car=s.nom()[i];
						it->cen->izq->cell=s;
						it->cen->izq->izq=NULL;
						it->cen->izq->der=NULL;
						it->cen->izq->cen=NULL;
						it->cen->izq->arr=it;
						b=false;
					}else{
						it=it->cen->izq;
					}
				}
			}else{
				it->cen=new arb;
				it->cen->car=s.nom()[i];
				it->cen->cell=s;
				it->cen->izq=NULL;
				it->cen->der=NULL;
				it->cen->cen=NULL;
				it->cen->arr=it;
				b=false;
			}
		}else{
			if(it->cen==NULL){
				it->cen=new arb;
				it->cen->car='#';
				it->cen->cell=s;
				it->cen->izq=NULL;
				it->cen->der=NULL;
				it->cen->cen=NULL;
				it->cen->arr=it;
				b=false;
			}else{
				arb *auxi =it->cen;
				while(auxi->izq!=NULL){
					auxi=auxi->izq;
				}
				auxi->izq=new arb;
				auxi->izq->car='#';
				auxi->izq->cell=s;
				auxi->izq->izq=NULL;
				auxi->izq->der=NULL;
				auxi->izq->cen=NULL;
				auxi->izq->arr=it;
			}
			b=false;
		}
	}
};

void easy_dial::add(arb *it,vector<string>&s)const{
	if(it!=NULL){
		add(it->izq,s);
		add(it->cen,s);
		add(it->der,s);
		s.push_back(it->cell.nom());
	}
};

void easy_dial::copiar(easy_dial::arb* rai,easy_dial::arb *it){
	if(it->izq==NULL){
		rai->izq=NULL;
	}else{
		rai->izq=new arb;
		rai->izq->arr=rai;
		rai->izq->car=it->izq->car;
		rai->izq->cell=it->izq->cell;
		copiar(rai->izq,it->izq);
	}

	if(it->cen==NULL){
		rai->cen=NULL;
	}else{
		rai->cen=new arb;
		rai->cen->arr=rai;
		rai->cen->car=it->cen->car;
		rai->cen->cell=it->cen->cell;
		copiar(rai->cen,it->cen);
	}
	
	if(it->der==NULL){
		rai->der=NULL;
	}else{
		rai->der=new arb;
		rai->der->arr=rai;
		rai->der->car=it->der->car;
		rai->der->cell=it->der->cell;
		copiar(rai->der,it->der);
	}
};

void easy_dial::busc(arb* &it,char s){
	if(it!=NULL){
		if(!it->car==s){
			if(it->car>s){
				it=it->izq;
				busc(it,s);
			}else{
				it=it->der;
				busc(it,s);
			}
		}
	}
};

void easy_dial::busca(arb* it,string s)const {
	int i = 0;
	while(i < s.size() and it != NULL){
		if(it != NULL){
			if(s[i] == it->car){
				it = it->cen;
				++i;
			} else if (s[i] < it->car){
				it = it->izq;
			} else {
				it = it->der;
			}
		}
	}
};

int easy_dial::conver(char letra){
	if ('A' <= letra < 'a'){
		return int(letra)-int('A');
	}
	else if ('a' <= letra <= 'z'){
		return int(letra)-int('a');
	}
};

easy_dial::arb* easy_dial::node_hashtag(const phone &p){
	arb *it=new arb;
	it->car=('#');
	it->izq=NULL;
	it->der=NULL;
	it->cen=NULL;
	it->cell=p;
	return it;
};

void easy_dial::fori(phone s,int i,arb* it){
	for(int x=i;x<s.nom().size();++x){
		it->cen=new arb;
		it=it->cen;
		it->car=s.nom()[x];
		it->izq=NULL;
		it->der=NULL;
		it->cen=NULL;
	}
	it->cen=node_hashtag(s);
};
*/