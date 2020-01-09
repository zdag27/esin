#include "call_registry.hpp"
/* Construeix un call_registry buit. */
/*
se uso el bst en lugar de otras structuras debido a la complegidad usada en ciertas funciones que nos parecia de manera mas eficiente con la estructura seleccionada de tal manera que se evitaba la repeticion de calculos debido a que consideramos que el costo de las multiples restructuraciones del arbol no compensaba los costes de las demas funciones que serian mas eficientes de este modo


*/
call_registry::call_registry() throw(error){
	/*
	inicializa el call registry teniendo la raiz del arbol a nulo y el numero de elementos a 0
	coste 1
	*/
	_raiz = NULL;
	num_nodes = 0;
}

/* Constructor per còpia, operador d'assignació i destructor. */
call_registry::call_registry(const call_registry& R) throw(error){
	/*
	inicializa el call registry a travez de las caracteristicas de otro pasado por parametro
	coste n
	debido a que es el coste de la funcion de asignacion 
	*/
	*this = R;
}

call_registry &call_registry::operator=(const call_registry &R) throw(error)   {
	/*
	elimina la informacion del call registry y realiza una copia de R
	posee costo 2n al ser la suma del costo de la funcion de 
	*/
	this->num_nodes = R.num_nodes;
	if(this->_raiz != R._raiz){
		borrador(this->_raiz);
		this->_raiz = copia_call(R._raiz);
	}

	return *this;
}

/* #COST LINEAL O MENOR */
/* Funció auxiliar del constructor per còpia i de l'operador d'assignació) */
call_registry::node* call_registry::copia_call(node* it){
	/*
	recorre los diferentes nodos ligados a it y retorna un node copia de los mismos
	su costo es n debido a que recursividad se realiza geometrico de parametros
	a=2
	b=2
	g(n)=1->k=0
	siendo el caso donde a > b^k
	coste = n^log b(a) 
	*/
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
	/*
	elimina los nodos atravez del borrador y coloca el contador de elementos a 0
	y posee costo n que es el costo del borrador
	*/
	borrador(_raiz);
	num_nodes=0;
}

/* Funció auxiliar del destructor */
void call_registry::borrador(node* n){
	/*
	recorre los diferentes nodos ligados a it y los elimina de los mismos
	su costo es n debido a que recursividad se realiza geometrico de parametros
	a=2
	b=2
	g(n)=1->k=0
	siendo el caso donde a > b^k
	coste = n^log b(a) 
	*/
	if (n != NULL) {
		borrador(n->izq);
		borrador(n->der);
		delete n;
	}
};

/* #COST MITJA = LOGARÍTMIC O MENOR -> ESTRUCTURES DE DADES DE TEORIA */

/* Registra que s'ha realitzat una trucada al número donat,
incrementant en 1 el comptador de trucades associat. Si el número no
estava prèviament en el call_registry afegeix una nova entrada amb
el número de telèfon donat, l'string buit com a nom i el comptador a 1. */
void call_registry::registra_trucada(nat num) throw(error){
/*
aumenta el contador de llamadas del nodo en particular que poseea el numero y en caso de que no exista se guarda uno nuevo
posee coste 
*/
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


/* Funció auxiliar de les seguents funcions "conte", "nom" i "num_trucades" */
call_registry::resp call_registry::buscar(nat num) const{
	/* PRE: it = arrel del BST */
	/* POST: Retorna un punter al node que conté un phone de numero = num.
		Si no existeix, retorna un punter al node previ i encontrado = false */
	/*
	busca el nodo con el numero dado y retorna el nodo y su anterior en caso contrario un null y el nodo anterior
	posee costo log n
	*/
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

/* Funció auxiliar registra_trucada i assigna_nom */
void call_registry::agrega(node* n, phone telf){
	/*
	realiza la insercion del phone en su lugar correspondiente
coste 1
	*/
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

/* Assigna el nom indicat al número donat.
Si el número no estava prèviament en el call_registry, s'afegeix
una nova entrada amb el número i nom donats, i el comptador
de trucades a 0.
Si el número existia prèviament, se li assigna el nom donat. */
void call_registry::assigna_nom(nat num, const string& name) throw(error){
	/*
	revisa si existe un phone que posea el numero de telefono y le coloca el nombre dado y en caso contrario lo crea y lo agrega
	posee coste n el cual seria la suma de costos de buscar y agrega
	*/
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



/* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
Es produeix un error si el número no estava present. */
void call_registry::elimina(nat num) throw(error){
	/*
	se encarga de eliminar el nodo que buscamos
	posee el costo de elimina aux la cual es n^k
	*/
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
	/*
	se encarga de realizar la busqueda del nodo y eliminarlo
	coste 
	a=1
	g(n)=h->k= h
	b=2
	siendo el caso donde a<b^k
	coste n^k
	*/
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


/* Retorna cert si i només si el call_registry conté un
telèfon amb el número donat. */
bool call_registry::conte(nat num) const throw(){
	/*
retorna un boleano que nos revela si contiene el numero o no
coste log n debido a q es el mismo q buscar
	*/
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
/*
retorna el string del numero insertado siempre y cuando exista
costo log n por que posee el costo de buscar
*/
	bool existeix = false;
	resp resultado = buscar(num);
	if(resultado.it == NULL)
		throw (error(ErrNumeroInexistent));
	return resultado.it->cell.frequencia();
}

/* Retorna cert si i només si el call_registry està buit. */
bool call_registry::es_buit() const throw(){
	/*
devuelve un boleano dando a conocer si la raiz esta vacia	
costo 1 
	*/
	
	return _raiz == NULL;
}

/* Retorna quants números de telèfon hi ha en el call_registry. */
nat call_registry::num_entrades() const throw(){
	/*
devuelve el numero de entradas que posee 
coste 1
	*/
	return num_nodes;
}



/* COST MITJA = LINEAL */
/* Fa un bolcat de totes les entrades que tenen associat un
nom no nul sobre un vector de phone.
Comprova que tots els noms dels telèfons siguin diferents{}
es produeix un error en cas contrari. */
void call_registry::dump(vector<phone>& V) const throw(error){
	/*
retorna el vector resultante de haber agregado los phones del call registry
	posee coste n por que es el valor de la funcion asociada*/
	bool existe_repetido=false;
	recnade(_raiz,V,existe_repetido);
		if(existe_repetido){
			throw(error(ErrNomRepetit));
		}
}

 void call_registry::rellena_vec(node* call,vector<phone> &v,bool &b) const{
 	/*
devuelde un vector ordenado alfabeticamente con los phones de las personas que poseea el call registry
a=2
b=2
g(n)=1->k=0
coste n
 	*/
	if(call!=NULL and !b){
		recnade(call->izq,v,b);
		if(call->cell.nom()!=""){
			if(v[v.size()-1]==call->cell.nom()){
				b=true;
			}else{
				v.push_back(call->cell);
			}
		}
		recnade(call->der,v,b);
	}
};