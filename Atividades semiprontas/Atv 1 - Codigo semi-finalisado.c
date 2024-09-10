/* Simulação de Torneio de Pedra-Papel-Tesoura com Fila
Desenvolva uma simulação de um torneio de Pedra-Papel-Tesoura onde os jogadores competem
em pares e os vencedores continuam para a próxima rodada. Utilize uma fila para organizar os
jogadores. A cada rodada, dois jogadores são removidos da fila e competem entre si. O vencedor
da partida deve retornar ao final da fila, enquanto o perdedor é eliminado do torneio. O processo
continua até que reste apenas um jogador na fila, que será o campeão do torneio. Por exemplo,
se a fila inicial tiver 8 jogadores, o algoritmo deve continuar removendo pares de jogadores,
competindo, e reordenando os vencedores até que reste apenas um vencedor final.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Max 10

/*TABELA DE TIPO:
    1- Papel
    2- Tisoura
    3- Pedra
*/


// Criando uma struct para poder Guardar os nomes
typedef struct{
    char nome[Max];
}Jogadore;

typedef struct{
    Jogadore Jogadores[Max];
    int comeco,fim,tamanho;
    int itens[Max];
}fila;

void inicializar(fila *f){
    f->tamanho = 0;
    f->comeco = 0;
    f->fim = -1;
}

int isVazia(fila *f){
    return (f->tamanho == 0);
}

int isFull(fila *f){
    return (f->tamanho == Max);
}

void Enqueue(fila *f, int estilo){
    if(!isFull(f)){
        f->fim++;
        if((f->fim) == Max){
            (f->tamanho++);
            f->fim = 0;
            f->itens[f->fim] = estilo;
        }else{
            f->tamanho++;
            f->itens[(f->fim)] = estilo;
        }
    }else{
        printf("A fila está cheia");    
    }
}

int Dequeue(fila *f){
    if(!isVazia(f)){
        int v = f->itens[f->comeco];
        f->comeco++;
        if((f->comeco) == Max){
            f->tamanho--;
            f->comeco = 0;
            return v;
        }else{
            f->tamanho--;
            return v;
        }
    }else{
        printf("A fila está vazia\n");
        return -1;
    }
}

int peek(fila *f){
    if(!isVazia(f)){
        return f->itens[f->comeco];
    }else{
        return -1;
    }
}

// Começando a Fazer as funções para manipular a  lista

void AdicionarJogador(fila *f, Jogadore *j, int estilo){
    if(!isFull(f)){
        Enqueue(f,estilo);
        f->Jogadores[f->fim] = *j;
    }else{
        printf("A fila está cheia");
    }
}

void AdicionarVencedores(fila *f, fila *f2, int indice){
    if(!isFull(f)){
        Enqueue(f,f2->itens[indice]);
        f->Jogadores[f->fim] = f2->Jogadores[indice];
    }else{
        printf("A fila está cheia");
    }
}

void AdicionarOUltimo(fila *f, fila *f2){
    if(!isFull(f)){
        Enqueue(f,f2->itens[f->fim]);
        f->Jogadores[f->fim] = f2->Jogadores[f2->fim];
    }else{
        printf("A fila está cheia\n");
    }
}

char *RemoverJogador(fila *f){
    int x = f->comeco;
    Dequeue(f);
    return f->Jogadores[x].nome;
}

void PopularRivais(fila *f, int Jogadores){
    int a;
    if(f->tamanho + Jogadores <= Max){
        for(int i = 0; i < Jogadores;i++){
            Jogadore j;
            int tipo;
            a = (rand() % 4) + 1;
            switch(a){
                case 1:
                    strcpy(j.nome,"Julia");
                    tipo = (rand() % 3) + 1;
                    AdicionarJogador(f,&j, tipo);
                break;
                
                case 2:
                    strcpy(j.nome,"Pedro");
                    tipo = (rand() % 3) + 1;
                    AdicionarJogador(f,&j, tipo);
                break;
                
                case 3:
                    strcpy(j.nome,"Joao");
                    tipo = (rand() % 3) + 1;
                    AdicionarJogador(f,&j, tipo);
                break;
                
                case 4:
                    strcpy(j.nome,"Lucas");
                    tipo = (rand() % 3) + 1;
                    AdicionarJogador(f,&j, tipo);
                break;
            }
        }
    }else{
        printf("Vc vai estourar a fila\n");
    }
}

