/*children.h
* Descricao: definicoes das funcoes executadas pelos nos que nao sao a raiz.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#ifndef CHILDREN
#define CHILDREN

#include "basic.h"
#include <iostream>
#include <sys/wait.h> 

using std::cout;
using std::endl;

//prototipo das funcoes
void childrensLoop (Tree*);
void propagateMessage (Tree*,Message);
void finish (Tree*);

#endif