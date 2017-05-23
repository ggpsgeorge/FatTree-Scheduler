/*basic.h
* Descricao: definicoes da estrutura basica da arvore e a funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 12/0051087
*     Guilherme Torres - 
*/

#ifndef BASIC
#define BASIC

#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>


#define MAX_ARGUMENTS 10
#define MAX_ARGUMENT_LENGTH 20

using std::cout;
using std::cerr;
using std::endl;

//estrutura para a arvore
//cada no sabe se eh a raiz
//e os pids de seus filhos
typedef struct {
    pid_t leftChild, rightChild, my, father;
    bool root, busy;
    int upQueue, downQueue;
} Tree;

//estrutura para passarmos os
//comandos na fila de mensagem
typedef struct {
	long pid;
	bool quit;
	int nargs;
	char info[MAX_ARGUMENTS][MAX_ARGUMENT_LENGTH];
} Message;

//estrutura da mensagem passada apos a execucao
//com os tempos medidos
typedef struct {
	long pid;
	long startTime, finishTime;
	std::chrono::high_resolution_clock::time_point startChrono, finishChrono;
	double runTime;
} Result;

//prototipos das funcoes
void create (Tree *);
void run (Tree *, char **, Result *);
void createQueues (Tree*);
void deleteQueues(Tree*);
void waitKids(Tree*);
void mergeResults (Tree*,Result*);
void compareResults (Result*, Result*);

#endif