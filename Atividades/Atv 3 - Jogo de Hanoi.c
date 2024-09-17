// Nome: Matheus Endlich Silveira - Matricula:202305392
// Nome: Rafael Ferreira Bassul - Matricula: 202305395
/* Implemente uma simulação do jogo Torre de Hanói, onde o objetivo é mover uma pilha de discos
de um pino para outro seguindo regras específicas: apenas um disco pode ser movido por vez, e
um disco maior não pode ser colocado sobre um disco menor. Utilize pilhas para representar
cada um dos três pinos, onde os discos são empilhados do maior (na base) ao menor (no topo).
Comece com todos os discos no pino inicial e mova-os para o pino de destino, utilizando o pino
auxiliar, se necessário. O jogo deve respeitar a regra de que um disco maior não pode ser
colocado sobre um disco menor.
Por exemplo, se o pino inicial contém os discos [3, 2, 1], o objetivo é movê-los para o pino de
destino, utilizando o pino auxiliar conforme as regras do jogo
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define Max 10  // Define o tamanho máximo da pilha

// Define a estrutura de dados para representar uma pilha
typedef struct{
    int topo, itens[Max];
}pilha;

// Função para inicializar uma pilha
void iniciador(pilha *p){
    p->topo = -1;  // Define o topo da pilha como -1, indicando que está vazia
}

// Função para verificar se a pilha está vazia
int isVazia(pilha *p){
    return p->topo == -1;
}

// Função para verificar se a pilha está cheia
int IsFull(pilha *p){
    return p->topo == Max - 1;
}

// Função para adicionar um elemento na pilha
void Push(pilha *p, int valor){
    if(IsFull(p)){  // Verifica se a pilha está cheia
        printf("A pilha está cheia!\n");
    }else{
        p->topo++;  // Incrementa o topo
        p->itens[p->topo] = valor;  // Adiciona o valor ao topo da pilha
    }
}

// Função para remover um elemento do topo da pilha
int pop(pilha *p){
    if(isVazia(p)){  // Verifica se a pilha está vazia
        printf("A pilha já está vazia\n");
        return -1;  // Retorna -1 para indicar falha
    }else{
        return p->itens[(p->topo--)];  // Retorna o elemento do topo e decrementa o topo
    }
}

// Função para visualizar o elemento no topo da pilha sem removê-lo
int peek(pilha *p){
    return p->itens[p->topo];
}

// Função para preencher a pilha com discos para o jogo
void preencherPilha(pilha *p, int QuantidadeDisco){
    if(QuantidadeDisco <= Max){
        for(int i = QuantidadeDisco; i > 0; i--){
            Push(p, i);  // Insere os discos do maior para o menor
        }
    }else{
        printf("Vc vai estourar a pilha\n");
    }
}

// Função para imprimir a pilha
void printpilha(pilha *p){
  if(!isVazia(p)){  
    printf("[");
    for(int i = 0; i<p->topo; i++){
        printf("%d, ",p->itens[i]);
    }
    printf("%d]\n",peek(p));
  }
}

// Função para realizar a troca de discos entre pinos
int efetuarTrocaDeBases(pilha *p, pilha *p2){
    int flag = 0;  // Indica se a pilha de destino estava inicialmente vazia
    if(isVazia(p2)){
        Push(p2,0);  // Adiciona um valor fictício para facilitar a verificação
        flag = 1;
    }
    if((peek(p2) < peek(p) && !flag)){  // Verifica se o disco no topo da pilha de destino é menor
        return 0;  // Troca inválida
    }else{
        if(flag){
            p2->topo--;  // Remove o valor fictício
        }
        if(!isVazia(p)){
            int aux = pop(p);  // Remove o disco da pilha de origem
            Push(p2,aux);  // Adiciona o disco na pilha de destino
            return 1;  // Troca realizada com sucesso
        }else{
            return 0;
        }
    }
}

// Função principal do jogo
void jogarJogo(pilha *p,pilha *p2,pilha *p3){
    int onde, ir, ganhou = 1, contadorDeJogadas = 0;
    int quantidade = p->topo;  // Número de discos no pino inicial
    printf("Numero ideal de Jogadas:%0.0f\n", (pow(2,quantidade) - 1));  // Calcula o número mínimo de jogadas
    
    do{
        printf("Numero De Jogadas Feitas:%d\n",contadorDeJogadas++);
        printf("Pilha 1:\n");
        printpilha(p);
        printf("Pilha 2:\n");
        printpilha(p2);
        printf("Pilha 3:\n");
        printpilha(p3);
        printf("\n\n");
        printf("Qual torre vc quer tirar?");
        scanf("%d",&onde);
        printf("Qual torre vc quer colocar?");
        scanf("%d",&ir);
        
        // Troca de discos entre pinos conforme a escolha do usuário
        if(onde == 1 && ir == 2){
            if(!efetuarTrocaDeBases(p,p2)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else if(onde == 1 && ir == 3){
            if(!efetuarTrocaDeBases(p,p3)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else if(onde == 2 && ir == 1){
            if(!efetuarTrocaDeBases(p2,p)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else if(onde == 2 && ir == 3){
            if(!efetuarTrocaDeBases(p2,p3)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else if(onde == 3 && ir == 1){
            if(!efetuarTrocaDeBases(p3,p)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else if(onde == 3 && ir == 2){
            if(!efetuarTrocaDeBases(p3,p2)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
        }else{
            printf("Digite Certo! Não tem sentido tirar um disco e colocá-lo no mesmo lugar!\n");
        }

        // Verifica se o jogo foi concluído
        if(p2->topo == quantidade || p3->topo == quantidade){
            ganhou = 0;  // Jogo concluído
            printf("\n\nParabens!!!! Ganhou!!!!\n\n");
        }
    }while(ganhou);
}

// Função principal para iniciar o programa
int main()
{
    pilha Pinos, Pinos2, Pinos3;  // Declaração de três pilhas representando os três pinos
    int QuantidadeDisco, escolha;
        
    while(1){
        iniciador(&Pinos);
        iniciador(&Pinos2);
        iniciador(&Pinos3);
        printf("O que quer fazer?\n1- Jogar \nDiferente de 1- Sair!\n");
        scanf("%d", &escolha);
        if(escolha == 1){
            printf("Quantidade de Discos no jogo!?\n");
            scanf("%d",&QuantidadeDisco);
            preencherPilha(&Pinos, QuantidadeDisco);  // Inicializa a pilha inicial com discos
            jogarJogo(&Pinos, &Pinos2, &Pinos3);  // Inicia o jogo
        }else{
            break;  // Encerra o programa
        }
    }
    
    return 0;
}
