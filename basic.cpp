/*basic.h
* Descricao: definicao da funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 12/0051087
*     Guilherme Torres - 
*/

#include "basic.h"

//funcao que cria os 15 processos da arvore
void create (Tree *pids) {
    //cria as filas de mensagem
    createQueues(pids);
    //checa se eh necessaria fazer a subtracao do tamanho de long 
    int rootPid = getpid();
    pids->father = 
    pids->root = false;

    //vamos criar uma arvore de 4 niveis, 2^4-1 = 15
    for (int i=0; i < 3; i++) {
        //criamos o no filho da esquerda
        pids->leftChild = fork();
        if (pids->leftChild > 0) {
            //sen for o pai, criamos mais um filho, agora o da direita
            pids->rightChild = fork();
            if (pids->rightChild > 0) {
                //se o no tem seus dois filhos, nao precisamos
                //de mais nenhum, logo, saimos do loop de criacao  
                break;
            } else if (pids->rightChild == 0) {
                //se for filho, zeramos as informacoes
                //de filhos e dizemos que nao eh a raiz
                pids->leftChild = 0;
            } else {
                cerr << "ERRO: Nao foi possivel realizar o fork." << endl;
            }
        } else if (pids->leftChild == 0) {
            //se for filho, zeramos as informacoes
            //de filhos e dizemos que nao eh a raiz
            pids->rightChild = 0;
        } else {
            cerr << "ERRO: Nao foi possivel realizar o fork." << endl;
        }
    }

    //seta o processo como nao ocupado
    pids->busy = false;
    //pega o proprio pid
    pids->my = getpid();
    //pega o pid do pai
    pids->father = getppid();

    if (pids->my == rootPid) {
        pids->root = true;
    }
}

//funcao que cria um novo processo para executar o comando passado
//com os argumentos retorna o tempo (em segundos) gasto na execucao
void run (Tree *info, char **argv, Result *res) {
    int child_ret;

    //guarda o tempo de inicio, com precisao de millisegundo e segundo
    res->startTime = time(NULL);
    res->startChrono = std::chrono::high_resolution_clock::now();
    
    //faz o fork
    pid_t pid = fork();

    if (pid) {
        //se for pai, espera o processo filho acabar
        waitpid(pid, &child_ret, 0);
        //quando o filho acabar, pegamos o tempo de fim 
        res->finishTime = time(NULL);
        res->finishChrono = std::chrono::high_resolution_clock::now();
    } else {
        //se for o filho, executa o comando que foi recebido como argumento
        execvp(argv[0], argv);
        //se chegou aqui, houve um erro no comando acima
        cerr << "\n\nNao foi possivel executar: \"" << argv[0] << "\"" << endl << endl;
        exit(1);
    }

    mergeResults(info, res);
}

void createQueues (Tree *info) {
    int key1 = 0x12004991;
    int key2 = 0x12004992;

    info->upQueue = msgget(key1, IPC_CREAT | 0666);
    if (info->upQueue < 0) {
        fprintf(stderr, "ERRO: nao foi possivel criar a fila de mensagens.\n");
    }

    info->downQueue = msgget(key2, IPC_CREAT | 0666);
    if (info->downQueue < 0) {
        fprintf(stderr, "ERRO: nao foi possivel criar a fila de mensagens.\n");
    }
}

void deleteQueues(Tree *info) {
    if (msgctl(info->downQueue, IPC_RMID, NULL) != 0) {
        cerr << "ERRO: Nao foi possivel deletar a fila." << endl;
    }

    if (msgctl(info->upQueue, IPC_RMID, NULL) != 0) {
        cerr << "ERRO: Nao foi possivel deletar a fila." << endl;
    }
}

//funcao para esperar os filhos retornarem
void waitKids (Tree *info) {
    int ret;

    if (info->leftChild != -1) {
        waitpid(info->leftChild, &ret, 0);
    }

    if (info->rightChild != -1) {
        waitpid(info->rightChild, &ret, 0);
    }
}

void mergeResults (Tree *info, Result *res) {
    //espera pelos resultados dos filhos, se for o caso
    if (info->leftChild > 0) {
        Result aux;
        msgrcv(info->upQueue, &aux, sizeof(aux), info->my, 0);
        compareResults(res, &aux);
    }

    if (info->rightChild > 0) {
        Result aux;
        msgrcv(info->upQueue, &aux, sizeof(aux), info->my, 0);
        compareResults(res, &aux);
    }

    //manda para o pai, se for o caso
    if (!info->root) {
        res->pid = info->father;
        msgsnd(info->upQueue, res, sizeof(*res), 0);
    }
}

//fica com os tempos de inicio minimo e final maximo
void compareResults (Result *final, Result *newData) {
    if (final->startTime > newData->startTime) {
        final->startTime = newData->startTime;
    }

    if (final->finishTime < newData->finishTime) {
        final->finishTime = newData->finishTime;
    }

    if (final->startChrono > newData->startChrono) {
        final->startChrono = newData->startChrono;
    }

    if (final->finishChrono < newData->finishChrono) {
        final->finishChrono = newData->finishChrono;
    }

    final->runTime = std::chrono::duration_cast<std::chrono::duration<double> >(final->finishChrono - final->startChrono).count();
}