#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

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
    	//printf("%d = %d\n",i, vetorCores[i]);
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
       //     printf("%d ", matriz[i][j].modificado);
        }
        //printf("\n");
    }
   // printf("\n");
}

Matriz **coloracao(Matriz **matriz, int n ,int corAtual, int cor){
    int i, j;
	//printf("mardita cor atual = %d \ncor escolhida: %d\n\n", corAtual, cor);
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
            //if(matriz[i][j].modificado == 1) printf("modificou: j = %d i = %d\n",j,i);
            matriz[i][j].status = 0;
        }
    }
     //printf("saiu coloracao\n");
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
    int i=0, j=0,y=0,x=0,cont;
    int corAtual = matriz[0][0].cor;
    int vetorCores[qtdCores];
    int resultado=0;
    zerarVetorCores(vetorCores, qtdCores);
    imprime(matriz , n);
    while(1){
    	
    	y++;
        i++;
        //printf("\nvalor do i = %d\nvalor do j = %d",i,j);
	    //printf("\nvalor do x = %d\nvalor do y = %d\n\n",x,y);
        if( y == i && i == n){
            j++;
            x = j;
            y = j;
            i = j;
            if( j == n){
            	x = y = i = j = 0;
            }
            if(matriz[i][j].cor != corAtual) vetorCores[matriz[i][j].cor]++;

            marcar(matriz,i,j,n,vetorCores,corAtual);
            resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
            //printf("resultado dentro do final = %d\n",resultado );
            if(resultado == corAtual){
                vetorCores[resultado] = 0;
                resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
            }
            	if(resultadoParcial(vetorCores,qtdCores) == 0){
            	 //printf("verificacao de saida\n");
		            if(previsaoTermino(matriz, n)==2){
		          //      printf("verificacao de saida 2\n");
		                break;
		            }
          		 }else{
          		 	matriz = coloracao(matriz, n, corAtual, resultado);
          		 }
                
            	continue;

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
               //printf("pontuacao i e j = %d\nPontuacao x e y = %d\n",vetorCores[matriz[i][j].cor],
               	//													 vetorCores[matriz[i][j].cor]);
               //printf("resultado = %d\n",resultado);

            }else if(matriz[i][j].cor != matriz[x][y].cor){
               if(matriz[i][j].cor != corAtual)vetorCores[matriz[i][j].cor]++;
               if(matriz[x][y].cor != corAtual)vetorCores[matriz[x][y].cor]++;
               //printf("cor atualissima = %d\n",corAtual );
               marcar(matriz,i,j,n,vetorCores,corAtual);
               marcar(matriz,x,y,n,vetorCores,corAtual);
               resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
               /*printf("pontuacao i e j = %d\nPontuacao x e y = %d\n",matriz[i][j].cor,
               														 matriz[x][y].cor);
               printf("resultado = %d\n",resultado);*/
               if(resultado != matriz[x][y].cor && resultado != matriz[i][j].cor){
                    //printf("CAGADA\n");
                    vetorCores[resultado] = 0;
                    resultado = corMaiorPeso(vetorCores, qtdCores, corAtual);
               }
               if(vetorCores[resultado] != 0) matriz = coloracao(matriz, n, corAtual, resultado);
               
               
            }
        }
            if(resultadoParcial(vetorCores,qtdCores) == 0){
            	continue;
            }

    //        printf("COR ATUAL = %d\n",corAtual);	    	
	  //      imprime(matriz , n);
	    //    printf("\n\n");
          //  visao(matriz, n);            
            corAtual = resultado;
            (int *)zerarVetorCores(vetorCores, qtdCores);
            //printf("--------------------------------------------------------\n");
           
         //  getchar();
     }
     printf("\n\nNOVA\n");
	imprime(matriz , n);
    return matriz;
}

int main(){
    int n, qtdCores,op;
    char *cores[11][10] = {"amarelo","verde","vermelho","azul","branco","rosa","marrom","preto","violeta","cinza","bronze"};
    qtdCores = 12;
    n =40;

   // scanf("%d %d",&n, &qtdCores);8
    //setbuf(stdin,NULL);
    //imprimirCores(cores, qtdCores);
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
    desinundar(matriz, n, qtdCores);
return 0;
}
