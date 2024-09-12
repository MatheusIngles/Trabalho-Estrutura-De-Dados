/* Simulação de Torneio de Pedra-Papel-Tesoura com Fila
Desenvolva uma simulação de um torneio de Pedra-Papel-Tesoura onde os jogadores competem
em pares e os vencedores continuam para a próxima rodada. Utilize uma fila para organizar os
jogadores. A cada rodada, dois jogadores são removidos da fila e competem entre si. O vencedor
da partida deve retornar ao final da fila, enquanto o perdedor é eliminado do torneio. O processo
continua até que reste apenas um jogador na fila, que será o campeão do torneio. Por exemplo,
se a fila inicial tiver 8 jogadores, o algoritmo deve continuar removendo pares de jogadores,
competindo, e reordenando os vencedores até que reste apenas um vencedor final.
*/
// Nome: Matheus Endlich Silveira - Matricula:202305392
// Nome: Rafael Ferreira Bassul - Matricula: 202305395
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Max 10 // Define o número máximo de jogadores

/* TABELA DE TIPO:
    1- Papel
    2- Tesoura
    3- Pedra
*/

// Estrutura para armazenar o nome de um jogador
typedef struct {
    char nome[Max];
} Jogadore;

// Estrutura de uma fila que armazena jogadores e tipos de jogadas
typedef struct {
    Jogadore Jogadores[Max]; // Array para armazenar os jogadores
    int comeco, fim, tamanho; // Variáveis para controle da fila
    int itens[Max]; // Array para armazenar os tipos de jogadas
} fila;

// Função para inicializar a fila
void inicializar(fila *f) {
    f->tamanho = 0;
    f->comeco = 0;
    f->fim = -1;
}

// Função para verificar se a fila está vazia
int isVazia(fila *f) {
    return (f->tamanho == 0);
}

// Função para verificar se a fila está cheia
int isFull(fila *f) {
    return (f->tamanho == Max);
}

// Função para adicionar um elemento à fila (Enqueue)
void Enqueue(fila *f, int estilo) {
    if (!isFull(f)) {
        f->fim++;
        if ((f->fim) == Max) { // Se o índice 'fim' alcançar o tamanho máximo, reseta para 0
            (f->tamanho++);
            f->fim = 0;
            f->itens[f->fim] = estilo;
        } else {
            f->tamanho++;
            f->itens[(f->fim)] = estilo; // Adiciona o elemento no final da fila
        }
    } else {
        printf("A fila está cheia");
    }
}

// Função para remover um elemento da fila (Dequeue)
int Dequeue(fila *f) {
    if (!isVazia(f)) {
        int v = f->itens[f->comeco]; // Remove o elemento do início da fila
        f->comeco++;
        if ((f->comeco) == Max) { // Se o índice 'comeco' alcançar o tamanho máximo, reseta para 0
            f->tamanho--;
            f->comeco = 0;
            return v;
        } else {
            f->tamanho--;
            return v;
        }
    } else {
        printf("A fila está vazia\n");
        return -1; // Retorna -1 se a fila estiver vazia
    }
}

// Função para obter o primeiro elemento da fila sem removê-lo
int peek(fila *f) {
    if (!isVazia(f)) {
        return f->itens[f->comeco];
    } else {
        return -1;
    }
}

// Função para adicionar um jogador à fila com um tipo de jogada
void AdicionarJogador(fila *f, Jogadore *j, int estilo) {
    if (!isFull(f)) {
        Enqueue(f, estilo); // Adiciona o tipo de jogada à fila
        f->Jogadores[f->fim] = *j; // Adiciona o jogador à fila
    } else {
        printf("A fila está cheia");
    }
}

// Função para adicionar vencedores à fila temporária
void AdicionarVencedores(fila *f, fila *f2, int indice) {
    if (!isFull(f)) {
        Enqueue(f, f2->itens[indice]); // Adiciona o tipo de jogada do vencedor à fila
        f->Jogadores[f->fim] = f2->Jogadores[indice]; // Adiciona o vencedor à fila
    } else {
        printf("A fila está cheia");
    }
}

// Função para adicionar o último jogador restante (sem par) à fila
void AdicionarOUltimo(fila *f, fila *f2) {
    if (!isFull(f)) {
        Enqueue(f, f2->itens[f->fim]);
        f->Jogadores[f->fim] = f2->Jogadores[f2->fim];
    } else {
        printf("A fila está cheia\n");
    }
}

// Função para remover um jogador da fila
char *RemoverJogador(fila *f) {
    int x = f->comeco;
    Dequeue(f); // Remove o jogador do início da fila
    return f->Jogadores[x].nome; // Retorna o nome do jogador removido
}

// Função para popular a fila com jogadores aleatórios
void PopularRivais(fila *f, int Jogadores) {
    char *nomes[] = {
    "Julia", "Pedro", "Joao", "Lucas", "Marcus", "Adolfo", "Guiberto", 
    "Ana", "Elena", "Maria", "Estevao", "Michael", "Bruno", "Pablo", 
    "Hery", "Alexa", "Oto", "Jun", "Rich", "Berno", "Harry", "Bassul", 
    "Bonato", "Scooby", "Carlos", "Roberto", "Tomas", "Samuel", "Nicolas", "Felipe", "Aline", 
    "Marcos", "Silvia", "Bianca", "Ricardo", "Jessica", "Thiago", "Gabriel", 
    "Cintia", "Daniel", "Marta", "Patricia", "Claudio", "Sandra"
};

    int a;
    if (f->tamanho + Jogadores <= Max) {
        for (int i = 0; i < Jogadores; i++) {
            Jogadore j;
            int tipo;
            a = (rand() % 45) ;
            strcpy(j.nome,nomes[a]);
            tipo = (rand() % 3) + 1;
            AdicionarJogador(f, &j, tipo);
        }
    } else {
        printf("Vc vai estourar a fila\n");
    }
}

