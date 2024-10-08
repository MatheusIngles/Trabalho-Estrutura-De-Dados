/*Implemente uma simulação do jogo Pinos de Hanói, onde o objetivo é mover uma pilha de discos
de um pino para outro seguindo regras específicas: apenas um disco pode ser movido por vez, e
um disco maior não pode ser colocado sobre um disco menor. Utilize pilhas para representar
cada um dos três pinos, onde os discos são empilhados do maior (na base) ao menor (no topo).
Comece com todos os discos no pino inicial e mova-os para o pino de destino, utilizando o pino
auxiliar, se necessário. O jogo deve respeitar a regra de que um disco maior não pode ser
colocado sobre um disco menor.
Por exemplo, se o pino inicial contém os discos [3, 2, 1], o objetivo é movê-los para o pino de
destino, utilizando o pino auxiliar conforme as regras do jogo.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define Max 10

typedef struct{
    int topo, itens[Max];
}pilha;

void iniciador(pilha *p){
    p->topo = -1;
}

int isVazia(pilha *p){
    return p->topo == -1;
}

int IsFull(pilha *p){
    return p->topo == Max - 1;
}

void Push(pilha *p, int valor){
    if(IsFull(p)){
        printf("A pilha está cheia!\n");
    }else{
        p->topo++;
        p->itens[p->topo] = valor;
    }
}

int pop(pilha *p){
    if(isVazia(p)){
        printf("A pilha já está vazia\n");
        return -1;
    }else{
        return p->itens[(p->topo--)];
    }
}

int peek(pilha *p){
    return p->itens[p->topo];
}

// Começando o exercicio 

void preencherPilha(pilha *p, int QuantidadeDisco){
    if(QuantidadeDisco <= Max){
        for(int i = QuantidadeDisco;i>0;i--){
            Push(p,i);
        }
    }else{
        printf("Vc vai estourar a pilha\n");
    }
}

/*void printarTorres(pilha *p, int quantidade){
    for(int i = Max; 0 < i; i--){
        if(p->topo < i){
            for(int j = quantidade; j > 0; i-- ){
                printf(" ");
                if(j = 1)
                    printf("\n");
            }
        }else{
            
        }
    }
}
*/

void printpilha(pilha *p){
  if(!isVazia(p)){  
    printf("[");
    for(int i = 0; i<p->topo;i++){
        printf("%d, ",p->itens[i]);
    }
    printf("%d]\n",peek(p));}
}

int pegarTopo(pilha *p){
    if(!isVazia(p)){
        return p->topo;
    }
}

/*void printilha(pilha *p,int quantidade){
    for(int i = Max, j=quantidade;i > 0; i--,j-=2){
        if(p->topo > i){
            int k = j-(i*2);
            int referencia = k-2;
            int l = (j-referencia)/2;
            for(; k >= 0; k--){
                if(k<l){
                    printf(" ");
                }else if(k <= referencia && k>=l){
                    printf("%d", p->itens[i]);
                } else {
                    printf(" ");
                }
                
                if(k==0){
                    printf("\n");
                }
            }
        }else{
            j=quantidade;
        }
        if(i==Max -1){
            printf("\n\n");
        }
    }
    
}
*/
int efetuarTrocaDeBases(pilha *p, pilha *p2){
    int flag = 0;
    if(isVazia(p2)){
        Push(p2,0);
        flag = 1;
    }
    if((peek(p2) < peek(p) && !flag)){
        return 0;
    }else{
        if(flag){
            p2->topo--;
        }
        int aux = pop(p);
        Push(p2,aux);
        return 1;
    }
}

void jogarJogo(pilha *p,pilha *p2,pilha *p3){
    int onde,ir, ganhou = 1, contadorDeJogadas = 0;
    int quantidade = p->topo;
    printf("Numero ideal de Jogadas:%0.0f\n", (pow(2,quantidade) - 1));
    
    while(ganhou){
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
        
        if(onde == 1 && ir == 2){
            if(!efetuarTrocaDeBases(p,p2)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else if(onde == 1 && ir == 3){
            if(!efetuarTrocaDeBases(p,p3)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else if(onde == 2 && ir == 1){
            if(!efetuarTrocaDeBases(p2,p)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else if(onde == 2 && ir == 3){
            if(!efetuarTrocaDeBases(p2,p3)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else if(onde == 3 && ir == 1){
            if(!efetuarTrocaDeBases(p3,p)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else if(onde == 3 && ir == 2){
            if(!efetuarTrocaDeBases(p3,p2)){
                printf("Não pode colocar o disco maior, já que o outro pino possui um disco menor\n");
            }
            if(p2->topo == quantidade || p3->topo == quantidade){
                ganhou = 0;
            }
        }else{
            printf("Digite Certo! Não tem sentido tirar um disco e colocalo no mesmo lugar\n!");
        }
        
    };
}

int main()
{
    pilha Pinos, Pinos2, Pinos3;
    int QuantidadeDisco, escolha;
    iniciador(&Pinos);
    iniciador(&Pinos2);
    iniciador(&Pinos3);
    
    while(1){
        printf("O que quer fazer?\n1- Jogar \nDiferente de 1- Sair!\n");
        scanf("%d", &escolha);
        if(escolha ==1){
            printf("Quantidade de Discos no jogo!?\n");
            scanf("%d",&QuantidadeDisco);
            preencherPilha(&Pinos,QuantidadeDisco);
            jogarJogo(&Pinos,&Pinos2,&Pinos3);
        }else{
            break;
        }
    }
    
    return 0;
}
