/*main.cpp
* Descricao: arquivo principal, faz a chamada dos outros arquivos para a exeucao correta.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#include "basic.h"
#include "children.h"
#include "root.h"

//funcao principal que ira popular a arvore e colocar cada no em seu loop
int main () {
    //variavel para armazenar as informacoes do processo (no) corrente
    Tree pids;
    //cout << "pids.root | pids.my | pids.left | pids.right | pids.numReceive | pids.numLeft | pids.numRight" << endl;

    //funcao para criar os processos necessarios, guarda os IDs das filas de mensagem para poder deletar no final
    int *queues = create(&pids);
    
    //para forcar a entrada no loop do root com um unico processo
    //retirar se a linha acima for descomentada
    //pids.root = true;

    //se este processo for a raiz executa o loop da raiz,
    //caso contrario executa o loop dos filhos
    if (pids.root) {
        rootLoop(&pids);
    } else {
        //childrensLoop(&pids);
    }
    
    /*
    struct message {
        long pid;
        char msg[30];
    } send, receive;

    strcpy(receive.msg, "branco");
    strcpy(send.msg, "oi");

    //cout << pids.root << "\t" << pids.my << "\t" << pids.leftChild << "\t" << pids.rightChild << "\t" << pids.receiveQueue << "\t" << pids.leftQueue << "\t" << pids.rightQueue << endl;

    if (pids.root) {
        cout << "Mandando na fila: " << pids.leftQueue << endl;
        send.pid = pids.leftChild;
        msgsnd(pids.leftQueue, &send, sizeof(send), 0);
        sleep(5);
    } else if (pids.receiveQueue == queues[0]) {
        cout << "Esperando na fila: " << pids.receiveQueue << endl;
        msgrcv(pids.receiveQueue, &receive, sizeof(receive), pids.my, 0);
        cout << "Recebi" << endl;
        cout << receive.msg << endl;
    }
    */
    
    //deleta as filas
    if (pids.root == true)
        deleteQueues(queues);

    return 0;
}