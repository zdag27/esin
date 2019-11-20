#include "call_registry.hpp"

typename Abin<phone>::node* Abin<phone>::copia_nodes(node* m) {
/* Pre: cert */
/* Post: si m és NULL, el resultat és NULL; sinó,
	 el resultat apunta al primer node d'un arbre binari
	 de nodes que són còpia de l'arbre apuntat per m */
	node* n;
	if (m == NULL) n = NULL;
	else {
		n = new node;
		try {
			n->info = m->info;
			n->f_esq = copia_nodes(m->f_esq);
			n->f_dret = copia_nodes(m->f_dret);
		} catch(...) {
			delete n;
			throw;
		}
	}
	return n;
};

template <typename T>
void Abin<T>::esborra_nodes(node* m) {
/* Pre: cert */
/* Post: no fa res si m és NULL, sinó allibera
	 espai dels nodes de l'arbre binari apuntat per m */
	if (m != NULL) {
		esborra_nodes(m->f_esq);
		esborra_nodes(m->f_dret);
		delete m;
	}
};

Abin<phone>::Abin(Abin<phone>& ae, const phone& x, Abin<phone>& ad) {
/* Pre: cert */
/* Post: el resultat és un arbre amb x com arrel, ae com a fill
esquerre i ad com a fill dret. No fa còpia dels arbres ae i ad */
	_arrel = new node;
	try {
		_arrel->info = x;
	}
	catch (...) {
		delete _arrel;
		throw;
	}
	_arrel->f_esq = ae._arrel;
	ae._arrel = NULL;
	_arrel->f_dret = ad._arrel;
	ad._arrel = NULL;
}

Abin<phone>::Abin(const Abin<phone> &a) {
	_arrel = copia_nodes(a._arrel);
};

Abin<phone>::~Abin() {
	esborra_nodes(_arrel);
};

Abin<phone>& Abin<phone>::operator=(const Abin<phone>& a) {
	if (this != &a) {
		node* aux;
		aux = copia_nodes(a._arrel);
		esborra_nodes(_arrel);
		_arrel = aux;
	}
	return (*this);
};


bool Abin<phone>::es_buit() const {
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
	return (_arrel == NULL);
};

typename Abin<phone>::iterador Abin<phone>::arrel() const {
/* Pre: cert */
/* Post: Retorna un iterador al node arrel. */
	iterador it;
	it._p = _arrel;
	return it;
};

typename Abin<phone>::iterador Abin<phone>::final() const{
/* Pre: cert */
/* Post: Retorna un iterador no vàlid. */
	return iterador();
};

Abin<phone> Abin<phone>::iterador::arbre() const {
/* Pre: cert */
/* Post: Retorna el subarbre al que apunta l'iterador; llança un error
si l'iterador no és vàlid. */
	if (_p == NULL)
		throw IteradorInvalid;
	Abin<phone> a;
	a._arrel = copia_nodes(_p);;
	return a;
};

T Abin<T>::iterador::operator*() const {
/* Pre: cert */
/* Post: Retorna l'element en el node al que apunta l'iterador, o
llança un error si l'iterador no és vàlid. */
	if (_p == NULL)
		throw IteradorInvalid;
	return _p->info;
};

typename Abin<phone>::iterador Abin<phone>::iterador::fesq() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill esquerre; llança
un error si l'iterador no és vàlid. */
	if (_p == NULL) 
		throw IteradorInvalid;
	iterador it;
	it._p = _p->f_esq;
	return it;
};

template <typename T>
typename Abin<phone>::iterador Abin<phone>::iterador::fdret() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill dret; llança
un error si l'iterador no és vàlid. */
	if (_p == NULL) 
		throw IteradorInvalid;
	iterador it;
	it._p = _p->f_dret;
	return it;
};

bool Abin <phone>::abin_buscar(Abin<phone> &a, Abin<phone>::iterador it, int &buscar){
	while(it != a.final()){
		if(buscar == *it){
			return true;
		} else if (buscar < *it){
			it = it.fesq();
		} else {
			it = it.fdret();
		}
	}
	return false;
}

    void Abin<phone>::crea(phone x) {
        creabts(_arrel,x);
    }

    typename Abin<phone>::node * Abin<phone>::creabts(node* m,phone x){
        if(x.numero()<m->info.numero()){
            if(m->f_esq==NULL){
                node* n=new node;
                n->f_esq=NULL;
                n->f_dret=NULL;
                n->info=x;
                m->f_esq=n;
            }else{
                creabts(m->f_esq,x);
            }
        }else if(x.numero()>m->info.numero()){
            if(m->f_dret==NULL){
                node* n=new node;
                n->f_esq=NULL;
                n->f_dret=NULL;
                n->info=x;
                m->f_dret=n;
            }else{
                creabts(m->f_dret,x);
            }
        }
    }
    
    void Abin<phone>::elimi(nat x,Abin<phone> &a){
        Abin<phone>::iterator:: it;
        if(a.arrel()!=it){
            if(*a.arrel().numero!= x){
                a.crea(*a.arrel);
            }
            elimi(x,a.fesq().arbre);
            elimi(x,a.fdret().arbre);
        }
    }
    
     void Abin<phone>::busca(Abin<phone>::iterator::it,nat num,phone &res){
        Abin<phone>::iterator::mal;
        if(!it==mal and res.nom!=""){
            if(*it.numero()==num){res=*it}
            else if(*it.numero()<num){
                busca(it.fdret().arbre(),num,s);
            }else{busca(it.fdret().arbre(),num,s)}
        }
    }
    void Abin<phone>::tamaño(Abin::iterator it,int x){
        
    }

