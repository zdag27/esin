#include "easy_dial.hpp"
 
void easy_dial::find_Phone(arb* it,phone &p){
    if(it!=NULL){
         if(it.car==int('#')){
             if(p.frequencia()<it._p.fecuencia())
                  p=it._p;
        }
         find_Phone(it->izq);
         find_Phone(it->cen);
         find_Phone(it->der);
    }
}

void easy_dial::mueve_it(arb* it,char c,arb* &ti){
    if(it!=NULL){
            while(it!=NULL and ti==NULL){
                if(it.car==int(c)){
                    ti=it;
                }else if(it.car<int(c)){
                    it=it->der;
                }else{
                    it=it->izq;
                }
            }
        }
};

void easy_dial::borrar(arb* &ra){
    if(ra!=NULL){
        borrar(ra->izq);
        borrar(ra->cen);
        borrar(ra->der);
        delete *this;
    }
};
arb* easy_dial::copiar(arb* m,arb* ac,arb* &c) {
    arb* n;
    if (m == NULL) n = NULL;
    else {
        n = new arb;
        try {
        		if(m==ac){c=n;}
            n->car = m->info;
            if(n->car==int('#')){
                n->p=m->p;
            }
            n->izq = copiar(m->izq);
            n->cen = copiar(m->cen);
            n->der = copiar(m->der);
        } catch(...) {
            delete n;
            throw;
        }
    }
    return n;
};

void easy_dial::add(arb* it,vector<phone> &result){
    if(it!=NULL){
        if(it->car==int('#')){
            result.push_back(it->p);
        }
        add(it.izq,result);
        add(it.cen,result);
        add(it.der,result);
    }
};

