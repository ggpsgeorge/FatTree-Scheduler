/*basic.h
* Descricao: definicao da funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 
*     George Geonardo - 
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#include "basic.h"

//funcao que cria os 15 processos da arvore
void create (Tree *pids) {
    int send = 0;
    //define o primeiro processo como a raiz
    pids->root = true;

    //vamos criar uma arvore 4 niveis, 2^4-1 = 15
    for (int i=0; i < 3; i++) {
        //criamos o no filho da esquerda
        pids->left = fork();
        if (pids->left) {
            //sen for o pai, criamos mais um filho, agora o da direita
            pids->right = fork();
            if (pids->right) {
                //se o no tem seus dois filhos, nao precisamos
                //de mais nenhum, logo, saimos do loop de criacao  
                break;
            } else {
                //se for filho, zeramos as informacoes
                //de filhos e dizemos que nao eh a raiz
                pids->left = 0;
                pids->root = false;
            }
        } else {

            //se for filho, zeramos as informacoes
            //de filhos e dizemos que nao eh a raiz
            pids->right = 0;
            pids->root = false;
        }
    }

    //seta o processo como nao ocupado
    pids->busy = false;
    //pega o proprio pid
    pids->my = getpid();
}

//funcao que cria um novo processo para executar o comando passado
//com os argumentos retorna o tempo (em segundos) gasto na execucao
double run (char **argv) {
    int child_ret;
    //variavel para calcular a o tempo gasto
    std::chrono::duration<double> diff;
    //variavel para armazenar o tempo de inicio
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    //faz o fork
    pid_t pid = fork();

    if (pid) {
        //se for pai, espera o processo filho acabar
        waitpid(pid, &child_ret, 0);
        //quando o filho acabar, pegamos o tempo de fim e calculamos a diferenca
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        diff = std::chrono::duration_cast<std::chrono::duration<double> >(end - start);
    } else {
        //se for o filho, executa o comando que foi recebido como argumento
        execvp(argv[0], argv);
        //se chegou aqui, houve um erro no comando acima
        cerr << "\n\nNao foi possivel executar: \"" << argv[0] << "\"" << endl << endl;
        exit(1);
    }

    //retorna a diferenca entre o tempo de fim e de inicio
    return diff.count();
}