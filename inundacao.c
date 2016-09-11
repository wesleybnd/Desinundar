#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct matriz{
    int status;
    int cor;
}Matriz;

Matriz **criarMatriz(int n){
int i;
Matriz **matriz = (Matriz **)malloc(sizeof(Matriz*)*n);
assert(matriz);

    for(i = 0; i < n; i++){
        matriz[i] = (Matriz *)malloc(sizeof(Matriz)*n);
        assert(matriz);
    }
    return matriz;
}

Matriz** inserirMatriz(Matriz **matriz, int n){
    int i,j,x;
    for (i =0; i < n; i++){
        printf("\nCOLUNA %d\n",i);
        for (j =0; j < n; j++){
            printf("LINHA: %d -- ",j);
            scanf("%d",&x);
            matriz[i][j].cor = x;
            matriz[i][j].status = 0;
        }
    }
    return matriz;
}

Matriz **inserirModoRandom(Matriz **matriz, int n, int qtdCores){
    int i,j,x,ale;
    for (i =0; i < n; i++){
        for (j =0; j < n; j++){
            ale = rand()%qtdCores;
            matriz[i][j].cor = ale;
            matriz[i][j].status = 0;
        }
    }
    return matriz;
}

void imprimirCores(char **cores[], int n){
    int i;
    printf("As cores escolhidas foram...\n");

        for (i =0; i < n ; i++){
            if(n > 10){
                printf("POR FAVOR REINICIE O PROGRAMA E ESCOLHA UMA QUANTIDADE MENOR DE CORES!");
                exit(1);
            }
            printf("%d -%s\n",i,cores[i]);
        }
}

void imprime(Matriz **matriz, int n){
int i,j;
    for(i =0; i <n; i++){
            for(j =0; j < n; j++){
                printf("%d ",matriz[i][j].cor);
            }
            printf("\n");
    }
}

int corMaiorPeso(int vetorCores[], int qtdCores, int corAtual){
    int i, cont=0;

    for( i = 0 ; i < qtdCores; i++){
        if(vetorCores[i] >= cont){
            cont = i;
        }
    }
    return cont;
}

int *marcar(Matriz **matriz, int i , int j , int n,int vetorCores[], int corAtual, int qtdCores){
    if(i == 0 && j != 0){
        if(j == 1){

            if(matriz[i][j+1].cor != corAtual){
                 vetorCores[matriz[i][j+1].cor]++;
            }
            if(matriz[i+1][j].cor != corAtual){
                 vetorCores[matriz[i+1][j].cor]++;
            }
        }else if(j == n-1){
            if(matriz[i][j-1].cor != corAtual){
                 vetorCores[matriz[i][j-1].cor]++;
            }
            if(matriz[i+1][j].cor != corAtual){
                 vetorCores[matriz[i+1][j].cor]++;
            }
        }else{
            if(matriz[i][j+1].cor != corAtual){
                 vetorCores[matriz[i][j+1].cor]++;
            }
            if(matriz[i+1][j].cor != corAtual){
                 vetorCores[matriz[i+1][j].cor]++;
            }
            if(matriz[i][j-1].cor != corAtual){
                 vetorCores[matriz[i][j-1].cor]++;
            }
        }
    }else if(i == n-1){
        if(j == 0){
            if(matriz[i][j+1].cor != corAtual){
                 vetorCores[matriz[i][j+1].cor]++;
            }
            if(matriz[i-1][j].cor != corAtual){
                 vetorCores[matriz[i-1][j].cor]++;
            }
        }else if(j == n-1){
            if(matriz[i][j-1].cor != corAtual){
                 vetorCores[matriz[i][j-1].cor]++;
            }
            if(matriz[i-1][j].cor != corAtual){
                 vetorCores[matriz[i-1][j].cor]++;
            }
        }else{
            if(matriz[i][j+1].cor != corAtual){
                 vetorCores[matriz[i][j+1].cor]++;
            }
            if(matriz[i-1][j].cor != corAtual){
                 vetorCores[matriz[i-1][j].cor]++;
            }
            if(matriz[i][j-1].cor != corAtual){
                 vetorCores[matriz[i][j-1].cor]++;
            }
        }
    }else if((i > 0 && i < n-1) && j == 0 ){
        if(matriz[i][j+1].cor != corAtual){
             vetorCores[matriz[i][j+1].cor]++;
        }
        if(matriz[i-1][j].cor != corAtual){
             vetorCores[matriz[i-1][j].cor]++;
        }
        if(matriz[i+1][j].cor != corAtual){
             vetorCores[matriz[i+1][j].cor]++;
        }

    }else if((i > 0 && i < n-1) && j == n-1 ){
        if(matriz[i][j-1].cor != corAtual){
             vetorCores[matriz[i][j-1].cor]++;
        }
        if(matriz[i-1][j].cor != corAtual){
             vetorCores[matriz[i-1][j].cor]++;
        }
        if(matriz[i+1][j].cor != corAtual){
             vetorCores[matriz[i+1][j].cor]++;
        }

    }else{
         if(matriz[i][j-1].cor != corAtual){
             vetorCores[matriz[i][j-1].cor]++;
        }
        if(matriz[i][j+1].cor != corAtual){
             vetorCores[matriz[i][j+1].cor]++;
        }
        if(matriz[i-1][j].cor != corAtual){
             vetorCores[matriz[i-1][j].cor]++;
        }
        if(matriz[i+1][j].cor != corAtual){
             vetorCores[matriz[i+1][j].cor]++;
        }
    }
  return vetorCores;
}

