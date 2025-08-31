#include<stdio.h>

int main()
{
	int filas; //contador para el bulce de las filas
	int columnas; //contador para el bucle de las columnas
	int n; //numero ingresado
	
	printf("........................................................\n");
	printf("   Algortimo que dibuja un cuadrado con n asteriscos\n");
	printf("........................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	do //bucle que valida el numero
	{
		printf("Ingrese un numero entre 3 y 11: \n");
		scanf("%d",&n);
		if (n<3 || n>11)
			printf("ERROR: El numero ingresado esta fuera del rango permitido \n");
	}while (n<3 || n>11);
	
	for (filas=1;filas<=n;filas++) //bucle para ir fila por fila
	{
		for (columnas=1;columnas<=n;columnas++) //bucle para ir columna por columna
		{
			printf(" "); //para que haya un espacion entre cada asterisco y no sea vea todo junto
			if (filas==n || filas==1 || columnas==1 || columnas==n) //condicion para saber en donde escribir un asterisco
				printf("*");
			else
				printf(" ");
		}
		printf("\n");//salto de linea cuando acaba de escribir una fila y continua con la siguiente
	}
	return 0;
}
