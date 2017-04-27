/*main.cpp
* Descricao: arquivo principal, faz a chamada dos outros arquivos para a exeucao correta.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 
*     George Geonardo - 
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
    //funcao para criar os processos necessarios 
    //create(&pids);
    
    //para forcar a entrada no loop do root com um unico processo
    //retirar se a linha acima for descomentada
    pids.root = true;

    //se este processo for a raiz executa o loop da raiz,
    //caso contrario executa o loop dos filhos
    if (pids.root) {
        rootLoop(pids);
    } else {
        childrensLoop(pids);
    }
    
    return 0;
}