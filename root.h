/*root.h
* Descricao: definicoes das funcoes executadas pela raiz da arvore.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#ifndef ROOT
#define ROOT

#include "basic.h"
#include "commandList.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <signal.h>
#include <sys/wait.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

//prototipo das funcoes
void rootLoop (Tree*);
timedCommand* prepareCommand (char*);
int getDelay (char*, timedCommand*);
void printMenu (bool);
void checkRun ();
void executeCommand (List*);
void sendMessage(timedCommand*);
void killKids();

//prototipo do tratamento de sinais
void executeScheduled (int);

#endif