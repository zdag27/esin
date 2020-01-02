#include "call_registry.hpp"
/* Construeix un call_registry buit. */
call_registry::call_registry() throw(error){
	_raiz = NULL;
	num_nodes = 0;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
	*this = R;
}

call_registry &call_registry::operator=(const call_registry &R) throw(error)   {
	this->num_nodes = R.num_nodes;
	if(this->_raiz != R._raiz){
		thanos(this->_raiz);
		this->_raiz = copia_call(R._raiz);
	}

	return *this;
}

/* #COST LINEAL O MENOR */
/* Funció auxiliar del constructor per còpia i de l'operador d'assignació) */
call_registry::node* call_registry::copia_call(node* it){
	node* n;
	if (it == NULL){
		n = NULL;
	} else {
		n = new node;
		n->cell = it->cell;
		n->izq = copia_call(it->izq);
		n->der = copia_call(it->der);
	}
	return n;
};

call_registry::~call_registry() throw(){
	thanos(_raiz);
	num_nodes=0;
}

/* Funció auxiliar del destructor */
void call_registry::thanos(node* n){
	if (n != NULL) {
		thanos(n->izq);
		thanos(n->der);
		delete n;
	}
};

/* #COST MITJA = LOGARÍTMIC O MENOR -> ESTRUCTURES DE DADES DE TEORIA */

/* Registra que s'ha realitzat una trucada al número donat,
incrementant en 1 el comptador de trucades associat. Si el número no
estava prèviament en el call_registry afegeix una nova entrada amb
el número de telèfon donat, l'string buit com a nom i el comptador a 1. */
void call_registry::registra_trucada(nat num) throw(error){
	if (_raiz != NULL){
		bool existeix = false;
		resp resultado = buscar(num);
		if(resultado.it != NULL){
			++resultado.it->cell;
		}else{
			phone a(num,"",1);
			agrega(resultado.it_anterior, a);
		}
	} else {
		_raiz = new node;
		phone a(num,"",1);
		_raiz->cell = a;
		_raiz->izq = NULL;
		_raiz->der = NULL;
		++num_nodes;
	}
}

/* Assigna el nom indicat al número donat.
Si el número no estava prèviament en el call_registry, s'afegeix
una nova entrada amb el número i nom donats, i el comptador
de trucades a 0.
Si el número existia prèviament, se li assigna el nom donat. */
void call_registry::assigna_nom(nat num, const string& name) throw(error){
	if (_raiz != NULL)
	{
		bool existeix = false;
		resp resultado = buscar(num);
		if(resultado.it != NULL){
			phone a(num,name,resultado.it->cell.frequencia());
			resultado.it->cell=a;
		} else {
			phone a(num,name,0);
			node* agregar_en = resultado.it_anterior;
			agrega(agregar_en, a);
		}
	} else {
		_raiz = new node;
		phone a(num,name,0);
		_raiz->cell = a;
		_raiz->izq = NULL;
		_raiz->der = NULL;
		++num_nodes;
	}
}

/* Funció auxiliar registra_trucada i assigna_nom */
void call_registry::agrega(node* n, phone telf){
	if(telf.numero()<n->cell.numero()){
		node* nuevo = new node;
		nuevo->cell = telf;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		n->izq = nuevo;
		++num_nodes;
	} else if(telf.numero()>n->cell.numero()){
		node* nuevo = new node;
		nuevo->cell = telf;
		nuevo->izq = NULL;
		nuevo->der = NULL;
		n->der = nuevo;
		++num_nodes;
	}
};

/* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
Es produeix un error si el número no estava present. */
void call_registry::elimina(nat num) throw(error){
	bool existeix = true;
	//cout << "gonna delete node " << num << endl;
	_raiz = elimina_aux(_raiz, num, existeix);
	if (!existeix){
		throw(error(ErrNumeroInexistent));
	}else{
		--num_nodes;
	}
}

/* Auxiliar de elimina(nat num) */
call_registry::node* call_registry::elimina_aux(node* it, nat &num, bool &existeix) {
	// Cas directe, l'element no existeix
	if (it == NULL) {
		existeix = false;
		return it;
	}

	if (num < it->cell.numero()){
		// cout << it->cell.numero() << " no era, me voy a la izquierda" << endl;
		it->izq = elimina_aux(it->izq, num, existeix);
	} else if (num > it->cell.numero()){
		// cout << it->cell.numero() << " no era, me voy a la derecha" << endl;
		it->der = elimina_aux(it->der, num, existeix);
	} else {
		// Mirem si te un fill esquerra o dret
		if (it->izq == NULL) {
			// cout << "Gonna delete node " << it->cell.numero() << endl;
			node *aux = it->der;
			delete it;
			return aux;
		} else if (it->der == NULL) {
			node *aux = it->izq;
			delete it;
			return aux;
		}

		// Si el que hem d'esborrar té dos fills, trobem el fill més petit de la branca dreta
		node* min = it->der;
		while (min->izq != NULL){
			min = min->izq;
		}
		// Copiem la informació del fill més petit a la posició de "l'arrel" (recursivitat fa que "arrel" = node que hem d'eliminar)
		it->cell = min->cell;

		/* Fem la crida per esborrar el node corresponen a mínim.
		No podem fer un esborrament directe perquè pot ser el cas qué el node
		a esborrar té un fill dret */
		nat min_num = min->cell.numero();
		it->der = elimina_aux(it->der, min_num, existeix);
	}
	return it;
}

