#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para alocação de memória
#include <stdbool.h> // Biblioteca para uso de tipo booleano

// Nome: Matheus Endlich Silveira - Matricula:202305392
// Nome: Rafael Ferreira Bassul - Matricula: 202305395

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

    criarFila(&fila, 12); // Cria uma fila com capacidade para 12 andares

    while (1) // Loop infinito para permitir interações contínuas
    {
        printf("Por andar [1]\nIr [2]\n"); // Menu para escolher entre adicionar um andar ou ir a um andar
        scanf("%i", &escolha); // Lê a escolha do usuário
        if (escolha == 1)
        {
            printf("Ponha o andar: \n");
            printf(" [12] [11] [10]\n [ 9] [ 8] [ 7]\n [ 6] [ 5] [ 4]\n [ 3] [ 2] [ 1]\n      [ 0]\n ");
            scanf("%i", &andar); // Lê o número do andar do usuário
            if (andar > 12 || andar < 0) // Verifica se o andar está fora do intervalo permitido
            {
                printf("O predio só possui 12 andares e o térreo\n"); // Mensagem de erro se o andar for inválido
            }
            else
            {
                inserir(&fila, andar); // Adiciona o andar à fila
            }
        }
        else if (escolha == 2)
        {
            if (estaVazia(&fila)) // Verifica se a fila está vazia
            {
                printf("você não colocou nenhum andar!\n"); // Mensagem se não há andares na fila
            }
            else if (andarAtual == andar) // Verifica se o andar atual é o mesmo que o selecionado
            {
                printf("Você já está neste andar :)\n"); // Mensagem se o usuário já está no andar selecionado
            }
            else
            {
                mostrarFila(&fila); // Mostra a fila de andares
                andarAtual = fila.dados[fila.ultimo]; // Atualiza o andar atual com o último valor na fila
                printf("Você está atualmente está no %i° andar\n", andar); // Mostra o andar atual
                criarFila(&fila, 12); // Reinicializa a fila
            }
        }
    }

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
