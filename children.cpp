/*children.h
* Descricao: implementacoes das funcoes executadas pelos nos que nao sao a raiz.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#include "children.h"

//loop executado pelos outros nos para receber instrucoes de seus pais
void childrensLoop (Tree *info) {
    Message msg;
    
    while (1) {
        msgrcv(info->receiveQueue, &msg, sizeof(msg), info->my, 0);
       	propagateMessage(info, msg);
       	//checa se devemos executar ou terminar este processo
       	if (msg.info != NULL) {
       		run((char**)msg.info);
       	} else {
       		break;
       	}
    }

    finish(info);
}

//funcao para propagar a mensagem para os filhos
void propagateMessage (Tree *info, Message send) {
	//verifica se tem filhos
	if (info->leftChild > 0) {
		//envia a mensagem para o filho da esquerda
		send.pid = info->leftChild;
		msgsnd(info->leftQueue, &send, sizeof(send), 0);

		//envia a mensagem para o filho da direita
		send.pid = info->rightChild;
		msgsnd(info->rightQueue, &send, sizeof(send), 0);
   	}
}

//funcao para esperar os filhos terminarem e terminar apos isto
void finish (Tree *info) {
	//espera os filhos terminarem, caso tenha
    int ret;
   
   	//verifica se tem filhos
    if (info->leftChild > 0) {
    	//se tiver, espera eles terminatem
   		waitpid(info->leftChild, &ret, 0);
   		waitpid(info->rightChild, &ret, 0);
   	}

   	//termina sua propria execucao
   	exit(0);
}