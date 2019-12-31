#include "call_registry.hpp"

/* Construeix un call_registry buit. */
call_registry::call_registry() throw(error){
	_raiz = NULL;
	num_nodes = 0;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
	_raiz = copia_call(R._raiz);
	num_nodes = R.num_nodes;
}

call_registry &call_registry::operator=(const call_registry &R) throw(error)   {
	if(_raiz != R._raiz){
		thanos(_raiz);
		_raiz = copia_call(R._raiz);
		num_nodes = R.num_nodes;
	}
	return *this;
}

/* #COST LINEAL O MENOR */
/* Funció auxiliar del constructor per còpia i de l'operador d'assignació) */
call_registry::node* call_registry::copia_call(node * _raiz){
	node* n;
	if (_raiz == NULL) 
		n = NULL;
	else {
		node* n = new node;
		try {
			n->cell = _raiz->cell;
			n->izq = copia_call(_raiz->izq);
			n->der = copia_call(_raiz->der);
		} catch(...) {
			delete n;
			throw;
		}
	}
	return n;
};

call_registry::~call_registry() throw(){
	thanos(_raiz);
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
	bool existeix = false;
	node* res = buscar(num);
	if(res != NULL){
		++res->cell;
	}else{
		phone a(num,"",1);
		agrega(res,a);
	}
}

/* Assigna el nom indicat al número donat.
Si el número no estava prèviament en el call_registry, s'afegeix
una nova entrada amb el número i nom donats, i el comptador 
de trucades a 0. 
Si el número existia prèviament, se li assigna el nom donat. */
void call_registry::assigna_nom(nat num, const string& name) throw(error){
	bool existeix = false;
	node* n = buscar(num);
	if(n != NULL){
		phone a(num,name,n->cell.frequencia());
		n->cell=a;
	} else {
		phone a(num,name,0);
		agrega(n,a);
	}
}

/* Funció auxiliar registra_trucada i assigna_nom */
void call_registry::agrega(node* &n, phone telf){
	if(telf.numero()<n->cell.numero()){
		node* agregar = new node;
		agregar->cell = telf;
		agregar->izq = NULL;
		agregar->der = NULL;
		n->izq = agregar;
		++num_nodes;
	} else if(telf.numero()>n->cell.numero()){
		node* agregar = new node;
		agregar->cell = telf;
		agregar->izq = NULL;
		agregar->der = NULL;
		n->der = agregar;
		++num_nodes;
	}
};

/* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
Es produeix un error si el número no estava present. */
void call_registry::elimina(nat num) throw(error){
	bool existeix = true;
	elimina_aux(_raiz, num, existeix);
	if (!existeix){
		throw(error(ErrNumeroInexistent));
	}
}

