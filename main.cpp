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
    //variavel para armazenar as informacoes do processo
    Tree pids;

    //funcao para criar os processos necessarios, guarda os IDs das filas de mensagem para poder deletar no final
    int *queues = create(&pids);

    //se este processo for a raiz executa o loop da raiz,
    //caso contrario executa o loop dos filhos
    if (pids.root) {
        rootLoop(&pids);
    } else {
        childrensLoop(&pids);
    }
    
    //deleta as filas
    if (pids.root == true)
        deleteQueues(queues);

    return 0;
}