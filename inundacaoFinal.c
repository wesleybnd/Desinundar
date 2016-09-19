#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#define MICRO_PER_SECOND 1000000 
typedef struct matriz{
    int status;
    int modificado;
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

Matriz **inserirMatriz(Matriz **matriz, int n){
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
            matriz[i][j].modificado = 0;
        }
    }
    return matriz;
}


void imprime(Matriz **matriz, int n){
int i,j;
    for(i =0; i < n; i++){
            for(j =0; j < n; j++){
                printf("%d ",matriz[i][j].cor);
            }
            printf("\n");
    }
}

int corMaiorPeso(int vetorCores[], int qtdCores, int corAtual){
    int i, cont=0, aux =0;
    for( i = 0 ; i < qtdCores; i++){
        if(vetorCores[i] > aux){
        	aux = vetorCores[i];
            cont = i;
        }
    }
    return cont;
}

Matriz **verificaProximoDiretaEsquerda(Matriz ** matriz, int vetorCores[], int i , int j, int corAtual){

        if(matriz[i][j+1].cor != corAtual && matriz[i][j+1].status != 1){
             matriz[i][j+1].status = 1;
             vetorCores[matriz[i][j+1].cor]++;
        }
        if(matriz[i+1][j].cor != corAtual && matriz[i+1][j].status != 1){
             matriz[i+1][j].status = 1;
             vetorCores[matriz[i+1][j].cor]++;
        }
return matriz;
}

Matriz **verificaAnteriorDiretaEsquerda(Matriz ** matriz, int vetorCores[], int i , int j, int corAtual){

    if(matriz[i][j-1].cor != corAtual && matriz[i][j-1].status != 1){
        matriz[i][j-1].status = 1;
         vetorCores[matriz[i][j-1].cor]++;
    }
    if(matriz[i-1][j].cor != corAtual && matriz[i-1][j].status != 1){
         matriz[i-1][j].status = 1;
         vetorCores[matriz[i-1][j].cor]++;
    }
return matriz;
}

int *marcar(Matriz **matriz, int i , int j , int n,int vetorCores[], int corAtual){

    if(i == 0){
        if(j == 1){
            matriz = verificaProximoDiretaEsquerda(matriz, vetorCores, i, j, corAtual);

        }else if(j == n-1 ){
            if(matriz[i][j-1].cor != corAtual && matriz[i][j-1].status != 1){
                 matriz[i][j-1].status = 1;
                 vetorCores[matriz[i][j-1].cor]++;
            }
            if(matriz[i+1][j].cor != corAtual && matriz[i+1][j].status != 1){
                matriz[i+1][j].status = 1;
                 vetorCores[matriz[i+1][j].cor]++;
            }
        }else{
            matriz =verificaProximoDiretaEsquerda(matriz, vetorCores, i, j, corAtual);
            if(matriz[i][j-1].cor != corAtual && matriz[i][j-1].status != 1){
                matriz[i][j-1].status = 1;
                vetorCores[matriz[i][j-1].cor]++;
            }
        }
    }else if(i == n-1){
        if(j == 0){
            if(matriz[i][j+1].cor != corAtual && matriz[i][j+1].status != 1){
                 matriz[i][j+1].status = 1;
                 vetorCores[matriz[i][j+1].cor]++;
            }
            if(matriz[i-1][j].cor != corAtual && matriz[i-1][j].status != 1){
                 matriz[i-1][j].status = 1;
                 vetorCores[matriz[i-1][j].cor]++;
            }
        }else if(j == n-1){
            matriz =verificaAnteriorDiretaEsquerda(matriz, vetorCores, i, j, corAtual);

        }else{
            if(matriz[i][j+1].cor != corAtual && matriz[i][j+1].status != 1){
                 matriz[i][j+1].status = 1;
                 vetorCores[matriz[i][j+1].cor]++;
            }
            matriz =verificaAnteriorDiretaEsquerda(matriz, vetorCores, i, j, corAtual);

        }
    }else if(j == 0){
        matriz =verificaProximoDiretaEsquerda(matriz, vetorCores, i, j, corAtual);

        if(matriz[i-1][j].cor != matriz[i-1][j].status != 1){
             matriz[i-1][j].status = 1;
             vetorCores[matriz[i-1][j].cor]++;
        }
    }else if(j == n-1 ){
        matriz =verificaAnteriorDiretaEsquerda(matriz, vetorCores, i, j, corAtual);
        if(matriz[i+1][j].cor != corAtual && matriz[i+1][j].status != 1){
            matriz[i+1][j].status = 1;
             vetorCores[matriz[i+1][j].cor]++;
        }
    }else{
        matriz =verificaProximoDiretaEsquerda(matriz, vetorCores, i, j, corAtual);
        matriz =verificaAnteriorDiretaEsquerda(matriz, vetorCores, i, j, corAtual);
    }
  return vetorCores;
}

