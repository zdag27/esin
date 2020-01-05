#include "easy_dial.hpp"

void easy_dial::fml(node *n, int div, int level, double &res,bool condon)const{
		if(n!=NULL){
				res+=((double(n->cell.frequencia())/double(divi))*double(level));
				fml(n->cen,div,level+1,res,true);
				if(condon){
						fml(n->izq,div,level+1,res,false);
						fml(n->der,div,level+1,res,false);
				}else{
						fml(n->izq,div,level,res,false);
						fml(n->der,div,level,res,false);
				}
		}


};

void easy_dial::buscahavueltomalditoesinmatable(node* it,vector<string>& s,bool b,int alberto)const{
		if(it!=NULL){
				if(it->izq!=NULL){
						if(it->izq->cell.nom()[alberto]==it->cell.nom()[alberto] or b)
						buscahavueltomalditoesinmatable(it->izq,s,b,alberto);
				}
				if(it->cen!=NULL){
						if(it->cen->cell.nom()[alberto]==it->cell.nom()[alberto] or b)
								buscahavueltomalditoesinmatable(it->cen,s,b,alberto);
				}
				if(it->der!=NULL){
						if(it->der->cell.nom()[alberto]==it->cell.nom()[alberto] or b)
								buscahavueltomalditoesinmatable(it->der,s,b,alberto);
				}
				s.push_back(it->cell.nom());
		}
};

easy_dial::easy_dial(const call_registry& R) throw(error){
	vector <phone> v;
	R.dump(v);
	this->prefix_size = 1;
	for (int i = 0; i < this->prefix_size; ++i){
		cout << this->prefix[i] << endl;
	}
	// cout << "Esto es lo del dump: " << endl;
	if (v.size() > 0) {
		// cout << "insertando " << v[0].nom() << endl;
		_raiz = new node;
		_raiz->cell = v[v.size()-1];
		_raiz->izq = NULL;
		_raiz->der = NULL;
		_raiz->arr = NULL;
		_raiz->cen = NULL;
		_it=_raiz;
		divi=v[v.size()-1].frequencia();
		for (int i=v.size()-2; i>=0; --i){
			// cout << "insertando " << v[i].nom() << endl;
			inserta(v[i]);
			divi+=v[i].frequencia();
		}
	} else {
			_raiz = NULL;
			divi=0;
	}
};

void easy_dial::inserta(phone p){
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
			char lletra_arbre;
			// Cas: node conté una paraula a
			if (it->cell.nom().size() == nivell){
				lletra_arbre = '#';
			} else {
				lletra_arbre = it->cell.nom()[nivell];
			}
			//cout << "comparando " << nom << " con " << it->cell.nom() << endl;
			if (lletra_phone == lletra_arbre){
				//cout << nom << "bajó por " << it->cell.nom() << endl;
				++nivell;
				amunt = it;
				esquerra = NULL;
				dreta = NULL;
				it = it->cen;
			} else if (lletra_phone < lletra_arbre){
				//cout << nom << "se fue a la izquierda de " << it->cell.nom() << endl;
				esquerra = it;
				it = it->izq;
			} else {
				//cout << nom << "se fue a la derecha de " << it->cell.nom() << endl;
				dreta = it;
				it = it->der;
			}
		}
	} // fi while
	/*
	cout << "Entrando en dump" << endl;
	dump(_raiz);
	cout << "Salí de dump*" << endl;
	*/
	it = new node;
	it->cell = p;

	if (esquerra != NULL)
		esquerra->izq = it;
	it->izq = NULL;

	if (dreta != NULL)
		dreta->der = it;
	it->der = NULL;

	if (amunt != NULL){
		it->arr = amunt;
		if (amunt->cen == NULL){
				amunt->cen = it;
		}
	} else {
		it->arr = NULL;
	}
	it->cen = NULL;

	/*
	if (dreta != NULL){
		cout << "DRETA = " << dreta->izq << ", " << dreta->der << ", " << dreta->arr << ", " << dreta->cen << endl;
	} else if (esquerra != NULL) {
		cout << "ESQUERRA = " << esquerra->izq << ", " << esquerra->der << ", " << esquerra->arr << ", " << esquerra->cen << endl;
	}
	cout << "IT = " << it->izq << ", " << it->der << ", " << it->arr << ", " << it->cen << endl;
	cout << "Entrando en dump" << endl;
	dump(_raiz);
	cout << "Salí de dump*" << endl;
	*/

};

void easy_dial::dump(node* it) const{
	if(it != NULL){
		dump(it->izq);
		dump(it->der);
		dump(it->cen);
		cout << it << " = " << it->cell.nom() << endl;
		cout << "izq = " << it->izq << ", der = " << it->der << ", arr = " << it->arr << ", cen = " << it->cen << endl;
	}
}
easy_dial::easy_dial(const easy_dial& D) throw(error){
	*this = D;
};

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
	if(_raiz != D._raiz){
		borrar(_raiz);
		divi=0;
		if(D._raiz!=NULL){
			_raiz=new node;
			_raiz->izq=NULL;
			_raiz->der=NULL;
			_raiz->arr=NULL;
			_raiz->cen=NULL;
			_raiz->cell=D._raiz->cell;
			copiar(_raiz,D._raiz);
			divi=D.divi;
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
	if(!init){
		this->init = !this->init;
	} // init = true
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
	if(!init){
		throw (error(ErrPrefixIndef));
	} else if (_it == NULL) {
		throw (error(ErrNoExisteixTelefon));
	} else {
		tel = _it->cell.numero();
	}
	return tel;
};

void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
	node* it=_raiz;
	int i=0;
	while(i<pref.size() and it!=NULL){
		if(it->cell.nom()[i]==pref[i]){
			++i;
			if(i<pref.size()){
				if(i<it->cell.nom().size()){
					if(it->cell.nom()[i]!=pref[i]){
						--i;
						it=it->cen;
					}
				}else{
					--i;
					it=it->cen;
				}
			}
		}else if(it->cell.nom()[i]>pref[i]){
			it=it->izq;
		}else if(it->cell.nom()[i]<pref[i]){
			it=it->der;
		}
	}
	if(it!=NULL){
		if(i==0)
			buscahavueltomalditoesinmatable(it,result,true,0);
		else{
			result.push_back(it->cell.nom());
			buscahavueltomalditoesinmatable(it->cen,result,false,pref.size()-1);
		}
	}
};

double easy_dial::longitud_mitjana() const throw(){
	double res=0;
	if(divi!=0) {
		fml(_raiz, divi,0, res,true);
	}
	double x=1.33333;
	cout<<x<<endl;
	return res;
};
