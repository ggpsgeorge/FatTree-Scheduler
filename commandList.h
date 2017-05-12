/*commandList.h
* Descricao: definicoes das funcoes que controlam a lista de programas a executar e das estruturas usadas.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#ifndef COMMAND
#define COMMAND

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

typedef struct {
	char** argv;
	int argc, delay, jobNumber;
	time_t arrivalTime, startTime, finishedTime;
	double runTime;
} timedCommand;

typedef struct list {
	timedCommand *element;
	struct list *prox;
} List;

//prototipo das funcoes
List* insert(List*, timedCommand*);
List* insertEnd(List*, List*);
long checkReady(List*);
List* removeFirst(List*, List*);
bool isEmpty(List*);
List* show(List*);
timedCommand *copy(timedCommand*);
void _deleteCommand(timedCommand*);
void _delete(List*);

#endif