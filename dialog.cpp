#include "dialog.hpp"

/*retorna en el vector respuestas los resultados obtenmidos al procesar los caracteres del string input y en
 numtelf retorna el numero de telefono corresopondiente
a el ultimo nombre obtenido o un cero por inexistencia este si en el proceso se produce error en answer 
se guarda el error associada a la etcepcion num telf 0 y acaba
*/
namespace dialog {
/*
realiza las diferentes ordenes dependiendo de los caracteres que entran interactuando con el easy dial
coste input.size()
*/
  void dialog(easy_dial& easy, const string& input, vector<string>& answers, nat& numtelf) throw(){
      bool existe_error=true;
  int i=0;
  easy.inici();
  string s;
  while(i<input.size() and existe_error){
    try{
        if(input[i]==phone::DELETECHAR){
            s=easy.anterior();
        }else if(input[i]==phone::ENDCHAR){
            s=easy.seguent(char(35));
        }else{
            s=easy.seguent(char(input[i]));
        }
        numtelf=easy.num_telf();
        answers.push_back(s);
    }catch(error e){
      existe_error=true;
      answers.push_back(e.mensaje());
      numtelf=0;
    }
  }
  }
}
