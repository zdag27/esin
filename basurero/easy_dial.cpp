#include "easy_dial.hpp"

void easy_dial::busca(arb* it,string s){
	int i = 0;
	while(i < s.size() and it != NULL){
		if(it != NULL){
			if(s[i] == it.car){
				it = it.cen;
				++i;
			} else if (s[i] < it.car){
				it = it.izq;
			} else {
				it = it.der;
			}
		}
	}
}

int easy_dial::conver(char letra){
	if ('A' <= letra < 'a'){
		return int(letra)-int('A');
	}
	else if ('a' <= letra <= 'z'){
		return int(letra)-int('a');
	}
}

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
						if(it->der!=NULL)
						inserta(s,i,it->der);
						else{
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
							if(it->izq!=NULL)
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
};

	easy_dial::easy_dial(const call_registry& R) throw(error){
		vector <string> v;
		R.dump(v);
		this->_raiz=NULL;
		for (int i=0;i<v.size();++i){
			arb* it = _raiz;
			inserta(v[i],0,it);
		}
	};
	easy_dial::easy_dial(const easy_dial& D) throw(error){
		this = D;
	};
	easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
		borrar(this->_raiz);
		copiar(D._raiz);
	};
	easy_dial::~easy_dial() throw(){
		borrar(this->_raiz);
	};

	string easy_dial::inici() throw(){};
	string easy_dial::seguent(char c) throw(error){};
	string easy_dial::anterior() throw(error){};
	nat easy_dial::num_telf() const throw(error){};

	void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
		arb* it=this->_raiz;
		busca(it, pref);
		if(it==NULL){
			throw(error(ErrPrefixIndef));
		}else{
			add(it,result);
		}
	};

	double easy_dial::longitud_mitjana() const throw(){};