void easy_dial::busca(arb* it,string s){
	int i = 0;
	while(i < s.size() and it != NULL){
		if(s[i] == it.car){
			it = it.cen;
			++i;
		} else if (s[i] < it.car){
			it = it.izq;
		} else {
			it = it.der;
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

arb easy_dial::node_hashtag(const phone &p){
		arb a=new arb;
		it.car=int('#');
			it.izq=NULL;
			it.der=NULL;
			it.cen=NULL;
			it.p=p;
			return a;
};

void fori(phone s,int i,arb* it){
			for(int x=i;x<s.nombre().size();++x){
			it.cen=new arb;
			it=it.cen;
			it.car=conver(s.nombre()[x]);
			it.izq=NULL;
			it.der=NULL;
			it.cen=NULL;
		}
		it.cen=node_hashtag(s);
};

void easy_dial::inserta(phone s,int i,arb* &it){
	if(it==NULL){
		it=new arb;
		it.car=conver(s.nombre()[i]);
		it.izq=NULL;
		it.der=NULL;
		it.cen=NULL;
		fori(s,1,it);
	}else{
		if(i!=s.nombre().size()){
			if(it.car==conver(s.nombre()[i])){
				it = it.cen;
			} else {
				//COMPARACIONES
				if(conver(s.nombre()[i]) > it.car){
					if(it->der!=NULL){
						inserta(s,i,it->der);
					}else{
						it.der=new arb;
						it=it.der;
						it.car=conver(s.nombre()[i]);
						it.izq=NULL;
						it.der=NULL;
						it.cen=NULL;
						i-= -1;
						fori(s,i,it);
					}
				}
				else{
					if(it->izq!=NULL){
						inserta(s,i,it->izq);
					}else{
						it.izq=new arb;
						it=it.izq;
						it.car=conver(s.nombre()[i]);
						it.izq=NULL;
						it.der=NULL;
						it.cen=NULL;
						i-= -1;
						fori(s,i,it);
					}
				}
			}
		}
	}
};

easy_dial::easy_dial(const call_registry& R) throw(error){
	vector <string> v;
	R.dump(v);
	this->_raiz=NULL;
	for (int i=0;i<v.size();++i){
		arb* it = _raiz;
		inserta(v[i],0,it);
	}
	act = _raiz;
};
easy_dial::easy_dial(const easy_dial& D) throw(error){
	this = D;
};
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
	borrar(this->_raiz);
	copiar(D._raiz,D.act,act);
	prefijo = D.prefijo;
};
easy_dial::~easy_dial() throw(){
	borrar(this->_raiz);
};

/* Inicialitza el prefix en curs a buit. Retorna el nom de F(S, '');
si F (S, '') no existeix llavors retorna l'string buit. */
string easy_dial::inici() throw(){
	this->prefijo = "";
	arb* it = this->_raiz;
	phone p;
	find_Phone(it,p);
	return p;
};

/* Retorna el nom de F(S, p') on p' és el prefix resultant d'afegir
el caràcter c al final del prefix en curs p i
fa que el nou prefix en curs sigui p'.
Si F(S, p) existeix però F(S, p') no existeix llavors retorna 
l'string buit. 
Si no existeix F(S, p) (i per tant tampoc pot existir F(S, p'))
llavors es produeix un error i el prefix en curs queda indefinit. 
Naturalment, es produeix un error si el prefix en curs inicial p 
fos indefinit. */
string easy_dial::seguent(char c) throw(error){
	string s;
	this->prefijo += c;
	arb* ti=NULL;
	if(prefijo.size>1)
	    mueve_it(it->cen,c,ti); // !!! mover el it a donde c, si no lo encuentra it = NULL !!!
	else
	    mueve_it(it,c,ti);
	if(ti == NULL){
	    prefijo.pop_back();
		throw(error(ErrPrefixIndef));
	}else{
		// Hemos encontrado un nodo con el prefijo, sacamos el primer nombre en orden lexicografico
		phone p;
		find_phone(it,p);
		s=p.nombre();
		it=ti;
		vecror[prefijo.size()-1]=it;
	}
	return s;
};

/* Elimina l'últim caràcter del prefix en curs p = p' · a
(a és el caràcter eliminat). Retorna el nom F(S, p') 
i fa que el nou prefix en curs sigui p'. 
Es produeix un error si p fos buida i si es fa que el prefix en curs
quedi indefinit. Òbviament, també es produeix un error 
si p fos indefinit. */
string easy_dial::anterior() throw(error){
    string s;
	if(prefijo.size() <= 1){
	    if(prefijo.size()==1){
	        it=_raiz;
	        prefijo.pop;
	    }
		throw(error(ErrNoHiHaAnterior))
	} else {
		this->prefijo.pop_back();
		arb* it = vecror[prefijo.size()-1];
			s = find_primerContacto(it).nom(); 
	}
	return s;
};

/* Retorna el número de telèfon de F(S, p), sent p
el prefix en curs. Es produeix un error si p és indefinit o si
no existeix F(S, p). */
nat easy_dial::num_telf() const throw(error){
    phone p;
	find_primerContacto(it,p); // 
	return p.numero()

};

/* Retorna en el vector result tots els noms dels contactes de 
telèfon que comencen amb el prefix pref, en ordre lexicogràfic creixent. */
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
	if(it==NULL){
		throw(error(ErrPrefixIndef));
	}else{
		add(it,result);
	}
};

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
el easy_dial i t(s) és el número de pulsacions mínimes
necessàries (= número de crides a l'operació seguent) per
obtenir el telèfon el nom del qual és s. La funció retorna la suma
    Pr(s) · t(s)
per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
telefonar a s. La probabilitat s'obté dividint la freqüència de s per
la suma de totes les freqüències. 


FER ESTADISTICA SEGONS NOU FIND, TREURE MITJANA
Nom 			Freq 	Nº Pulsacions 
MARIA			15t					3
JOSEP			50t					1
MAR 			5t 					5
MIQUEL 	    	30t					2
MARTA 		    10t					4
FRAN             1t                 2
sumatorio (freq*npul)/sumatorio(req)
*/

double easy_dial::longitud_mitjana() const throw(){};
