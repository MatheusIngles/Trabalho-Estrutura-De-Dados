#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para alocação de memória
#include <stdbool.h> // Biblioteca para uso de tipo booleano

// Estrutura que define uma Fila
struct Fila
{
    int capacidade; // Capacidade máxima da fila
    int *dados;     // Array para armazenar os elementos da fila
    int primeiro;   // Índice do primeiro elemento da fila
    int ultimo;     // Índice do último elemento da fila
    int nItens;     // Número atual de itens na fila
};

// Função para criar uma fila com capacidade especificada
void criarFila(struct Fila *f, int c)
{
    f->capacidade = c;                                     // Define a capacidade da fila
    f->dados = (int *)malloc(f->capacidade * sizeof(int)); // Aloca memória para os dados da fila
    f->primeiro = 0;                                       // Inicializa o índice do primeiro elemento
    f->ultimo = -1;                                        // Inicializa o índice do último elemento
    f->nItens = 0;                                         // Inicializa o número de itens na fila como zero
}

// Função para inserir um elemento na fila
void inserir(struct Fila *f, int v)
{
    if (f->ultimo == f->capacidade - 1) // Se o último índice atingiu a capacidade máxima
        f->ultimo = -1;                 // Reinicia o índice do último para -1

    f->ultimo++;             // Incrementa o índice do último
    f->dados[f->ultimo] = v; // Insere o valor na posição do último índice
    f->nItens++;             // Incrementa o número de itens na fila
}

// Função para remover um elemento da fila
int remover(struct Fila *f)
{
    int temp = f->dados[f->primeiro++]; // Armazena o valor do primeiro elemento e incrementa o índice

    if (f->primeiro == f->capacidade) // Se o primeiro índice atinge a capacidade máxima
        f->primeiro = 0;              // Reinicia o índice do primeiro para 0

    f->nItens--; // Decrementa o número de itens na fila
    return temp; // Retorna o valor removido
}

// Função para verificar se a fila está vazia
int estaVazia(struct Fila *f)
{
    return (f->nItens == 0); // Retorna verdadeiro se o número de itens for zero
}

// Função para verificar se a fila está cheia
int estaCheia(struct Fila *f)
{
    return (f->nItens == f->capacidade); // Retorna verdadeiro se o número de itens for igual à capacidade
}

// Função para mostrar todos os elementos da fila
void mostrarFila(struct Fila *f)
{
    int cont, i;

    for (cont = 0, i = f->primeiro; cont < f->nItens; cont++)
    {                                                        // Percorre a fila a partir do primeiro elemento
        printf("indo para o %dº andar...\n", f->dados[i++]); // Imprime o elemento atual
        if (i == f->capacidade)                              // Se o índice atual atinge a capacidade máxima
            i = 0;                                           // Reinicia o índice para 0
    }
    printf("\n\n");
}

int main()
{
    struct Fila fila;
    int andar, escolha, andarAtual;

    criarFila(&fila, 12);

    while (1)
    {
        printf("Por andar [1]\nIr [2]\n");
        scanf("%i", &escolha);
        if (escolha == 1)
        {
            printf("Ponha o andar: \n");
            printf(" [12] [11] [10]\n [ 9] [ 8] [ 7]\n [ 6] [ 5] [ 4]\n [ 3] [ 2] [ 1]\n      [ 0]\n ");
            scanf("%i", &andar);
            if (andar > 12 || andar < 0)
            {
                printf("O predio só possui 12 andares e o térreo");
            }
            inserir(&fila, andar);
        }
        else if (escolha == 2)
        {
            if (estaVazia(&fila))
            {
                printf("você não colocou nenhum andar!\n");
            }
            else if (andarAtual == andar)
            {
                printf("Você já está neste andar :)\n");
            }
            else
            {
                mostrarFila(&fila);
                andarAtual = fila.dados[fila.ultimo];
                printf("Você está atualmente está no %i° andar\n", andar);
                criarFila(&fila, 12);
            }
        }
    }

    return 0;
}