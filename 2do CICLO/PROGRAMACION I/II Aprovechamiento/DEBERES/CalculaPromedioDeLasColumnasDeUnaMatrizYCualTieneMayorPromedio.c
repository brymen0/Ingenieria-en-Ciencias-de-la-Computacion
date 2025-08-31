#include<stdio.h>

int main(){
	int nfilas; //numero de filas de la matriz
	int ncolumnas; //numero de columnas de la matriz
	int i,j; //contadores del bucle
	int matriz[20][20]; //matriz que almacena los valores
	int suma[j]; //vector que acumula las sumas de los valores de las columnas de la matriz
	float promedio[j]; //vector que almacena los promedio de las columnas
	float promediomayor; //promedio mas alto de las columnas
	int k; //almacena el numero de columna con mayor promedio

	
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("   PROGRAMA QUE LEE UNA MATRIZ, CALCULA EL PROMEDIO DE CADA COLUMNA Y CUAL COLUMNA TIENE MAYOR PROMEDIO\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("Autor: Bryan Mendoza\n\n");
	
	do{ //valida el numero de filas
		printf("Ingrese el numero de la filas de la matriz:");
		scanf("%d",&nfilas);
		if(nfilas<=0)
			printf("ERROR: El numero ingresado de filas es incorrecto.\n");
		if(nfilas%2==1)
			printf("Este programa solo acepta matrices con un numero de filas par\n");
	}while(nfilas<=0 || (nfilas%2==1));
	
	do{ //valida el numero de columnas
		printf("Ingrese el numero de la columnas de la matriz:");
		scanf("%d",&ncolumnas);
		if(ncolumnas<=0)
			printf("ERROR: El numero ingresado de columnas es incorrecto.\n");
	}while(ncolumnas<=0);

	printf("Ingrese los datos de la primera mitad de las filas\nRECUERDE: sus valores deben estar entre 1 y 30\n");
	for(i=1;i<=(nfilas/2);i++)//pide los valores de la mitad de las filas de la matriz
		for(j=1;j<=ncolumnas;j++){
			do{ //valida los valores ingresados
				printf("Ingrese el valor de la posicion %d,%d: ",i,j);
				scanf("%d",&matriz[i][j]);
				if((matriz[i][j]<1) || (matriz[i][j]>30)) 
					printf("ERROR: El valor ingresado esta fuera del rango permitido para esta parte de la matriz.\n");
			}while((matriz[i][j]<1) || (matriz[i][j]>30));
		}
		
	printf("Ingrese los datos de la segunda mitad de las filas\nRECUERDE: sus valores deben estar entre 40 y 80\n");
	for(i=(nfilas-(nfilas/2)+1);i<=nfilas;i++) //pide los valores de la segunda mitad de las filas de la matriz
		for(j=1;j<=ncolumnas;j++){
			do{ //valida los valores ingresados
				printf("Ingrese el valor de la posicion %d,%d: ",i,j);
				scanf("%d",&matriz[i][j]);
				if((matriz[i][j]<40) || (matriz[i][j]>80)) 
					printf("ERROR: El valor ingresado esta fuera del rango permitido para esta parte de la matriz.\n");
			}while((matriz[i][j]<40) || (matriz[i][j]>80));
		}
	
	printf("La matriz ingresada es:\n");
	for(i=1;i<=nfilas;i++){ //imprime la matriz ingresada
		printf("| ");
		for(j=1;j<=ncolumnas;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("|\n");
	}
	
	for(j=1;j<=ncolumnas;j++){ //calcula la suma de las columnas
		suma[j]=0; //en este punto la suma se vuelve a inicializar en 0
		for(i=1;i<=nfilas;i++){
			suma[j]+=matriz[i][j];
		}
		promedio[j]=(float)suma[j]/nfilas; //calcula el promedio de las comlumnas
	}
	
	for(j=1;j<=ncolumnas;j++){
		printf("El promedio de la columna %d es %.2f.\n",j,promedio[j]);
	}
	
	promediomayor=promedio[1]; //inicializo la varible
	for(j=1;j<=ncolumnas;j++){ //determina el promedio mayor y cual columna es
		if(promedio[j]>promediomayor)
			promediomayor=promedio[j];
			k=j;
	}
	printf("La columna %d tiene mayor promedio.\n",k);
	return 0;
}