/* Funció auxiliar de les seguents funcions "conte", "nom" i "num_trucades" */
call_registry::resp call_registry::buscar(nat num) const{
	/* PRE: it = arrel del BST */
	/* POST: Retorna un punter al node que conté un phone de numero = num.
		Si no existeix, retorna un punter al node previ i encontrado = false */
	resp resultado;
	node* it = this->_raiz;
	bool existeix = false;
	while(it != NULL and !existeix){
		resultado.it_anterior = it;
		if(num < it->cell.numero()){
			it = it->izq;
		} else if (num > it->cell.numero()){
			it = it->der;
		} else {
			existeix = true;
		}
	}

	if (existeix){
		resultado.it = it;
	} else {
		resultado.it = NULL;
	}

	return resultado;
};

/* Retorna cert si i només si el call_registry conté un
telèfon amb el número donat. */
bool call_registry::conte(nat num) const throw(){
	resp resultado = buscar(num);
	return (resultado.it != NULL);
}

/* Retorna el nom associat al número de telèfon que s'indica.
Aquest nom pot ser l'string buit si el número de telèfon no
té un nom associat. Es produeix un error si el número no està en
el call_registry. */
string call_registry::nom(nat num) const throw(error){
	bool existeix = false;
	resp resultado = buscar(num);
	if(resultado.it == NULL)
		throw (error(ErrNumeroInexistent));
	return resultado.it->cell.nom();
}

/* Retorna el comptador de trucades associat al número de telèfon
indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
aquest número. Es produeix un error si el número no està en el
call_registry. */
nat call_registry::num_trucades(nat num) const throw(error){
	bool existeix = false;
	resp resultado = buscar(num);
	if(resultado.it == NULL)
		throw (error(ErrNumeroInexistent));
	return resultado.it->cell.frequencia();
}

/* Retorna cert si i només si el call_registry està buit. */
bool call_registry::es_buit() const throw(){
	return _raiz == NULL;
}

/* Retorna quants números de telèfon hi ha en el call_registry. */
nat call_registry::num_entrades() const throw(){
	return num_nodes;
}


 void call_registry::recnade(node* call,vector<phone> &v) const{
	if(call!=NULL){
		if(call->cell.nom()!=""){
			v.push_back(call->cell);
		}
		recnade(call->izq,v);
		recnade(call->der,v);
	}
};


void call_registry::margaux(vector<phone> &vec, int ini, int auxi, int fini) const{
	int tam1 = auxi - ini + 1;
	int tam2 =  fini - auxi;
	vector <phone> vec1(tam1);
	vector <phone> vec2(tam2);
	for (int i = 0; i < tam1; i++)vec1[i] = vec[ini + i];
	for (int i = 0; i < tam2; i++)vec2[i] = vec[auxi + 1+ i];
	int i = 0,j = i,k = ini;
	while (i < tam1 && j < tam2){
		if (vec1[i].frequencia() <= vec2[j].frequencia()){
			vec[k] = vec1[i];
			i++;
		}else{
			vec[k] = vec2[j];
			j++;
		}
		k++;
	}
	while (i < tam1){
		vec[k] = vec1[i];
		i++;
		k++;
	}
	while (j < tam2){
		vec[k] = vec2[j];
		j++;
		k++;
	}
}

void call_registry::marga(vector<phone> &vec, int ini, int fini) const{
	if (ini < fini){
		int aux = ini+(fini-ini)/2;
		marga(vec, ini, aux);
		marga(vec, aux+1, fini);
		margaux(vec, ini, aux, fini);
	}
}


/* COST MITJA = LINEAL */
/* Fa un bolcat de totes les entrades que tenen associat un
nom no nul sobre un vector de phone.
Comprova que tots els noms dels telèfons siguin diferents{}
es produeix un error en cas contrari. */
void call_registry::dump(vector<phone>& V) const throw(error){
	recnade(_raiz,V);
	for(int i=0;i<V.size();++i){
		for(int j=0;j<V.size();++j){
			if(i!=j and V[i].nom()==V[j].nom()){
				throw(error(ErrNomRepetit));
			}
		}
	}
	unsigned int x=V.size()-1;
	marga(V,0,x);
}



