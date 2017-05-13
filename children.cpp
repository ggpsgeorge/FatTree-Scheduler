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
    timedCommand cmd;
    while (1) {
        //espera por uma mensagem
        msgrcv(info->receiveQueue, &msg, sizeof(msg), info->my, 0);
        //manda a mensagem para os filhos
        propagateMessage(info, &msg);
        
        //checa se deve terminar
        if (msg.quit) {
          waitKids(info);
          exit(0);
        }

        //se nao terminar, executamos o comando recebido
        messageToCommand(&msg, &cmd);
        run(&cmd);
    }
}

//funcao para propagar a mensagem para os filhos
void propagateMessage (Tree *info, Message *send) {
	//cout << "Propagando" << endl;
  //verifica se tem filhos
	if (info->leftChild > 0) {
		//envia a mensagem para o filho da esquerda
		send->pid = info->leftChild;
		msgsnd(info->leftQueue, &send, sizeof(*send), 0);
  }

  if (info->rightChild > 0) {
		//envia a mensagem para o filho da direita
		send->pid = info->rightChild;
		msgsnd(info->rightQueue, send, sizeof(*send), 0);
  }
}