int resultadoParcial(int vetorCores[], int n){
int i;
    for(i = 0; i < n ; i++){
    	if(vetorCores[i] != 0) return 1;
    }
    return 0;
}

void visao(Matriz **matriz, int n){
    int i, j;
    for( i = 0; i < n ; i++){
        for( j = 0; j < n ; j++){
            printf("%d ", matriz[i][j].modificado);
        }
        printf("\n");
    }
    printf("\n");
}

Matriz **coloracao(Matriz **matriz, int n ,int corAtual, int cor){
    int i, j;
	for( i = 0; i < n ; i++){
        for( j = 0; j < n ; j++){
            if( i== 0 && j == i){
                matriz[i][j].modificado =1;
                matriz[i][j].cor = cor;
            
            }else if(matriz[i][j].cor == corAtual || matriz[i][j].cor == cor){
                if(i == 0){
                    if(j == n-1){
                        if(matriz[i][j-1].cor == corAtual && matriz[i][j-1].modificado == 1
                                || matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                        if(matriz[i][j-1].cor == cor && matriz[i][j-1].modificado == 1
                                || matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                    }else{
                        if(matriz[i][j+1].cor == corAtual && matriz[i][j+1].modificado == 1
                                || matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1
                                || corAtual && matriz[i][j-1].cor == corAtual && matriz[i][j-1].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                        if(matriz[i][j+1].cor == cor && matriz[i][j+1].modificado == 1
                                || matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1
                                || corAtual && matriz[i][j-1].cor == cor && matriz[i][j-1].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                    }
                }else if(i == n-1){
                    if(j == 0){
                        if(matriz[i][j+1].cor == corAtual && matriz[i][j+1].modificado == 1
                                || matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }

                        if(matriz[i][j+1].cor == cor && matriz[i][j+1].modificado == 1
                                || matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                    }
                    if(j == n-1){
                        if(matriz[i][j-1].cor == corAtual && matriz[i][j-1].modificado == 1
                                || matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                        if(matriz[i][j-1].cor == cor && matriz[i][j-1].modificado == 1
                                || matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                    }
                    else{
                        if(matriz[i][j+1].cor == corAtual && matriz[i][j+1].modificado == 1
                                || matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1
                                || corAtual && matriz[i][j-1].cor == corAtual && matriz[i][j-1].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                        if(matriz[i][j+1].cor == cor && matriz[i][j+1].modificado == 1
                                || matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1
                                || corAtual && matriz[i][j-1].cor == cor && matriz[i][j-1].modificado == 1){
                            matriz[i][j].modificado = 1;
                        	matriz[i][j].cor = cor;
                        }
                    }
                }else if( j == n-1){
                    if(matriz[i][j-1].cor == corAtual && matriz[i][j-1].modificado == 1
                            || matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                    if(matriz[i][j-1].cor == cor && matriz[i][j-1].modificado == 1
                            || matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                }else if( j == 0){
                    if(matriz[i][j+1].cor == corAtual && matriz[i][j+1].modificado == 1
                            || matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                    if(matriz[i][j+1].cor == cor && matriz[i][j+1].modificado == 1
                            || matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                }else{
                    if(matriz[i][j+1].cor == corAtual && matriz[i][j+1].modificado == 1
                            || matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == corAtual && matriz[i-1][j].modificado == 1
                            || corAtual && matriz[i+1][j].cor == corAtual && matriz[i+1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                    if(matriz[i][j+1].cor == cor && matriz[i][j+1].modificado == 1
                            || matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1
                            || corAtual && matriz[i-1][j].cor == cor && matriz[i-1][j].modificado == 1
                            || corAtual && matriz[i+1][j].cor == cor && matriz[i+1][j].modificado == 1){
                        matriz[i][j].modificado = 1;
                    	matriz[i][j].cor = cor;
                    }
                }
            }
            matriz[i][j].status = 0;
        }
    }
    return matriz;
}


int *zerarVetorCores(int *vetor, int n){
int i =0;
    for(i; i < n;i++){
        vetor[i] =0;
    }
return vetor;
}

int previsaoTermino(Matriz **matriz, int n){
int i, j, cont = matriz[0][0].cor;
    for(i = 0; i < n ; i++){
        for(j = 0; j < n ; j++){
            if(matriz[i][j].cor != cont){
                return 0;
            }
        }
    }
    return 2;
}

Matriz **desinundar(Matriz **matriz, int n, int qtdCores){
    struct timeval start_time;
    struct timeval stop_time;
    float time_diff; 
    gettimeofday( &start_time, NULL );
    int i=0, j=0,y=0,x=0,cont;
    int corAtual = matriz[0][0].cor;
    int vetorCores[qtdCores];
    int resultado=0;
    float tmili;
    zerarVetorCores(vetorCores, qtdCores);
    printf("%d ", matriz[0][0].cor);
    while(1){
    	
    	y++;
        i++;
        if( y == i && i == n){
            j++;
            x = j;
            y = j;
            i = j;
            if( j == n){
                x = 0; 
                y = 1;
                i = 1;
                j = 0;
            }
            if(matriz[i][j].cor != corAtual) vetorCores[matriz[i][j].cor]++;
            marcar(matriz,i,j,n,vetorCores,corAtual);
            resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
            if(resultado == corAtual){
                vetorCores[resultado] = 0;
                resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
            }
            	if(resultadoParcial(vetorCores,qtdCores) == 0){
    	            if(previsaoTermino(matriz, n)==2){
		                break;
		            }
          		 }else{
          		 	matriz = coloracao(matriz, n, corAtual, resultado);
          		 }
        }else{
                if(i+1 > n){
                    i=0;
                    j++;
                }
                if( j+1 > n){
                    j=0;
                }
                if( y+1 > n){
                    y=1;
                    x++;
                }
                if(x+1 > n){
                    x=0;
                }
            if (matriz[i][j].cor == matriz[x][y].cor && matriz[i][j].cor != corAtual){
                matriz[i][j].modificado = 1;
                matriz[x][y].modificado = 1;
                resultado = matriz[i][j].cor;
                vetorCores[1] = 1;
                coloracao(matriz, n, corAtual, matriz[i][j].cor);

            }else if (matriz[i][j].cor == matriz[x][y].cor && matriz[i][j].cor == corAtual){
            	matriz[i][j].modificado = 1;
                matriz[x][y].modificado = 1;
                coloracao(matriz, n, corAtual, matriz[i][j].cor);
                vetorCores[matriz[i][j].cor]++;
                resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
     
            }else if(matriz[i][j].cor != matriz[x][y].cor){
               if(matriz[i][j].cor != corAtual)vetorCores[matriz[i][j].cor]++;
               if(matriz[x][y].cor != corAtual)vetorCores[matriz[x][y].cor]++;
               marcar(matriz,i,j,n,vetorCores,corAtual);
               marcar(matriz,x,y,n,vetorCores,corAtual);
               resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
               if(resultado != matriz[x][y].cor && resultado != matriz[i][j].cor){
                    vetorCores[resultado] = 0;
                    resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
               }
               if(vetorCores[resultado] != 0) matriz = coloracao(matriz, n, corAtual, resultado);               
            }
        }
            if(resultadoParcial(vetorCores,qtdCores) == 0){
            	continue;
            }            
            (int *)zerarVetorCores(vetorCores, qtdCores);

            if(resultado != corAtual)printf("- %d ",corAtual);    
            corAtual = resultado;        
     }
    printf("\n");
    gettimeofday( &stop_time, NULL );
    time_diff = (float)(stop_time.tv_sec - start_time.tv_sec);
    time_diff += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND; 
    printf("\nfuncao executada em %f ms\n",time_diff);
    return matriz;
}

int main(){
    int n, qtdCores,op;
    scanf("%d %d",&n, &qtdCores);
    setbuf(stdin,NULL);
    Matriz **matriz = criarMatriz(n);
    printf("\nQual modo deseja:\n1 - aleatorio\n2-Manual\nopcao: ");
    scanf("%d",&op);
    inserirModoRandom(matriz, n, qtdCores);
     
    if(op == 1){
        inserirModoRandom(matriz, n, qtdCores);
    }else{
        printf("insira as cores correspondentes à coluna e linha:\n");
        inserirMatriz(matriz, n);
    }    
    desinundar(matriz, n, qtdCores);
return 0;
}