// Função para mostrar os jogadores e seus tipos de jogada na fila
void mostrarJogadores(fila *f) {
    int cont, i;

    for (cont = 0, i = f->comeco; cont < f->tamanho; cont++) {
        printf("Jogadores: %s - Tipo de jogada:%d \n", f->Jogadores[i].nome, f->itens[i]);
        i++;
        if (i == f->tamanho + 1)
            i = 0;
    }
    printf("\n\n");
}

// Função para realizar o chaveamento e definir os vencedores de cada rodada
void chaveamento(fila *f, fila *temporaria, int rodadas) {
    int cont, i, i2;
    if (!isVazia(f)) {
        printf("Rodada : %d\n", rodadas++);
        for (cont = 0, i = f->comeco; cont < f->tamanho; cont += 2) {
            if (i + 1 >= Max) {
                i2 = 0;
            } else if (i + 1 >= f->tamanho) {
                break;
            } else {
                i2 = i + 1;
            }

            // Definindo o vencedor com base nas regras de Pedra-Papel-Tesoura
            do {
                if (f->itens[i] == 1 && f->itens[i2] == 2) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i2].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i2);
                    break;
                } else if (f->itens[i] == 1 && f->itens[(i2)] == 3) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i);
                    break;
                } else if (f->itens[i] == 2 && f->itens[(i2)] == 3) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i2].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i2);
                    break;
                } else if (f->itens[i] == 2 && f->itens[i2] == 1) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i);
                    break;
                } else if (f->itens[i] == 3 && f->itens[(i2)] == 1) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i2].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i2);
                    break;
                } else if (f->itens[i] == 3 && f->itens[(i2)] == 2) {
                    printf("Vencedor do confronto: %s, entre %s e %s\n", f->Jogadores[i].nome, f->Jogadores[i2].nome, f->Jogadores[i].nome);
                    AdicionarVencedores(temporaria, f, i);
                    break;
                } else {
                    int a = (rand() % 3) + 1, a2 = (rand() % 3) + 1;
                    f->itens[i] = a; // Gera novas jogadas se os jogadores empatarem
                    f->itens[i2] = a2;
                }
            } while (1);

            i += 2;
            if (i > Max) {
                i -= f->tamanho;
            }
        }
        if (f->tamanho % 2 != 0) { // Se houver um jogador sem par, ele é movido para a próxima rodada
            AdicionarOUltimo(temporaria, f);
        }
        *f = *temporaria;

        if (f->tamanho != 1) { // Se mais de um jogador ainda resta, continua o torneio
            inicializar(temporaria);
            chaveamento(f, temporaria, rodadas);
        } else {
            printf("O vencedor da competição foi: %s\n", f->Jogadores[f->comeco].nome); // Anuncia o vencedor final
        }
    } else {
        printf("Lista Vazia\n");
    }
}

// Função principal
int main() {
    int escolha, tipo;
    fila FilaPrincipal, FilaPlaceHolder; // Filas principal e auxiliar
    char *JogadorRetirado;
    Jogadore J;
    inicializar(&FilaPrincipal);
    inicializar(&FilaPlaceHolder);
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    while (1) {
        printf("O que vc quer fazer?\n1-Adicionar Jogador\n2-Remover Jogador\n3-Colocar Competidores Da Vizinhança\n4-Mostrar Fila\n5-Começar a competição\n");
        scanf("%d", &escolha);
        if (escolha == 1) {
            printf("Qual o Nome do Jogador e o tipo, respectivamente de jogada seguindo a tabela. Lembre que o tipo é inteiro, então em caso de palavra ira acabar com o codigo\n");
            scanf("\n%[^\n]", J.nome);
            scanf("%d", &tipo);
            if (tipo == 1 || tipo == 2 || tipo == 3) {
                AdicionarJogador(&FilaPrincipal, &J, tipo);
            } else {
                printf("Escolha certo!!\n");
            }
        } else if (escolha == 2) {
            JogadorRetirado = RemoverJogador(&FilaPrincipal);
            printf("Nome do Jogador Removido: %s\n", JogadorRetirado);
        } else if (escolha == 3) {
            printf("Quantidade De Jogadores Que vc quer inserir?(Lembre que o tipo é inteiro)\n");
            scanf("%d", &escolha);
            if (escolha < 0) {
                printf("Coloque um numero Positivo");
            } else {
                PopularRivais(&FilaPrincipal, escolha);
            }
        } else if (escolha == 4) {
            mostrarJogadores(&FilaPrincipal);
        } else if (escolha == 5) {
            inicializar(&FilaPlaceHolder);
            chaveamento(&FilaPrincipal, &FilaPlaceHolder, 0);
        } else {
            break;
        }
    }
    return 0;
}