/* COST LINEAL O MENOR */

  /* Construeix un call_registry buit. */
  call_registry::call_registry() _regg(NULL) throw(error){ }
 
  /* Constructor per còpia, operador d'assignació i destructor. */
  call_registry::call_registry(const call_registry& R) throw(error){
  		_regg=R->_regg;
  }
  call_registry::call_registry& operator=(const call_registry& R) throw(error){
  		delete _regg->_arrel;
  		_regg->_arrel =copia_nodes(R->_regg->_arrel);
  }
  call_registry::~call_registry() throw(){
		delete _regg;
  }


/* COST MITJA = LOGARÍTMIC O MENOR -> ESTRUCTURES DE DADES DE TEORIA */
/* !TAULES DE DISPERSIÓ! */
/* EXPLICAR PERQUÈ ESTRUCTURA I NO ALTRES */

  /* Registra que s'ha realitzat una trucada al número donat, 
  incrementant en 1 el comptador de trucades associat. Si el número no 
  estava prèviament en el call_registry afegeix una nova entrada amb 
  el número de telèfon donat, l'string buit com a nom i el comptador a 1. */
  void call_registry::registra_trucada(nat num) throw(error){

  }

  /* Assigna el nom indicat al número donat.
  Si el número no estava prèviament en el call_registry, s'afegeix
  una nova entrada amb el número i nom donats, i el comptador 
  de trucades a 0. 
  Si el número existia prèviament, se li assigna el nom donat. */
  void call_registry::assigna_nom(nat num, const string& name) throw(error){
  	// Crear nou objecte amb el nou nom -> PREGUNTA DEL FORUM
  	try{

  	} catch(...) {
  		throw()
  	}
  }

  /* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
  Es produeix un error si el número no estava present. */
  void call_registry::elimina(nat num) throw(error){
  	if(conte(num)){
  	    Abin <phone> a;
  	    _regg.elimi(num,a);
  	}else{
  	    throw(ErrNumeroInexistentv )
  	}
  }

  /* Retorna cert si i només si el call_registry conté un 
  telèfon amb el número donat. */
  bool call_registry::conte(nat num) const throw(){
  		Abin<phone>::iterador it(_regg.arrel());
  		return (_regg.abin_buscar(_regg, it, int(num)));
  }


  /* Retorna el nom associat al número de telèfon que s'indica.
  Aquest nom pot ser l'string buit si el número de telèfon no
  té un nom associat. Es produeix un error si el número no està en
  el call_registry. */
  string call_registry::nom(nat num) const throw(error){
    phone res();
    busca(_regg.arrel(),num,res);
    if(res.nom()=="") throw (ErrNumeroInexistentv)
    return res.nom();
  }

  /* Retorna el comptador de trucades associat al número de telèfon 
  indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
  aquest número. Es produeix un error si el número no està en el 
  call_registry. */
  nat call_registry::num_trucades(nat num) const throw(error){
    phone res();
    busca(_regg.arrel(),num,res);
    if(res==phone a()) throw (ErrNumeroInexistentv)
    return res.frequencia();
  }

  /* Retorna cert si i només si el call_registry està buit. */
  bool call_registry::es_buit() const throw(){
    return _regg==NULL
  }

  /* Retorna quants números de telèfon hi ha en el call_registry. */
  nat call_registry::num_entrades() const throw(){
    x=0;
    Abin<phone>::iterator it=_regg->_arrel;
    _regg.tamaño(it, x)
    return x;
  }

  /* COST MITJA = LINEAL */
  /* Fa un bolcat de totes les entrades que tenen associat un
  nom no nul sobre un vector de phone.
  Comprova que tots els noms dels telèfons siguin diferents{} 
  es produeix un error en cas contrari. */
  void call_registry::dump(vector<phone>& V) const throw(error){
  	// NOMES TELEFONS AMB NOM

  	/*
  	Phone registry pot tenir noms repetits, NO HI PODEN HAVER NUMEROS REPETITS
  	PERO DUMP NO: try{} catch throw(ErrNomRepetit)

  }
