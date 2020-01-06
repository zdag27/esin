#include "easy_dial.hpp"

void easy_dial::cominginur(node * n, string pref, vector < string > & s) const {
	if (n != NULL) {
		if (pref.size() == 0) {
			cominginur(n->izq, pref, s);
			cominginur(n->cen, pref, s);
			cominginur(n->der, pref, s);
			s.push_back(n->cell.nom());
		} else if (n->cell.nom().size() >= pref.size()) {
			if (n->cell.nom().substr(0, pref.size()) == pref) {
				cominginur(n->izq, pref, s);
				cominginur(n->cen, pref, s);
				cominginur(n->der, pref, s);
				s.push_back(n->cell.nom());
			}
		}
	}
};

void easy_dial::fml(node * n, double & div, int level, double & res, bool condon) const {
	if (n != NULL) {
		res += ((double(n->cell.frequencia())) * double(level));
		div += double(n->cell.frequencia());
		fml(n->cen, div, level + 1, res, true);
		if (condon) {
			fml(n->izq, div, level + 1, res, false);
			fml(n->der, div, level + 1, res, false);
		} else {
			fml(n->izq, div, level, res, false);
			fml(n->der, div, level, res, false);
		}
	}

};

easy_dial::easy_dial(const call_registry & R) throw (error) {
	nivel = -1;
	vector < phone > v;
	R.dump(v);
	_it = NULL;
	// cout << "Esto es lo del dump: " << endl;
	if (v.size() > 0) {
		// cout << "insertando " << v[0].nom() << endl;
		_raiz = new node;
		_raiz->cell = v[v.size() - 1];
		_raiz->izq = NULL;
		_raiz->der = NULL;
		_raiz->arr = NULL;
		_raiz->cen = NULL;
		_it = _raiz;
		for (int i = v.size() - 2; i >= 0; --i) {
			node * it = _raiz;
			cout << v[i].nom() << " ";
			inserta(v[i], it, 0);
		}
	} else {
		_raiz = NULL;
	}
};

void easy_dial::inserta(phone p, node * & it, int x) {
	if (it->cell.nom()[x] == p.nom()[x]) {
		if (it->cen == NULL) {
			it->cen = new node;
			it->cen->cell = p;
			it->cen->cen = NULL;
			it->cen->izq = NULL;
			it->cen->der = NULL;
			it->cen->arr = it;
		} else {
			inserta(p, it->cen, x + 1);
		}
	} else if (it->cell.nom()[x] > p.nom()[x]) {
		if (it->izq == NULL) {
			it->izq = new node;
			it->izq->cell = p;
			it->izq->cen = NULL;
			it->izq->izq = NULL;
			it->izq->der = NULL;
			it->izq->arr = it->arr;
		} else {
			inserta(p, it->izq, x);
		}
	} else {
		if (it->der == NULL) {
			it->der = new node;
			it->der->cell = p;
			it->der->cen = NULL;
			it->der->izq = NULL;
			it->der->der = NULL;
			it->der->arr = it->arr;
		} else {
			inserta(p, it->der, x);
		}
	}
};

void easy_dial::dump(node * it) const {
	if (it != NULL) {
		dump(it->izq);
		dump(it->der);
		dump(it->cen);
		cout << it << " = " << it->cell.nom() << endl;
		cout << "izq = " << it->izq << ", der = " << it->der << ", arr = " << it->arr << ", cen = " << it->cen << endl;

	}
}

easy_dial::easy_dial(const easy_dial & D) throw (error) {
	* this = D;
};

easy_dial & easy_dial::operator = (const easy_dial & D) throw (error) {
	if (_raiz != D._raiz) {
		borrar(_raiz);
		if (D._raiz != NULL) {
			_raiz = new node;
			_raiz->izq = NULL;
			_raiz->der = NULL;
			_raiz->arr = NULL;
			_raiz->cen = NULL;
			_raiz->cell = D._raiz->cell;
			copiar(_raiz, D._raiz);
		}
	}
};
void easy_dial::copiar(easy_dial::node * rai, easy_dial::node * it) {
	if (it->izq == NULL) {
		rai->izq = NULL;
	} else {
		rai->izq = new node;
		rai->izq->arr = rai;
		rai->izq->cell = it->izq->cell;
		copiar(rai->izq, it->izq);
	}

	if (it->cen == NULL) {
		rai->cen = NULL;
	} else {
		rai->cen = new node;
		rai->cen->arr = rai;
		rai->cen->cell = it->cen->cell;
		copiar(rai->cen, it->cen);
	}

	if (it->der == NULL) {
		rai->der = NULL;
	} else {
		rai->der = new node;
		rai->der->arr = rai;
		rai->der->cell = it->der->cell;
		copiar(rai->der, it->der);
	}
};

easy_dial::~easy_dial() throw () {
	borrar(_raiz);
};

void easy_dial::borrar(node * it) {
	if (it != NULL) {
		borrar(it->izq);
		borrar(it->cen);
		borrar(it->der);
		delete it;
	}
}

