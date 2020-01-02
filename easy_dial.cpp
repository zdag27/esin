#include "easy_dial.hpp"

void easy_dial::add(arb *it,vector<string>&s)const{
    if(it!=NULL){
        add(it->izq,s);
        add(it->cen,s);
        add(it->der,s);
        s.push_back(it->p.nom());
    }
};

void easy_dial::copiar(easy_dial::arb* rai,easy_dial::arb *it){
    if(it->izq==NULL){
        rai->izq=NULL;
    }else{
        rai->izq=new arb;
        rai->izq->arr=rai;
        rai->izq->car=it->izq->car;
        rai->izq->p=it->izq->p;
        copiar(rai->izq,it->izq);
    }
    if(it->cen==NULL){
        rai->cen=NULL;
    }else{
        rai->cen=new arb;
        rai->cen->arr=rai;
        rai->cen->car=it->cen->car;
        rai->cen->p=it->cen->p;
        copiar(rai->cen,it->cen);
    }
    if(it->der==NULL){
        rai->der=NULL;
    }else{
        rai->der=new arb;
        rai->der->arr=rai;
        rai->der->car=it->der->car;
        rai->der->p=it->der->p;
        copiar(rai->der,it->der);
    }

}

void easy_dial::borrar(easy_dial::arb *it){
    if(it!=NULL){
        borrar(it->izq);
        borrar(it->cen);
        borrar(it->der);
        delete it;
    }
};

void easy_dial::busc(arb* &it,char s){
    if(it!=NULL){
        if(!it->car==s){
            if(it->car>s){
                it=it->izq;
                busc(it,s);
            }else{
                it=it->der;
                busc(it,s);
            }
        }
    }
};

void easy_dial::busca(arb* it,string s)const {
    int i = 0;
    while(i < s.size() and it != NULL){
        if(it != NULL){
            if(s[i] == it->car){
                it = it->cen;
                ++i;
            } else if (s[i] < it->car){
                it = it->izq;
            } else {
                it = it->der;
            }
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

easy_dial::arb* easy_dial::node_hashtag(const phone &p){
    arb *it=new arb;
    it->car=('#');
    it->izq=NULL;
    it->der=NULL;
    it->cen=NULL;
    it->p=p;
    return it;
};

void easy_dial::fori(phone s,int i,arb* it){
    for(int x=i;x<s.nom().size();++x){
        it->cen=new arb;
        it=it->cen;
        it->car=s.nom()[x];
        it->izq=NULL;
        it->der=NULL;
        it->cen=NULL;
    }
    it->cen=node_hashtag(s);
};

void easy_dial::inserta(phone s,int i,arb* &it){
    bool b=true;
    while(b){
        if(i<s.nom().size()){
            if(it->cen!=NULL){
                if(s.nom()[i]==it->cen->car){
                    ++i;
                    it=it->cen;
                }else if(s.nom()[i]>it->cen->car){
                    if(it->cen->der==NULL){
                        it->cen->der->car=s.nom()[i];
                        it->cen->der->p=s;
                        it->cen->der->izq=NULL;
                        it->cen->der->der=NULL;
                        it->cen->der->cen=NULL;
                        it->cen->der->arr=it;
                        b=false;
                    }else{
                        it=it->cen->der;
                    }
                }else{
                    if(it->cen->izq==NULL){
                        it->cen->izq->car=s.nom()[i];
                        it->cen->izq->p=s;
                        it->cen->izq->izq=NULL;
                        it->cen->izq->der=NULL;
                        it->cen->izq->cen=NULL;
                        it->cen->izq->arr=it;
                        b=false;
                    }else{
                        it=it->cen->izq;
                    }
                }
            }else{
                it->cen=new arb;
                it->cen->car=s.nom()[i];
                it->cen->p=s;
                it->cen->izq=NULL;
                it->cen->der=NULL;
                it->cen->cen=NULL;
                it->cen->arr=it;
                b=false;
            }
        }else{
            if(it->cen==NULL){
                it->cen=new arb;
                it->cen->car='#';
                it->cen->p=s;
                it->cen->izq=NULL;
                it->cen->der=NULL;
                it->cen->cen=NULL;
                it->cen->arr=it;
                b=false;
            }else{
                arb *auxi =it->cen;
                while(auxi->izq!=NULL){
                    auxi=auxi->izq;
                }
                auxi->izq=new arb;
                auxi->izq->car='#';
                auxi->izq->p=s;
                auxi->izq->izq=NULL;
                auxi->izq->der=NULL;
                auxi->izq->cen=NULL;
                auxi->izq->arr=it;
            }
            b=false;
        }
    }
};

easy_dial::easy_dial(const call_registry& R) throw(error){
    vector <phone> v;
    R.dump(v);
    this->_raiz=new arb;
    _raiz->izq=NULL;
    _raiz->der=NULL;
    _raiz->arr=NULL;
    _raiz->cen=NULL;
    _raiz->car=v[0].nom()[0];
    _raiz->p=v[0];
    _it=_raiz;
    for (int i=1;i<v.size();++i){
        arb* it = _raiz;
        inserta(v[i],0,it);
    }
};
easy_dial::easy_dial(const easy_dial& D) throw(error){
    *this = D;
};
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){
    borrar(_raiz);
    if(D._raiz!=NULL){
        _raiz=new arb;
        _raiz->izq=NULL;
        _raiz->der=NULL;
        _raiz->arr=NULL;
        _raiz->cen=NULL;
        _raiz->car=D._raiz->car;
        _raiz->p=D._raiz->p;
        copiar(_raiz,D._raiz);
    }else{
        _raiz=NULL;
    }

};
easy_dial::~easy_dial() throw(){
    borrar(_raiz);
};

string easy_dial::inici() throw(){
    _it=_raiz;
    return _it->p.nom();
};
string easy_dial::seguent(char c) throw(error){
    arb *auxi=_it->cen;
    busc(auxi,c);
    if(auxi==NULL){
        throw (error(ErrPrefixIndef));
    }else{
        _it=auxi;
        return(_it->p.nom());
    }
};
string easy_dial::anterior() throw(error){
    if(_it->arr==NULL){
        throw (error(ErrNoHiHaAnterior));
    }else{
        _it=_it->arr;
        return(_it->p.nom());
    }
};
nat easy_dial::num_telf() const throw(error){
    return(_it->p.numero());
};

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
