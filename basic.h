/*basic.h
* Descricao: definicoes da estrutura basica da arvore e a funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 
*     George Geonardo - 
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#ifndef BASIC
#define BASIC

#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

//estrutura para a arvore
//cada no sabe se eh a raiz
//e os pids de seus filhos
typedef struct {
    pid_t left, right, my;
    bool root, busy;
} Tree;

//prototipos das funcoes
void create (Tree *pids);
double run (char **argv);

#endif