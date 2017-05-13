/*basic.h
* Descricao: definicao da funcao de inicio.
* 
* Autores:
*     Caio Batista de Melo - 12/0049945
*     Felipe Spinola - 12/0011131
*     George Geonardo - 12/0012197
*     Giovanni Torres - 
*     Guilherme Torres - 
*/

#include "basic.h"

//funcao que cria os 15 processos da arvore
int* create (Tree *pids) {
    //cria as filas de mensagem
    int *queues = createQueues();
    //checa se eh necessaria fazer a subtracao do tamanho de long 
    int rootPid = getpid();
    //define o primeiro processo como a raiz
    pids->receiveQueue = 0;

    pids->root = false;

    //vamos criar uma arvore de 4 niveis, 2^4-1 = 15
    for (int i=0; i < 3; i++) {
        pids->leftQueue = -1;
        pids->rightQueue = -1;
        int queueNum = pids->receiveQueue * 2 + 1;
        //criamos o no filho da esquerda
        pids->leftChild = fork();
        if (pids->leftChild > 0) {
            //sen for o pai, criamos mais um filho, agora o da direita
            pids->leftQueue = queueNum++;
            pids->rightChild = fork();
            if (pids->rightChild > 0) {
                pids->rightQueue = queueNum;
                //se o no tem seus dois filhos, nao precisamos
                //de mais nenhum, logo, saimos do loop de criacao  
                break;
            } else if (pids->rightChild == 0) {
                //se for filho, zeramos as informacoes
                //de filhos e dizemos que nao eh a raiz
                pids->leftChild = 0;
                pids->leftQueue = -1;
                pids->rightQueue = -1;
                pids->receiveQueue = queueNum;
            } else {
                cerr << "ERRO: Nao foi possivel realizar o fork." << endl;
            }
        } else if (pids->leftChild == 0) {
            //se for filho, zeramos as informacoes
            //de filhos e dizemos que nao eh a raiz
            pids->rightChild = 0;
            pids->receiveQueue = queueNum;
            pids->rightQueue = -1;
            pids->leftQueue = -1;
        } else {
            cerr << "ERRO: Nao foi possivel realizar o fork." << endl;
        }
    }

    //seta o processo como nao ocupado
    pids->busy = false;
    //pega o proprio pid
    pids->my = getpid();

    if (pids->my == rootPid) {
        pids->root = true;
    }

    //troca os indices pelos ids das filas
    if (!pids->root) {
        pids->receiveQueue = queues[pids->receiveQueue-1];
    }
    pids->leftQueue = queues[pids->leftQueue-1];
    pids->rightQueue = queues[pids->rightQueue-1];

    return queues;
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

int* createQueues () {
    int *ret = (int*) malloc(sizeof(int)*14);
    int numbers[14], number = 6213;

    for (int i=0; i<14; i++) {
        numbers[i] = number++;
        ret[i] = msgget(numbers[i], IPC_CREAT | 0x1FF);
        //cout << "i: " << i << "\t" << ret[i] << endl;
        if (ret[i] < 0) {
            cerr << "ERRO: Nao foi possivel criar a fila." << endl;
        }
    }

    return ret;
}

void deleteQueues(int *queues) {
    for (int i=0; i<14; i++) {
        //cout << "Deletando: " << queues[i] << endl;
        if (msgctl(queues[i], IPC_RMID, NULL) != 0) {
            cerr << "ERRO: Nao foi possivel deletar a fila." << endl;
        }
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