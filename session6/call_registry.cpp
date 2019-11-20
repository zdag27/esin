#include "call_registry.hpp"

Abin::node* Abin::copia_nodes(node* m) {
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
void Abin::esborra_nodes(node* m) {
/* Pre: cert */
/* Post: no fa res si m és NULL, sinó allibera
	 espai dels nodes de l'arbre binari apuntat per m */
	if (m != NULL) {
		esborra_nodes(m->f_esq);
		esborra_nodes(m->f_dret);
		delete m;
	}
};

Abin::Abin(Abin& ae, const phone& x, Abin& ad) {
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

Abin::Abin(const Abin&a) {
	_arrel = copia_nodes(a._arrel);
};

Abin::~Abin() {
	esborra_nodes(_arrel);
};

Abin& Abin:: operator=(const Abin& a) {
	if (this != &a) {
		node* aux;
		aux = copia_nodes(a._arrel);
		esborra_nodes(_arrel);
		_arrel = aux;
	}
	return (*this);
};


bool Abin::es_buit() const {
/* Pre: cert */
/* Post: el resultat indica si el p.i. és buit o no */
	return (_arrel == NULL);
};

typename Abin::iterador Abin::arrel() const {
/* Pre: cert */
/* Post: Retorna un iterador al node arrel. */
	iterador it;
	it._p = _arrel;
	return it;
};

typename Abin::iterador Abin::final() const{
/* Pre: cert */
/* Post: Retorna un iterador no vàlid. */
	return iterador();
};

Abin Abin::iterador::arbre() const {
/* Pre: cert */
/* Post: Retorna el subarbre al que apunta l'iterador; llança un error
si l'iterador no és vàlid. */
	if (_p == NULL)
		throw IteradorInvalid;
	Abin a;
	a._arrel = copia_nodes(_p);;
	return a;
};

phone Abin::iterador::operator*() const {
/* Pre: cert */
/* Post: Retorna l'element en el node al que apunta l'iterador, o
llança un error si l'iterador no és vàlid. */
	if (_p == NULL)
		throw IteradorInvalid;
	return _p->info;
};

typename Abin::iterador Abin::iterador::fesq() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill esquerre; llança
un error si l'iterador no és vàlid. */
	if (_p == NULL) 
		throw IteradorInvalid;
	iterador it;
	it._p = _p->f_esq;
	return it;
};

typename Abin::iterador Abin::iterador::fdret() const {
/* Pre: cert */
/* Post: Retorna un iterador al fill dret; llança
un error si l'iterador no és vàlid. */
	if (_p == NULL) 
		throw IteradorInvalid;
	iterador it;
	it._p = _p->f_dret;
	return it;
};

bool Abin ::abin_buscar(Abin  &a, Abin::iterador it, int buscar){
	while(it != a.final()){
		if(buscar == (*it).numero()){
			return true;
		} else if (buscar < (*it).numero()){
			it = it.fesq();
		} else {
			it = it.fdret();
		}
	}
	return false;
}

    void Abin::crea(phone x) {
        creabts(_arrel,x);
    }

    typename Abin::node * Abin::creabts(node* m,phone x){
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
    
    void Abin::elimi(nat x, Abin a){
        Abin::iterador it;
        if(a.arrel()!=it){
            if((*a.arrel()).numero() != x){
                a.crea(*a.arrel());
            }
            Abin::iterador iti=a.arrel();
            elimi(x,iti.fesq().arbre());
            elimi(x,iti.fdret().arbre());
        }
    }
    
     void Abin::busca(Abin::iterador it,nat num,phone &res){
        Abin::iterador mal;
        if(it!=mal and res.nom()!=""){
            if((*it).numero()==num){res=*it;}
            else if((*it).numero()<num){
                busca(it.fdret(),num,res);
            }else{busca(it.fdret(),num,res);}
        }
    }
    void Abin::tamaño(Abin::iterador it,int &x){
        Abin::iterador it2;
        if(it.fesq()!=it2){
            ++x;
            tamaño(it.fesq(),x);
        }
        if(it.fdret()!=it2){
            ++x;
            tamaño(it.fdret(),x);
        }
    }

/* COST LINEAL O MENOR */

  /* Construeix un call_registry buit. */
  call_registry::call_registry() throw(error){
    _regg=NULL;
  }
 
  /* Constructor per còpia, operador d'assignació i destructor. */

  //{
  	//	delete _regg;
  	//	_regg-> =copia_nodes(R->_regg );
  //}

  call_registry::call_registry(const call_registry& R) throw(error){
    _regg=_regg->copia_nodes(R->_arrel());
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
  		throw(call_registry::ErrNumeroInexistent);
  	}
  }

  /* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
  Es produeix un error si el número no estava present. */
  void call_registry::elimina(nat num) throw(error){
  	if(conte(num)){
  	    Abin a;
  	    _regg->elimi(num,a);
  	}else{
  	    throw(call_registry::ErrNumeroInexistent );
  	}
  }

  /* Retorna cert si i només si el call_registry conté un 
  telèfon amb el número donat. */
  bool call_registry::conte(nat num) const throw(){
  		Abin::iterador it= reinterpret_cast<Abin::iterador &&>(_regg);
  		return (_regg->abin_buscar(reinterpret_cast<Abin &>(_regg), it, int(num)));
  }


  /* Retorna el nom associat al número de telèfon que s'indica.
  Aquest nom pot ser l'string buit si el número de telèfon no
  té un nom associat. Es produeix un error si el número no està en
  el call_registry. */
  string call_registry::nom(nat num) const throw(error){
    phone res;
      _regg->busca(_regg->arrel(),num,res);
    if(res.nom()=="") throw (call_registry::ErrNumeroInexistent);
    return res.nom();
  }

  /* Retorna el comptador de trucades associat al número de telèfon 
  indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
  aquest número. Es produeix un error si el número no està en el 
  call_registry. */
  nat call_registry::num_trucades(nat num) const throw(error){
    phone res;
    phone a;
    _regg->busca(_regg->arrel(),num,res);
    if(res==a) throw (call_registry::ErrNumeroInexistent);
    return res.frequencia();
  }

  /* Retorna cert si i només si el call_registry està buit. */
  bool call_registry::es_buit() const throw(){
    return _regg==NULL;
  }

  /* Retorna quants números de telèfon hi ha en el call_registry. */
  nat call_registry::num_entrades() const throw(){
    int x=1;
    Abin::iterador it= reinterpret_cast<Abin::iterador &&>(_regg);
    _regg->tamaño(it, x);
    if(_regg==NULL) return 0;
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
  	PERO DUMP NO: try{} catch throw(ErrNomRepetit)*/

  }

call_registry &call_registry::operator=(const call_registry &R) throw(error)   {
delete _regg;
_regg-> =copia_nodes(R._regg );
}
