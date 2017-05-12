/*commandList.cpp
* Descricao: implementacoes das funcoes que controlam a lista de programas a executar.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#include "commandList.h"

//insere de maneira ordenada um novo elemento na lista de comandos a serem executados
List* insert(List *list, timedCommand *x) {
	List *ret = list;
	
	//se o elemento for nulo, nao faz nada
	if (x != NULL) {
		//cria a nova entrada que sera adicionada
		List *newEntry = (List*) malloc(sizeof(List));
		newEntry->element = copy(x);
		newEntry->prox = NULL;

		free(x);

		//se a lista eh vazia, colocamos a nova entrada na primeira posicao
		if (ret == NULL) {
			ret = newEntry;
		} else {
			//se nao for vazia, encontramos a posicao adequada
			List *aux = NULL;
			while (list != NULL) {
				//se a posicao atual eh menor ou igual a nova entrada, vamos para a proxima posicao
				if (list->element->startTime <= newEntry->element->startTime) {
					//guardamos o endereco atual se precisar
					aux = list;
					list = list->prox;
				} else {
					//checa se a posicao anterior nao era vazia
					if (aux) {
						//adicionamos entre a posicao anterior e a proxima
						aux->prox = newEntry;
						newEntry->prox = list;
					} else {
						//se for, vamos inserir no comeco da lista
						newEntry->prox = ret;
						ret = newEntry;
					}
					//com o elemento inserido, saimos do loop
					break;
				}
			}

			//se saimos do loop porque a lista acabou, adicionamos na ultima posicao
			if (list == NULL) {
				aux->prox = newEntry;
			}
		}
	}

	return ret;
}

//funcao usada para inserir novos elementos na lista dos comandos concluidos
List* insertEnd (List *list, List *last) {
	if (list == NULL) {
		return last;
	}

	List *ret = list;
	List *aux = NULL;

	//navega ate o fim da lista
	while (list != NULL) {
		aux = list;
		list = list->prox;
	}

	//insere o novo elemento no final
	aux->prox = last;

	return ret;
}

//verifica se esta na hora de executar o primeiro elemento da lista
//retorno:
//-1, lista vazia
//0, comando para ser executado
//1+, segundos que faltam para que o primeiro elemento execute
long checkReady(List *list) {
	int ret = -1;

	if (list != NULL) {
		if (list->element->startTime <= time(NULL)) {
			ret = 0;
		} else {
			ret = list->element->startTime - time(NULL);
		}
	}

	return ret;
}

//remove o primeiro elemento da lista e libera sua memoria
List* removeFirst (List *list, List *first) {
	List *ret;

	if (list == NULL) {
		ret = NULL;
	} else {
		ret = (List*) malloc(sizeof(List));
		ret = list->prox;

		//cria uma copia dele para poder ser liberada a copia original
		first->element = copy(list->element);
		first->prox = NULL;

		_deleteCommand(list->element);
		free(list);
	}

	return ret;
}

//checa se a lista esta vazia
bool isEmpty(List *list) {
	return (list == NULL);
}

//imprime toda a lista
List* show(List* print) {
	List *ret = print;
	char arrivalDate[9], startDate[12], finishDate[12];

	if (print == NULL) {
		cout << "Lista vazia!" << endl;
	} else {
		cout << "Job\tArq\tArrival\t\tDelay\tStart\t\tFinish\t\tRun Time\n";
	}

	while (print != NULL) {
		//formata as datas
		strftime (arrivalDate, 9, "%H:%M:%S", localtime(&print->element->arrivalTime));
		if (print->element->finishedTime != -1) {
			strftime (startDate, 9, "%H:%M:%S", localtime(&print->element->startTime));
			strftime (finishDate, 9, "%H:%M:%S", localtime(&print->element->finishedTime));
		} else {
			strcpy(startDate, "Didn't run.");
			strcpy(finishDate, "Didn't run.");
		}

		cout << print->element->jobNumber << "\t";
		cout << print->element->argv[0]+2 << "\t";
		cout << arrivalDate << "\t";
		cout << print->element->delay << "\t";
		cout << startDate << "\t";
		cout << finishDate << "\t";
		printf("%.5lfs\n", print->element->runTime);
		print = print->prox;
	}

	return ret;
}

//copia um elemento do tipo timedCommand e retorna sua copia
timedCommand *copy (timedCommand *x) {
	//aloca a memoria necessaria
	timedCommand *ret = (timedCommand*) malloc(sizeof(timedCommand));

	//faz a copia das variaveis que nao sao alocadas dinamicamente
	ret->argc = x->argc;
	ret->delay = x->delay;
	ret->jobNumber = x->jobNumber;
	ret->arrivalTime = x->arrivalTime;
	ret->startTime = x->startTime;
	ret->finishedTime = x->finishedTime;
	//aloca espaco para o array de comandos
	ret->argv = (char**) malloc(sizeof(char*) * ret->argc+1);
	ret->argv[ret->argc] = NULL;

	//copia argumento a argumento
	for (int i=0; i < ret->argc; i++) {
		ret->argv[i] = (char*) malloc(sizeof(char)*strlen(x->argv[i]));
		strcpy(ret->argv[i], x->argv[i]);
	}

	//retorna a nova copia
	return ret;
}

//funcao para deletar um elemento do tipo timedCommand
void _deleteCommand (timedCommand *x) {
	for (int i = x->argc-1; i>=0; i--) {
		free(x->argv[i]);
	}
	free(x->argv);
	free(x);
}

//apaga a lista
void _delete(List *list) {
	if (list) {
		do {
			List* aux = list;
			list = list->prox;
			free(aux);
		} while (list != NULL);
	}
}