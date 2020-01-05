#include "dialog.hpp"
/*retorna en el vector respuestas los resultados obtenmidos al procesar los caracteres del string input y en numtelf retorna el numero de telefono corresopondiente
a el ultimo nombre obtenido o un cero por inexistencia este si en el proceso se produce error en answer se guarda el error associada a la etcepcion num telf 0 y acaba
*/
namespace dialog {
  void dialog(easy_dial& easy,const string& input, vector<string>& answers, nat& numtelf) throw() {
      bool b=true;
      int i=0;
      easy.inici();
      string s;
      while(i<input.size() and b){
          if(input[i]==phone::DELETECHAR){
              s=easy.anterior();
          }else if(input[i]==phone::ENDCHAR){
              s=easy.seguent(char(35));
          }else{
              s=easy.seguent(char(input[i]));
          }
          if(s!="Error::easy_dial:33:No es pot eliminar caracter en el prefix en curs." and s!="Error::easy_dial:31:Prefix en curs indefinit." and s!="Error::easy_dial:32:No hi ha telefons amb el prefix en curs."){
              b= false;
              numtelf=easy.num_telf();
          }else{
              numtelf=0;
          }
          answers.push_back(s);
      }
  }
}
