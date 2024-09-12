#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <stdlib.h>  // Biblioteca padrão para alocação de memória
#include <stdbool.h> // Biblioteca para uso de tipo booleano

// Nome: Matheus Endlich Silveira - Matrícula: 202305392
// Nome: Rafael Ferreira Bassul - Matrícula: 202305395

// Estrutura que define uma Fila
struct Fila
{
    int capacidade; // Capacidade máxima da fila (número máximo de elementos que a fila pode armazenar)
    int *dados;     // Array para armazenar os elementos da fila
    int primeiro;   // Índice do primeiro elemento na fila
    int ultimo;     // Índice do último elemento na fila
    int nItens;     // Número atual de itens na fila
};

// Função para criar uma fila com capacidade especificada
void criarFila(struct Fila *f, int c)
{
    f->capacidade = c;                                     // Define a capacidade da fila
    f->dados = (int *)malloc(f->capacidade * sizeof(int)); // Aloca memória para o array de dados da fila
    f->primeiro = 0;                                       // Inicializa o índice do primeiro elemento
    f->ultimo = -1;                                        // Inicializa o índice do último elemento
    f->nItens = 0;                                         // Inicializa o número de itens na fila como zero
}

// Função para inserir um elemento na fila
void inserir(struct Fila *f, int v)
{
    if (f->ultimo == f->capacidade - 1) // Se o índice do último elemento atinge a capacidade máxima
        f->ultimo = -1;                 // Reinicia o índice do último elemento para -1

    f->ultimo++;             // Incrementa o índice do último elemento
    f->dados[f->ultimo] = v; // Armazena o valor na posição do último índice
    f->nItens++;             // Incrementa o número de itens na fila
}

// Função para remover um elemento da fila
int remover(struct Fila *f)
{
    int temp = f->dados[f->primeiro++]; // Armazena o valor do primeiro elemento e incrementa o índice

    if (f->primeiro == f->capacidade) // Se o índice do primeiro elemento atinge a capacidade máxima
        f->primeiro = 0;              // Reinicia o índice do primeiro elemento para 0

    f->nItens--; // Decrementa o número de itens na fila
    return temp; // Retorna o valor removido
}

// Função para verificar se a fila está vazia
int estaVazia(struct Fila *f)
{
    return (f->nItens == 0); // Retorna verdadeiro (1) se o número de itens for zero, indicando que a fila está vazia
}

// Função para verificar se a fila está cheia
int estaCheia(struct Fila *f)
{
    return (f->nItens == f->capacidade); // Retorna verdadeiro (1) se o número de itens for igual à capacidade, indicando que a fila está cheia
}

// Função para mostrar todos os elementos da fila
void mostrarFila(struct Fila *f)
{
    int cont, i;
    int ultimoAndar = 0; // Variável para rastrear o último andar visitado

    // Loop para percorrer todos os itens da fila
    for (cont = 0, i = f->primeiro; cont < f->nItens; cont++)
    {
        // Se o próximo andar na fila é maior que o último andar visitado
        if(f->dados[i] > 0 && f->dados[i] > ultimoAndar){
            // Percorre todos os andares entre o último andar visitado e o próximo andar
            for(int j = ultimoAndar + 1; j < f->dados[i]; j++){
                printf("indo para o %d° andar...\n", j);
            }
            // Imprime mensagem indicando que chegou no andar atual
            printf("chegou no %dº andar...\n", f->dados[i]);
            ultimoAndar = f->dados[i]; // Atualiza o último andar visitado
            i++; // Move para o próximo índice na fila
        }
        // Se o próximo andar na fila é menor que o último andar visitado
        else if(f->dados[i] < ultimoAndar)
        {
            // Percorre todos os andares entre o último andar visitado e o próximo andar
            for(int j = ultimoAndar - 1; j > f->dados[i]; j--){
                printf("indo para o %d° andar...\n", j);
            }
            // Imprime mensagem indicando que chegou no andar atual
            printf("chegou no %dº andar...\n", f->dados[i]);
            ultimoAndar = f->dados[i]; // Atualiza o último andar visitado
            i++; // Move para o próximo índice na fila
        }                                      
    }
    printf("\n");
}

int main()
{
    struct Fila fila; // Declara uma variável do tipo Fila
    int andar, escolha, andarAtual = -1; // Variáveis para armazenar o andar selecionado, escolha do usuário e andar atual

    criarFila(&fila, 12); // Cria uma fila com capacidade para 12 andares

    while (1) // Loop infinito para permitir interações contínuas
    {
        // Menu para escolher entre adicionar um andar ou ir a um andar
        printf("Por andar [1]\nIr [2]\n");
        scanf("%i", &escolha); // Lê a escolha do usuário
        
        // Se a escolha for 1, o usuário deseja adicionar um andar
        if (escolha == 1)
        {
            printf("Ponha o andar: \n");
            printf(" [12] [11] [10]\n [ 9] [ 8] [ 7]\n [ 6] [ 5] [ 4]\n [ 3] [ 2] [ 1]\n      [ 0]\n ");
            scanf("%i", &andar); // Lê o número do andar do usuário
            // Verifica se o andar está fora do intervalo permitido
            if (andar > 12 || andar < 0)
            {
                printf("O predio só possui 12 andares e o térreo\n"); // Mensagem de erro se o andar for inválido
            }
            else
            {
                inserir(&fila, andar); // Adiciona o andar à fila
            }
        }
        // Se a escolha for 2, o usuário deseja ir a um andar
        else if (escolha == 2)
        {
            // Verifica se a fila está vazia
            if (estaVazia(&fila))
            {
                printf("você não colocou nenhum andar!\n"); // Mensagem se não há andares na fila
            }
            // Verifica se o andar atual é o mesmo que o selecionado
            else if (andarAtual == andar)
            {
                printf("Você já está neste andar :)\n"); // Mensagem se o usuário já está no andar selecionado
            }
            else
            {
                mostrarFila(&fila); // Mostra a fila de andares
                andarAtual = fila.dados[fila.ultimo]; // Atualiza o andar atual com o último valor na fila
                printf("Você está atualmente está no %i° andar\n", andar); // Mostra o andar atual
                criarFila(&fila, 12); // Reinicializa a fila para permitir novas inserções
            }
        }
    }

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
