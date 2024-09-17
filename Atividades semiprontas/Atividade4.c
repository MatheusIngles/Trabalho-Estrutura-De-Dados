// Nome: Matheus Endlich Silveira - Matricula:202305392
// Nome: Rafael Ferreira Bassul - Matricula: 202305395

#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <string.h>  // Inclui a biblioteca de manipulação de strings
#include <stdlib.h>  // Inclui a biblioteca de funções utilitárias (por exemplo, malloc, free)

// Define o tamanho máximo da pilha
#define TAM_MAX 100

// Define a estrutura da pilha
typedef struct {
    int topo;        // Índice que indica a posição do topo da pilha
    char itens[TAM_MAX]; // Array para armazenar os itens da pilha
} Pilha;

// Função para inicializar a pilha
void stack(Pilha *p) {
    p->topo = -1; // Inicializa a pilha como vazia, topo está em -1
}

// Função para verificar se a pilha está cheia
int isFull(Pilha *p) {
    return (p->topo == TAM_MAX - 1); // Retorna 1 se o topo estiver no último índice (cheia), 0 caso contrário
}

// Função para verificar se a pilha está vazia
int isEmpty(Pilha *p) {
    return (p->topo == -1); // Retorna 1 se o topo estiver em -1 (vazia), 0 caso contrário
}

// Função para empilhar um elemento
void push(Pilha *p, char valor) {
    if (isFull(p)) {
        printf("Erro: A pilha está cheia!\n\n"); // Imprime mensagem de erro se a pilha estiver cheia
    } else {
        p->itens[++(p->topo)] = valor; // Incrementa o topo e adiciona o valor ao topo
    }
}

// Função para desempilhar um elemento
char pop(Pilha *p) {
    if (isEmpty(p)) {
        printf("Erro: A pilha está vazia!\n\n"); // Imprime mensagem de erro se a pilha estiver vazia
        return '\0';  // Retorna '\0' para indicar que ocorreu um erro
    } else {
        return p->itens[(p->topo)--]; // Retorna o valor do topo e decrementa o topo
    }
}

// Função para visualizar o elemento no topo da pilha
char peek(Pilha *p) {
    if (isEmpty(p)) {
        printf("A pilha está vazia.\n\n"); // Imprime mensagem se a pilha estiver vazia
        return '\0'; // Retorna '\0' para indicar que a pilha está vazia
    } else {
        return p->itens[p->topo]; // Retorna o valor do topo da pilha
    }
}

// Função para imprimir a pilha atual
void printStack(Pilha *p) {
    if (!isEmpty(p)) {  
        for (int i = 0; i <= p->topo; i++) {
            printf("%c", p->itens[i]); // Imprime todos os elementos da pilha
        }
    } else {
        printf("A pilha está vazia.\n\n"); // Imprime mensagem se a pilha estiver vazia
    }
}

// Função principal que realiza a conversão da notação infixa para pós-fixa
int main() {
    Pilha pilha; // Cria uma nova pilha para operadores
    char notacaofixa[TAM_MAX], notacaopolonesareversa[TAM_MAX]; // Strings para armazenar a notação infixa e pós-fixa
    int tamanhonotacaofixa, indice = 0; // Tamanho da expressão infixa e índice para a notação pós-fixa
    stack(&pilha); // Inicializa a pilha com topo em -1
    
    printf("Coloque sua notação: ");
    scanf("\n%[^\n]", notacaofixa); // Lê a expressão infixa do usuário (inclui espaços e outros caracteres até a nova linha)
     
    tamanhonotacaofixa = strlen(notacaofixa); // Calcula o comprimento da expressão infixa
    
    // Processa cada caractere da expressão infixa
    for(int i = 0; i < tamanhonotacaofixa; i++){
        char c = notacaofixa[i];
        
        if(c == '('){
            push(&pilha, c); // Empilha o parêntese de abertura
        } else if(c == ')'){
            // Desempilha até encontrar o parêntese de abertura
            while(!isEmpty(&pilha) && peek(&pilha) != '('){
                notacaopolonesareversa[indice++] = pop(&pilha); // Adiciona operadores à notação pós-fixa
            }
            if (!isEmpty(&pilha) && peek(&pilha) == '(') {
                pop(&pilha); // Remove o parêntese de abertura da pilha
            }
        } else if(c == '+' || c == '-' || c == '/' || c == '^' || c == '*'){
            // Processa operadores com base na precedência e associatividade
            while(!isEmpty(&pilha) && (
                 (peek(&pilha) == '*' || peek(&pilha) == '/') && (c == '+' || c == '-') || // Precedência de * e / sobre + e -
                 (peek(&pilha) == '*') && (c == '/') || // Precedência de * sobre /
                 (peek(&pilha) == '/') && (c == '*') || // Precedência de / sobre *
                 (peek(&pilha) == '+') && (c == '-') || // Precedência de + sobre -
                 (peek(&pilha) == '-') && (c == '+') // Precedência de - sobre +
                 )){
                notacaopolonesareversa[indice++] = pop(&pilha); // Adiciona operadores à notação pós-fixa
            }
            push(&pilha, c); // Empilha o operador atual
        } else if(c == ' '){ // Ignora espaços
            continue;
        } else {
            notacaopolonesareversa[indice++] = c; // Adiciona operandos (variáveis ou números) à notação pós-fixa
        }
    }
    
    // Desempilha todos os operadores restantes
    while(!isEmpty(&pilha)){
        notacaopolonesareversa[indice++] = pop(&pilha); // Adiciona operadores restantes à notação pós-fixa
    }
    
    notacaopolonesareversa[indice++] = '\0'; // Adiciona o caractere de terminação de string ao final da notação pós-fixa
    
    printf("Notação pós-fixa: %s\n", notacaopolonesareversa); // Exibe a expressão em notação pós-fixa

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