void resultadoParcial(int vetorCores[], int n){
int i;
    for(i = 0; i < n ; i++){
        printf("%d = %d\n",i,vetorCores[i]);
    }
    printf("\n");
}

Matriz **desinundar(Matriz **matriz, int n, int qtdCores){
    int i=0, j=0,aux =0;
    int corAtual = matriz[0][0].cor;
    int vetorCores[qtdCores];
    int resultado;

    for(i; i < qtdCores;i++){
        vetorCores[i] =0;
    }
    i=0;
    while(1){
        if(matriz[i][j+1].cor != matriz[i+aux+1][j].cor){
            if(matriz[i][j+1].cor == corAtual){
                if(j+1 < n-1){
                    j++;
                    continue;
                }
            }
            if(matriz[i+aux+1][j].cor == corAtual){
                if(aux+1 < n-1){
                    aux++;
                    continue;
                }
            }
           marcar(matriz,i,j+1,n,vetorCores,corAtual,qtdCores);
           resultadoParcial(vetorCores, qtdCores);
           marcar(matriz,i+aux+1,j,n,vetorCores,corAtual,qtdCores);
           resultadoParcial(vetorCores, qtdCores);
           resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
           if(resultado == 1){
                printf("COR ESCOLHIDA: %d",matriz[i][j+1].cor);
           }else{
                printf("COR ESCOLHIDA 3: %d",resultado);
           }
           exit(1);
        }else if (matriz[i][j+1].cor == matriz[i+aux+1][j].cor && matriz[i+aux+1][j].cor != corAtual){
           printf("A COR ESCOLHIDA: %d", matriz[i][j+1].cor);
           exit(1);
        }else if (matriz[i][j+1].cor == matriz[i+aux+1][j].cor && matriz[i+aux+1][j].cor == corAtual){
            i++;
        }
    }
    return matriz;
}

int main(){
    int n, qtdCores,op;
    char *cores[11][10] = {"amarelo","verde","vermelho","azul","branco","rosa","marrom","preto","violeta","cinza","bronze"};
    qtdCores = 7;
    n = 10;

   // scanf("%d %d",&n, &qtdCores);
    //setbuf(stdin,NULL);
    imprimirCores(cores, qtdCores);
    Matriz **matriz = criarMatriz(n);
    //printf("\nQual modo deseja:\n1 - aleatorio\n2-Manual\nopcao: ");
    //scanf("%d",&op);
     inserirModoRandom(matriz, n, qtdCores);
     /*
    if(op == 1){
        inserirModoRandom(matriz, n, qtdCores);
    }else{
        printf("insira as cores correspondentes aos numeros\n");
        inserirMatriz(matriz, n);
    }
    */
    imprime(matriz,n);
    desinundar(matriz, n, qtdCores);
return 0;
}
