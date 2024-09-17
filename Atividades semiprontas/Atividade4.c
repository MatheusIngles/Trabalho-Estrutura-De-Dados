/*Desenvolva um algoritmo para converter uma expressão aritmética da notação infixa (onde os
operadores são colocados entre os operandos) para a notação pós-fixa (também conhecida
como notação polonesa reversa - RPN), onde os operadores são colocados após seus operandos.
O programa deve receber uma expressão aritmética em notação infixa. A expressão pode conter
os operadores +, -, *, /, e ^ (exponenciação), além de parênteses ( e ). A expressão pode incluir
variáveis (representadas por letras) ou números (opcionais).
Exemplos de entrada incluem A + B * (C ^ D - E) ^ (F + G * H) - I, 3 + 4 * 2 / (1 - 5) ^ 2 ^ 3, A * (B
+ C) / D, e (A + B) * (C + D). A saída deve ser a expressão correspondente em notação pós-fixa: A
B C D ^ E - F G H * + ^ * + I -, 3 4 2 * 1 5 - 2 3 ^ ^ / +, A B C + * D /, e A B + C D + *, respectivamente. 

Utilize uma estrutura de dados pilha para armazenar operadores e gerenciar sua precedência. A
precedência dos operadores é a seguinte: ^ tem a maior precedência, seguido por * e /, e depois
por + e -. A associatividade dos operadores é da esquerda para a direita, exceto para ^, que é da
direita para a esquerda. Os parênteses na notação infixa definem a ordem das operações, mas
não devem aparecer na saída pós-fixa. Seu código será avaliado pela correção da conversão, pela
eficiência do algoritmo e pela clareza da implementação. Certifique-se de incluir comentários
explicativos no código.
*/

// Nome: Matheus Endlich Silveira - Matricula:202305392
// Nome: Rafael Ferreira Bassul - Matricula: 202305395

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX 100

// Definição da estrutura da pilha
typedef struct {
    int topo;        // Índice do topo da pilha
    char itens[TAM_MAX]; // Array para armazenar os itens da pilha
} Pilha;

// Função para inicializar a pilha
void stack(Pilha *p) {
    p->topo = -1; // Inicializa a pilha vazia, com topo em -1
}

// Função para verificar se a pilha está cheia
int isFull(Pilha *p) {
    return (p->topo == TAM_MAX - 1); // Retorna 1 se a pilha estiver cheia
}

// Função para verificar se a pilha está vazia
int isEmpty(Pilha *p) {
    return (p->topo == -1); // Retorna 1 se a pilha estiver vazia
}

// Função para empilhar um elemento
void push(Pilha *p, char valor) {
    if (isFull(p)) {
        printf("Erro: A pilha está cheia!\n\n"); // Mensagem de erro se a pilha estiver cheia
    } else {
        p->itens[++(p->topo)] = valor; // Incrementa o topo e adiciona o valor
    }
}

// Função para desempilhar um elemento
char pop(Pilha *p) {
    if (isEmpty(p)) {
        printf("Erro: A pilha está vazia!\n\n"); // Mensagem de erro se a pilha estiver vazia
        return '\0';  // Retorna NULL para indicar erro
    } else {
        return p->itens[(p->topo)--]; // Retorna o valor do topo e decrementa o topo
    }
}

// Função para visualizar o elemento no topo da pilha
char peek(Pilha *p) {
    if (isEmpty(p)) {
        printf("A pilha está vazia.\n\n"); // Mensagem se a pilha estiver vazia
        return '\0';
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
        printf("A pilha está vazia.\n\n"); // Mensagem se a pilha estiver vazia
    }
}

// Função principal para testar a pilha e converter a notação
int main() {
    Pilha pilha; // Cria uma nova pilha
    char notacaofixa[TAM_MAX], notacaopolonesareversa[TAM_MAX]; // Strings para notação infixa e pós-fixa
    int tamanhonotacaofixa, indice = 0; // Tamanho da notação infixa e índice para a notação pós-fixa
    stack(&pilha); // Inicializa a pilha com topo -1
    
    printf("Coloque sua notação: ");
    scanf("\n%[^\n]", notacaofixa); // Lê a expressão infixa do usuário
     
    tamanhonotacaofixa = strlen(notacaofixa); // Calcula o comprimento da expressão infixa
    
    // Processa cada caractere da expressão infixa
    for(int i = 0; i < tamanhonotacaofixa; i++){
        char c = notacaofixa[i];
        
        if(c == '('){
            push(&pilha, c); // Empilha o parêntese de abertura
        } else if(c == ')'){
            // Desempilha até encontrar o parêntese de abertura
            while(!isEmpty(&pilha) && peek(&pilha) != '('){
                notacaopolonesareversa[indice++] = pop(&pilha);
            }
            if (!isEmpty(&pilha) && peek(&pilha) == '(') {
                pop(&pilha); // Remove o parêntese de abertura da pilha
            }
        } else if(c == '+' || c == '-' || c == '/' || c == '^' || c == '*'){
            // Processa operadores com base na precedência (aqui que está o pulo do gato)
            while(!isEmpty(&pilha) && (
                 (peek(&pilha) == '*' || peek(&pilha) == '/') && (c == '+' || c == '-') || 
                 ( peek(&pilha) == '-' || peek(&pilha) == '*') && (c == '/' || c =='^'))){
                notacaopolonesareversa[indice++] = pop(&pilha);
            }
            push(&pilha, c); // Empilha o operador atual
        } else if(c == ' '){ //Ignora os espaços
            continue;
        }else{
            notacaopolonesareversa[indice++] = c; // Adiciona o operando à notação pós-fixa
        }
    }
    
    // Desempilha todos os operadores restantes
    while(!isEmpty(&pilha)){
        notacaopolonesareversa[indice++] = pop(&pilha);
    }
    
    notacaopolonesareversa[indice++] = '\0'; // Adiciona o caractere de terminação de string
    
    printf("Notação pós-fixa: %s\n", notacaopolonesareversa); // Exibe a expressão pós-fixa

    return 0;
}
