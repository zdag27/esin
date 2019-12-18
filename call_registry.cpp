#include "call_registry.hpp"
void call_registry::recnade(dalb* call,vector<phone> &v){
    if(call!=NULL){
        if(call->cell.nom()!=""){
            v.push_back(call->cell);
        }
        recnade(call->izq,v);
        recnade(call->der,v);
    }
};
void call_registry::tamano(dalb* call,int &x){
	++x;
	if(call->izq!=NULL){
		tamano(call->izq,x);
	}if(call->der!=NULL){
		tamano(call->der,x);
	}
};

call_registry::dalb* call_registry::buscar(dalb* call,nat num){
    if(call!=NULL){
	    if(call->cell.numero()==num){
		    return call;
	    }else{
		    dalb* n;
		    if(call->cell.numero()>num){
			    n=buscar(call->izq,num);
		    }else{
			    n=buscar(call->der,num);
		    }
		    return n;
	    }
    }
    return NULL;
};
/* COST LINEAL O MENOR */
call_registry::dalb* call_registry::copia_call(dalb * R){
		dalb* n;
		if (R == NULL) n = NULL;
		else {
				n = new dalb;
				try {
						n->cell = R->cell;
						n->izq = copia_call(R->izq);
						n->der = copia_call(R->der);
				} catch(...) {
						delete n;
						throw;
				}
		}
		return n;
};
void call_registry::thanos(dalb* m){
		if (m != NULL) {
				thanos(m->izq);
				thanos(m->der);
				delete m;
		}
};

void call_registry::agrega(dalb* &call,phone telf){
	if(call->cell.numero()<telf.numero()){
		if(call->der==NULL){
			dalb* n=new dalb;
			n->cell=telf;
			n->der=NULL;
			n->izq=NULL;
			call->der=n;
		}else{
			agrega(call->der,telf);
		}
	}else {
		if (call->izq == NULL) {
			dalb *n = new dalb;
			n->cell = telf;
			n->der = NULL;
			n->izq = NULL;
			call->izq = n;
		} else {
			agrega(call->izq, telf);
		}
	}
};

call_registry::dalb* call_registry::elimina (dalb *n, nat &num) {

	dalb *p = n;
	if (n != NULL) {
		if (num < n->cell.numero()) {
			n->izq = elimina(n->izq, num );
		}
		else if (num > n->cell.numero()) {
			n->der = elimina(n->der, num );
		}
		else {
			n = ajunta(n->izq, n->der);
			delete(p);
		}
	}
	return n;
};

call_registry::dalb* call_registry::ajunta(dalb *t1, dalb *t2)  {
		if (t1 == NULL) {
				return t2;
		}
		if (t2 == NULL) {
				return t1;
		}
		dalb* p = elimina_maxim(t1);
		p->der = t2;
		return p;
};

call_registry::dalb* call_registry::elimina_maxim (dalb* p) {
		dalb *p_orig = p, *pare = NULL;
		while (p->der != NULL) {
				pare = p;
				p = p->der;
		}
		if (pare != NULL) {
				pare->der = p->izq; // p és fill dret de pare
				p->izq = p_orig;
		}
		return p;
};
	/* Construeix un call_registry buit. */
	call_registry::call_registry() throw(error){
		//cout << "No estoy ";
		dalb*x = new dalb;
		phone a;
		x->izq=NULL;
		x->cell = a;
		x->der=NULL;
		rai=x;
		//cout << "loco, lo juro" << endl;
	}

	call_registry::call_registry(const call_registry& R) throw(error){
	 rai=copia_call(R.rai);
}
	call_registry::~call_registry() throw(){
		thanos(rai);
	}


/* COST MITJA = LOGARÍTMIC O MENOR -> ESTRUCTURES DE DADES DE TEORIA */
/* !TAULES DE DISPERSIÓ! */
/* EXPLICAR PERQUÈ ESTRUCTURA I NO ALTRES */

	/* Registra que s'ha realitzat una trucada al número donat, 
	incrementant en 1 el comptador de trucades associat. Si el número no 
	estava prèviament en el call_rbuscar(rai, num)egistry afegeix una nova entrada amb
	el número de telèfon donat, l'string buit com a nom i el comptador a 1. */
	void call_registry::registra_trucada(nat num) throw(error){
		dalb* n=buscar(rai, num);
		if(n!=NULL){
			++n->cell;
		}else{
			phone a(num,"",1);
			agrega(rai,a);
		}
	}

	/* Assigna el nom indicat al número donat.
	Si el número no estava prèviament en el call_registry, s'afegeix
	una nova entrada amb el número i nom donats, i el comptador 
	de trucades a 0. 
	Si el número existia prèviament, se li assigna el nom donat. */
	void call_registry::assigna_nom(nat num, const string& name) throw(error){
		// Crear nou objecte amb el nou nom -> PREGUNTA DEL FORUM
		dalb* res=buscar(rai,num);
		if(res==NULL){
				phone a(num,name,0);
				agrega(rai,a);
		}else{
				phone a(num,name,res->cell.frequencia());
				res->cell=a;
		}
	}

	/* Elimina l'entrada corresponent al telèfon el número de la qual es dóna.
	Es produeix un error si el número no estava present. */
	void call_registry::elimina(nat num) throw(error){
		if(conte(num)){
			 elimina(rai,num);
		}else{
				throw(error(ErrNumeroInexistent) );
		}
	}

	/* Retorna cert si i només si el call_registry conté un 
	telèfon amb el número donat. */
	bool call_registry::conte(nat num) const throw(){
			return (NULL!= buscar(rai, num));
	}


	/* Retorna el nom associat al número de telèfon que s'indica.
	Aquest nom pot ser l'string buit si el número de telèfon no
	té un nom associat. Es produeix un error si el número no està en
	el call_registry. */
	string call_registry::nom(nat num) const throw(error){
			dalb* res = (buscar(rai, num));
		if(res==NULL){
		throw (error(ErrNumeroInexistent));} 
		return res->cell.nom();
	}

	/* Retorna el comptador de trucades associat al número de telèfon 
	indicat. Aquest número pot ser 0 si no s'ha efectuat cap trucada a
	aquest número. Es produeix un error si el número no està en el 
	call_registry. */
	nat call_registry::num_trucades(nat num) const throw(error){
		dalb*   res=buscar(rai, num);
		if(res==NULL) throw (error(ErrNumeroInexistent));
		return res->cell.frequencia();
	}

	/* Retorna cert si i només si el call_registry està buit. */
	bool call_registry::es_buit() const throw(){
		return rai==NULL;
	}

	/* Retorna quants números de telèfon hi ha en el call_registry. */
	nat call_registry::num_entrades() const throw(){
		if(rai==NULL) return 0;
		int x=0;
		tamano(rai, x);
		return x;
	}

	/* COST MITJA = LINEAL */
	/* Fa un bolcat de totes les entrades que tenen associat un
	nom no nul sobre un vector de phone.
	Comprova que tots els noms dels telèfons siguin diferents{} 
	es produeix un error en cas contrari. */
	void call_registry::dump(vector<phone>& V) const throw(error){
  	recnade(rai,V);
    for(int i=0;i<V.size();++i){
        for(int j=0;j<V.size();++j){
            if(i!=j and V[i].nom()==V[j].nom()){
		throw(error(ErrNomRepetit))
            }
        }
    }
	}

call_registry &call_registry::operator=(const call_registry &R) throw(error)   {
	delete rai;
	rai =copia_call(R.rai);
	return *this;
}