/* Auxiliar de elimina(nat num) */
call_registry::node* call_registry::elimina_aux(node* it, nat &num, bool &existeix) { 
	// Cas directe, l'element no existeix
	if (it == NULL) {
		existeix = false;
		return _raiz;
	}
  
	if (num < it->cell.numero()){
		it->izq = elimina_aux(it->izq, num, existeix); 
	} else if (num > _raiz->cell.numero()){
		it->der = elimina_aux(it->der, num, existeix); 
	} else {
	 	// Mirem si te un fill esquerra o dret 
		if (it->izq == NULL) { 
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
		it->der = elimina_aux(_raiz->der, min_num, existeix); 
	} 
	return it; 
} 

/* Funció auxiliar de les seguents funcions "conte", "nom" i  "num_trucades" */
call_registry::node* call_registry::buscar(nat num) const{
	/* PRE: it = arrel del BST */
	/* POST: Retorna un punter al node que conté un phone de numero = num.
		Si no existeix, retorna un punter al node previ i encontrado = false */
	node* res;
	node* it = this->_raiz;
	bool existeix = false;
	while(it != NULL and !existeix){
		res = it;
		if(num < it->cell.numero()){
			it = it->izq;
		} else if (num > it->cell.numero()){
			it = it->der;
		} else {
			existeix = true;
		}
	}
	if (existeix){
		res = it;
	}
	return res;
};

/* Retorna cert si i només si el call_registry conté un 
telèfon amb el número donat. */
bool call_registry::conte(nat num) const throw(){
	bool existeix = false;
	node* res = buscar(num);
	return (res != NULL);
}

/* Retorna el nom associat al número de telèfon que s'indica.
Aquest nom pot ser l'string buit si el número de telèfon no
té un nom associat. Es produeix un error si el número no està en
el call_registry. */
string call_registry::nom(nat num) const throw(error){
	bool existeix = false;
	node* res = (buscar(num));
	if(res == NULL)
		throw (error(ErrNumeroInexistent));
	return res->cell.nom();
}

/* Retorna el comptador de trucades associat al número de telèfon 
indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
aquest número. Es produeix un error si el número no està en el 
call_registry. */
nat call_registry::num_trucades(nat num) const throw(error){
	bool existeix = false;
	node* res = buscar(num);
	if(res == NULL)
		throw (error(ErrNumeroInexistent));
	return res->cell.frequencia();
}

/* Retorna cert si i només si el call_registry està buit. */
bool call_registry::es_buit() const throw(){
	return _raiz==NULL;
}

/* Retorna quants números de telèfon hi ha en el call_registry. */
nat call_registry::num_entrades() const throw(){
	return num_nodes;
}

/*
	if(_raiz==NULL) return 0;
	int x=0;
	num_nodes_aux(_raiz, x);
	return x;
}


void call_registry::num_nodes_aux(node* it,int &x){
	++x;
	if(it->izq!=NULL){
		num_nodes_aux(it->izq,x);
	}
	if(call->der!=NULL){
		num_nodes_aux(it->der,x);
	}
};
*/
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
	//quick(V, 0, V.size() - 1);
}


void call_registry::recnade(node* call,vector<phone> &v){
	if(call!=NULL){
		if(call->cell.nom()!=""){
			v.push_back(call->cell);
		}
		recnade(call->izq,v);
		recnade(call->der,v);
	}
};
/*
void quick(vector<phone>  &vec, unsigned int ini , unsigned int fini)   {
	if(fini - ini + 1 <= 1){}else{
		unsigned int aux= divi(vec, ini, fini);
		quick(vec, ini, aux - 1) ;
		quick(vec, aux + 1, fini) ;
	}
}
*/

/*
unsigned int divi(vector<phone>  & vec, unsigned int ini , unsigned int fini ){
	unsigned int auxini , aufini;
	phone aux=vec[ini];
	auxini = ini + 1;
	aufini= fini;
	while(auxini < aufini + 1) {
		while(auxini < aufini + 1 and vec[auxini].frequencia() <= aux.frequencia() )++ auxini ;
		while(auxini < aufini + 1 and vec[aufini].frequencia() >= aux.frequencia())--aufini ;
		if(auxini < aufini + 1)swap (vec[auxini], vec[aufini]);
	}
	swap(vec[ini], vec[aufini]);
	return aufini ;
}

unsigned int divi(vector<phone>  & vec, unsigned int ini , unsigned int fini ){
	unsigned int auxini , aufini;
	phone aux=vec[ini];
	auxini = ini + 1;
	aufini= fini;
	while(auxini < aufini + 1) {
		while(auxini < aufini + 1 and vec[auxini] <= aux )++ auxini ;
		while(auxini < aufini + 1 and vec[aufini] >= aux)--aufini ;
		if(auxini < aufini + 1)swap (vec[auxini], vec[aufini]);
	}
	swap(vec[ini], vec[aufini]);
	return aufini ;
}

void quick(vector<phone>  &vec, unsigned int ini , unsigned int fini)   {
	if(fini - ini + 1 <= 1){}else{
		unsigned int aux= divi(vec, ini, fini);
		quick(vec, ini, aux - 1) ;
		quick(vec, aux + 1, fini) ;
	}
}
*/