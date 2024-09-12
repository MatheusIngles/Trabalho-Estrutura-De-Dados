#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX 100

typedef struct {
    char notacaofixa[TAM_MAX];
} notacao;

// Definição da estrutura da pilha
typedef struct {
    int topo;
    notacao *itens[TAM_MAX];
} Pilha;

// Função para inicializar a pilha
void stack(Pilha *p) {
    p->topo = -1;
}

// Função para verificar se a pilha está cheia
int isFull(Pilha *p) {
    return (p->topo == TAM_MAX - 1);
}

// Função para verificar se a pilha está vazia
int isEmpty(Pilha *p) {
    return (p->topo == -1);
}

// Função para empilhar um elemento
void push(Pilha *p, char *valor) {
    if (isFull(p)) {
        printf("Erro: A pilha está cheia!\n\n");
    } else {
        strcpy(p->itens[++(p->topo)]->notacaofixa, valor);
    }
}

// Função para desempilhar um elemento
char* pop(Pilha *p) {
    if (isEmpty(p)) {
        printf("Erro: A pilha está vazia!\n\n");
        return NULL;  // Retorna NULL para indicar erro
    } else {
        return p->itens[(p->topo)--]->notacaofixa;
    }
}

// Função para visualizar o elemento no topo da pilha
char* peek(Pilha *p) {
    if (isEmpty(p)) {
        printf("A pilha está vazia.\n\n");
        return NULL;
    } else {
        return p->itens[p->topo]->notacaofixa;
    }
}

// Função para imprimir a pilha atual
void printStack(Pilha *p) {
    if (!isEmpty(p)) {  
        for (int i = 0; i <= p->topo; i++) {
            printf("%s\n", p->itens[i]->notacaofixa);
        }
    } else {
        printf("A pilha está vazia.\n\n");
    }
}

// Função principal para testar a pilha
int main() {
    Pilha NP; // Cria uma nova pilha
    char notacaoinfixadousuario[TAM_MAX];
    int tamanhonotacaofixa;
    
    stack(&NP); // Inicializa a pilha com topo -1
    printf("Coloque sua notação: ");
    scanf("%[^\n]", notacaoinfixadousuario);
     
    tamanhonotacaofixa = strlen(notacaoinfixadousuario);
    
    push(&NP,notacaoinfixadousuario[0]);
    
    for(int i = 1;  i <  tamanhonotacaofixa; i++){
        if(notacaoinfixadousuario[i] == '-' || notacaoinfixadousuario[i] == '/' || notacaoinfixadousuario[i] == '+' || notacaoinfixadousuario[i] == '^' || notacaoinfixadousuario[i] == '*'){
            push(&NP,notacaoinfixadousuario[i+1]);
            push(&NP,notacaoinfixadousuario[i]);
        }
    }
    printStack(&NP);

    return 0;
}