string easy_dial::inici() throw () {
	nivel = 0;
	DIO = true;
	first_lateral = false;
	lateral = false;
	era_NULL = false;

	_it = _raiz;
	string nom = "";
	if (_it != NULL) {
		nom = _raiz->cell.nom();
	}
	return nom;
};

string easy_dial::seguent(char c) throw (error) {
	//error pref ind
	string nom = "";
	if (!era_NULL and _it != NULL) {
		bool trobat = false;
		bool rama_princpial = true;
		node* aux = _it;
		if (lateral) {
			rama_princpial = false;
			aux = _it->cen;
		}
		/*
		if (aux != NULL){
			cout << "Flag nivel = " << nivel << " lateral = " << lateral << " aux = " << aux << " | " << aux->cell.nom() << endl;
		}
		*/
		while (!trobat and aux != NULL) {
			//cout << "Comparando " << c << " con " << aux->cell.nom()[nivel] << " | " << aux->cell.nom() << endl;
			if (c < aux->cell.nom()[nivel]) {
				// primer desplazamiento = TRUE
				// segundo y consequentes = FALSE
				if(rama_princpial){
					first_lateral = true;
				} else {
					first_lateral = false;
				}
				lateral = true;
				aux = aux->izq;
			} else if (c > aux->cell.nom()[nivel]) {
				// primer desplazamiento = TRUE
				// segundo y consequentes = FALSE
				if(rama_princpial){
					first_lateral = true;
				} else {
					first_lateral = false;
				}
				lateral = true;
				aux = aux->der;
			} else {
				// Trobat
				if (!lateral) {
					if (aux == _it) {
						aux = aux->cen;
					}
				}
				_it = aux;
				trobat = true;
			}
		}

		if (aux == NULL) {
			if (era_NULL) {
				throw (error(ErrPrefixIndef));
			} else {
				nom = "";
				era_NULL = true;
			}
		} else if (trobat) {
			nom = aux->cell.nom();
		}
	} else {
		throw (error(ErrPrefixIndef));
	}
	++nivel;
	return nom;
};

string easy_dial::anterior() throw (error) {
	//error 33 31
	string nom = "";
	if(_it == NULL or era_NULL){
		throw(error(ErrPrefixIndef));
	}
	if(_it->arr == NULL or nivel == -1){
		throw(error(ErrNoHiHaAnterior));
	}

	if(first_lateral){
		_it = _it->arr->cen;
	} else {
		_it = _it->arr;
	}
	nom = _it->cell.nom();

	if(nivel > 0){
		--nivel;
	}
	return nom;
};

nat easy_dial::num_telf() const throw (error) {
	nat telf;
	/*
	if(nivel == -1 or era_NULL or (_raiz == NULL and nivel == -1)){
		throw(error(ErrPrefixIndef));
	}
	*/
	if 	(	(_raiz == NULL and nivel == -1) or
				(_raiz != NULL and nivel == -1) or
				(_raiz == NULL and nivel != -1 and era_NULL) or
				(_raiz != NULL and nivel == -1 and era_NULL)
			)
	{
		throw(error(ErrNoExisteixTelefon));
	}

	if 	( (_raiz == NULL and nivel != -1) or
				(_it == NULL)
			)
	{
		throw(error(ErrPrefixIndef));
	}
	/* 31:
		_raiz = NULL, init = FALSE
		_raiz != NULL, init = FALSE
		_raiz = NULL, init = TRUE, era_NULL = TRUE;
		_raiz != NULL, init FALSE, era_NULL = TRUE;
	
		32:
		_raiz = NULL, init = TRUE
	*/
	/*
	if(_it == NULL){
		throw(error(ErrNoExisteixTelefon));
	}
	if(nivel == -1 or era_NULL or (_raiz == NULL and nivel == -1) or (_it == NULL and nivel == -1)){
		throw(error(ErrPrefixIndef));
	}
	*/
	telf = _it->cell.numero();
	return telf;
};

void easy_dial::comencen(const string & pref, vector < string > & result) const throw (error) {
	node * it = _raiz;
	int i = 0;
	while (i < pref.size() and it != NULL) {
		if (it->cell.nom()[i] == pref[i]) {
			++i;
			if (i < pref.size()) {
				if (i < it->cell.nom().size()) {
					if (it->cell.nom()[i] != pref[i]) {
						--i;
						it = it->cen;
					}
				} else {
					--i;
					it = it->cen;
				}

			}
		} else if (it->cell.nom()[i] > pref[i]) {
			it = it->izq;
		} else if (it->cell.nom()[i] < pref[i]) {
			it = it->der;
		}
	}
	if (it != NULL) {
		cominginur(it, pref, result);
	}
};

double easy_dial::longitud_mitjana() const
throw () {
	double res = 0;
	double divi = 0;
	if (_raiz != NULL) {
		fml(_raiz, divi, 0, res, true);
		res = res / divi;
	}
	return res;

};