void mostrarJogadores(fila *f) {
    int cont, i;

    for (cont = 0, i = f->comeco; cont < f->tamanho; cont++) {
        printf("Jogadores: %s - Tipo de jogada:%d \n",f->Jogadores[i].nome, f->itens[i++]);
        if (i == f->tamanho+1)
            i = 0;
    }
    printf("\n\n");
}

void chaveamento(fila *f, fila *temporaria, int rodadas){
    int cont, i, i2;
    if(!isVazia(f)){
        printf("Rodada : %d\n", rodadas++);
        for (cont = 0, i = f->comeco; cont < f->tamanho; cont+=2) {
            if(i+1 >= Max){
                i2 = 0;
            }else if(i+1 > f-> tamanho){
                break;
            }else{
                i2 = i+1;
            }
            
            /*TABELA DE TIPO:
              1- Papel
              2- Tisoura
              3- Pedra
            */
            do{
                    if(f->itens[i] == 1 &&  f->itens[i2] == 2){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i2].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i2);
                        break;
                    }else if(f->itens[i] == 1 &&  f->itens[(i2)] == 3){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i);
                        break;
                    }else if(f->itens[i] == 2 &&  f->itens[(i2)] == 3){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i2].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i2);
                        break;
                    }else if(f->itens[i] == 2 &&  f->itens[i2] == 1){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i);
                        break;
                    }else if(f->itens[i] == 3 &&  f->itens[(i2)] == 1){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i2].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i2);
                        break;
                    }else if(f->itens[i] == 3 &&  f->itens[(i2)] == 2){
                        printf("Vencedor do confronto: %s, entre %s e %s\n",f->Jogadores[i].nome,f->Jogadores[i2].nome,f->Jogadores[i].nome);
                        AdicionarVencedores(temporaria,f,i);
                        break;
                    }else{
                        int a = (rand() % 3)+1, a2 = (rand() % 3) + 1;
                        f->itens[i] = a;
                        f->itens[i2] = a2;
                    } 
            }while(1);
            
            i+=2;
            if (i > Max){
                i -= f->tamanho;
            }
        }
        if(f->tamanho % 2 != 0){
            AdicionarOUltimo(temporaria,f);
        }
        *f = *temporaria;
        
        if(f->tamanho != 1){
          inicializar(temporaria);
          chaveamento(f,temporaria,rodadas);
        }else{
            printf("O vencedor da competição foi: %s\n",f->Jogadores[f->comeco].nome);
        }
    }else{
        printf("Lista Vazia\n");
    }
}

int main()
{
    int escolha,tipo;
    fila FilaPrincipal, FilaPlaceHolder;
    char *JogadorRetirado;
    Jogadore J;
    inicializar(&FilaPrincipal);
    inicializar(&FilaPlaceHolder);
    srand(time(NULL));
    while(1){
        printf("O que vc quer fazer?\n1-Adicionar Jogador\n2-Remover Jogador\n3-Colocar Competidores Da Vizinhança\n4-Mostrar Fila\n5-Começar a competição\n");
        scanf("%d",&escolha);
        if(escolha == 1){
            printf("Qual o Nome do Jogador e o tipo, respectivamente de jogada seguindo a tabela. Lembre que o tipo é inteiro, então em caso de palavra ira acabar com o codigo\n");
            scanf("\n%[^\n]",J.nome);
            scanf("%d",&tipo);
            if(tipo == 1 || tipo == 2 || tipo == 3){
                AdicionarJogador(&FilaPrincipal,&J,tipo);
            }else{
                printf("Escolha certo!!\n");
            }
        }else if(escolha == 2){
            JogadorRetirado = RemoverJogador(&FilaPrincipal);
            printf("Nome do Jogador Removido: %s\n",JogadorRetirado);
        }else if(escolha == 3){
            printf("Quantidade De Jogadores Que vc quer inserir?(Lembre que o tipo é inteiro)\n");
            scanf("%d",&escolha);
            if(escolha < 0){
                printf("Coloque um numero Positivo");
            }else{
                PopularRivais(&FilaPrincipal,escolha);
            }
        }else if(escolha == 4){
            mostrarJogadores(&FilaPrincipal);
        }else if(escolha == 5){
            inicializar(&FilaPlaceHolder);
            chaveamento(&FilaPrincipal, &FilaPlaceHolder,0);
        }else{
            break;
        }
    }
    return 0;
}