#include<stdio.h>
#include<string.h>
#define MAXIMO 100

int main(){
	
	int matrizA[20][20]; //Primera matriz
	int matrizB[20][20]; //Segunda matriz
	int matrizC[20][20]; //Tercera matriz
	int matrizD[20][20]; //matriz que almacena las nuevas posiciones para calcular la inversa
	float matrizE[20][20]; //matriz resultante de la inversa
	
	int nFilasA; //numero de filas de la matriz A
	int nColnA; //numero de columnas de la matriz A
	int nFilasB; //numero de filas de la matriz B
	int nColnB; //numero de columnas de la matriz B
	
	int i,j,k; //contadores de los bucles
	int opcion; //opcion del menu
	int operacion; //operacion de suma o resta que eliga el usuario
	float determinante; //determinante de la matriz
	float constante; //constante por la que se debe multiplicar la matriz para calcular la inversa
	
	printf("------------------------------------------------------------\n");
	printf("     PROGRAMA QUE REALIZA OPERACIONES CON MATRICES\n");
	printf("------------------------------------------------------------\n");
	printf("Autor: Bryan Mendoza\n");
	
	
	do{
		printf(".......................................................\n");
		printf("                  M E N U   D E    O P C I O N E S\n");
		printf(".......................................................\n");
		printf("\n");
		printf("1. Suma/Resta de matrices\n");
		printf("2. Producto de matrices\n");
		printf("3. Inversa de matrices\n");
		printf("4. Salir\n");
		printf("Seleccione una opcion:\n");
		scanf("%d",&opcion);
				
		switch(opcion){
			case 1: //Suma
				printf("Ingrese el numero de filas de la matrices:\n");
				scanf("%d",&nFilasA);
					printf("Ingrese el numero de columnas de la matrices:\n");
				scanf("%d",&nColnA);
				
				printf("Primer Matriz\n");
				for(i=1;i<=nFilasA;i++){
					for (j=1;j<=nColnA;j++){
						printf("Ingrese el elemento %d, %d :",i,j);
						scanf("%d",&matrizA[i][j]);
					}
				}
				
				printf("La primera matriz es:\n");
					for(i=1;i<=nFilasA;i++){
						printf("|");
						for(j=1;j<=nColnA;j++){
							printf("%d  ",matrizA[i][j]);
						}
						printf("|\n");
					}
				
				printf("Segunda Matriz\n");	
				for(i=1;i<=nFilasA;i++){
					for(j=1;j<=nColnA;j++){
						printf("Ingrese el elemento %d, %d :",i,j);
						scanf("%d",&matrizB[i][j]);
					}
				}
				
				printf("La segunda matriz es:\n");
				for(i=1;i<=nFilasA;i++){
					printf("|");
					for(j=1;j<=nColnA;j++){
						printf("%d  ",matrizB[i][j]);
					}
						printf("|\n");
				}
				
				printf("Digite 1 para sumar o 2 para restar\n");
				scanf("%d",&operacion);
				
				if(operacion==1){
					for(i=1;i<=nFilasA;i++)
						for(j=1;j<=nColnA;j++)
							matrizC[i][j]=matrizA[i][j]+matrizB[i][j];
							
					printf("La suma de las matrices es:\n");
					for(i=1;i<=nFilasA;i++){
						printf("|");
						for(j=1;j<=nColnA;j++){
							printf("%d  ",matrizC[i][j]);
						}
						printf("|\n");
					}
				}
				else{
					if(operacion==2){
					for(i=1;i<=nFilasA;i++)
						for(j=1;j<=nColnA;j++)
						matrizC[i][j]=matrizA[i][j]-matrizB[i][j];
					
				printf("La resta de las matrices es:\n");
				for(i=1;i<=nFilasA;i++){
					printf("|");
					for(j=1;j<=nColnA;j++){
						printf("%d  ",matrizC[i][j]);
					}
						printf("|\n");
				}
					}
					else
					printf("Opcion no valida.\n");	
				}
			break;
			
			case 2: //producto
				printf("Ingrese el numero de filas de la matriz A:\n");
				scanf("%d",&nFilasA);
				printf("Ingrese el numero de columnas de la matriz A:\n");
				scanf("%d",&nColnA);
				printf("Ingrese el numero de columnas de la matriz B:\n");
				scanf("%d",&nColnB);
				nFilasB=nColnA;
				
				printf("Primer Matriz\n");
				for(i=1;i<=nFilasA;i++)
					for (j=1;j<=nColnA;j++){
						printf("Ingrese el elemento %d, %d :",i,j);
						scanf("%d",&matrizA[i][j]);
					}
					
				printf("La primera matriz es:\n");
					for(i=1;i<=nFilasA;i++){
						printf("|");
						for(j=1;j<=nColnA;j++){
							printf("%d  ",matrizA[i][j]);
						}
						printf("|\n");
					}
				
				printf("Segunda Matriz\n");	
				for(i=1;i<=nColnA;i++)
					for(j=1;j<=nColnB;j++){
						printf("Ingrese el elemento %d, %d :",i,j);
						scanf("%d",&matrizB[i][j]);
					}
				
				printf("La segunda matriz es:\n");
					for(i=1;i<=nColnA;i++){
						printf("|");
						for(j=1;j<=nColnB;j++){
							printf("%d  ",matrizB[i][j]);
						}
						printf("|\n");
					}
						
				for(i=1;i<=nFilasA;i++)
					for(j=1;j<=nColnB;j++){
						matrizC[i][j]=0;
						for(k=1;k<=nFilasB;k++)
							matrizC[i][j]+=matrizA[i][k]*matrizB[k][j];
					}
					
					printf("El producto de las matrices es:\n");
					for(i=1;i<=nFilasA;i++){
						printf("|");
						for(j=1;j<=nColnB;j++){
							printf("%d  ",matrizC[i][j]);
						}
						printf("|\n");
					}
			break;
			
			case 3: //inversa
				
				printf("Ingrese el numero de filas de la matriz:\n");
				scanf("%d",&nFilasA);
				printf("Ingrese el numero de columnas de la matriz:\n");
				scanf("%d",&nColnA);
				
				if(nFilasA!=nColnA) //condicion segun las filas y columnas ingresadas
					printf("ERROR: No se puede calcular la inversa de una matriz rectangular\n");
				else{
					if(nFilasA==2 && nColnA==2){ //calcula la inversa solo en caso de ser 2x2 la matriz
						for(i=1;i<=nFilasA;i++){
							for(j=1;j<=nColnA;j++){
								printf("Ingrese el elemento %d, %d :",i,j);
								scanf("%d",&matrizA[i][j]);
							}
						}

					determinante=(matrizA[1][1]*matrizA[2][2]-matrizA[1][2]*matrizA[2][1]); //calcula el determinante de la matriz necesario para calcular la inversa
					constante=1/determinante; //constante por la que se debe multiplicar la matriz para calcular la inversa
					
					//Lo siguiente indica las nuevas posiciones de los elementos de la matriz y el signo necesario para calcular la inversa
					matrizD[1][1]=matrizA[2][2];
					matrizD[1][2]=-matrizA[1][2];
					matrizD[2][1]=-matrizA[2][1];
					matrizD[2][2]=matrizA[1][1];
					
					for(i=1;i<=nFilasA;i++)//calcula la inversa
						for(j=1;j<=nColnA;j++)
							matrizE[i][j]=constante*matrizD[i][j];
					
					printf("La inversa de la matriz es:\n");
					for(i=1;i<=nFilasA;i++){ //imprime en pantalla la inversa
						printf("|");
						for(j=1;j<=nColnA;j++){
							printf("%.2f  ",matrizE[i][j]);
						}
						printf("|\n");
					}
					}
					else
						printf("Este programa solo puede calcular la inversa de matrices 2x2\n");
				}		
			break;
			
			case 4: //salir
				printf("Gracias por usar mi programa :\n)");
			break;
			
			default: //si selecciona un numero que no se encuentra en el menu
				printf("Opcion no valida\n"); 
		}
		
	}while(opcion!=4);
	
	return 0;
}
