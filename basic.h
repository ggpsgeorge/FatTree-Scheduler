/*basic.h
* Descricao: definicoes da estrutura basica da arvore e a funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
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
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;

//estrutura para a arvore
//cada no sabe se eh a raiz
//e os pids de seus filhos
typedef struct {
    pid_t leftChild, rightChild, my;
    bool root, busy;
    int leftQueue, rightQueue, receiveQueue;
} Tree;

//estrutura para passarmos os
//comandos na fila de mensagem
typedef struct {
	long pid;
	char *info;
} Message;

//prototipos das funcoes
int* create (Tree *pids);
double run (char **argv);
int* createQueues ();
void deleteQueues(int*);

#endif