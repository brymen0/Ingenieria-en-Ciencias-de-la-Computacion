#include<stdio.h>

int main()
{
	int numero; //numero ingresado
	int i;//contador del bucle para calcular los divisores
	int numdivi; //contador de divisores
	int sumadiv; //acumulador de divisores
	
	printf("..........................................................................................\n");
	printf("  Programa que calcula los divisores de un numero y determina si es primo y perfecto\n");
	printf("..........................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	do //bucle que valida el numero
	{
		printf("Ingrese un numero entre 0 y 900:\n"),
		scanf("%d",&numero);
		if (numero<=0 || numero>=900)
			printf("ERROR: El numero ingresado esta fuera del rango permitido\n");
	}while(numero<=0 || numero>=900);
	
	numdivi=0; //inicializo el contador
	sumadiv=0; //inicializo el acumulador
	
	for(i=1;i<=numero;i++) //bucle que calcula los divisores
	{
		if (numero%i==0)
		{
			sumadiv=sumadiv+i;
			numdivi=numdivi+1;
			printf("El numero %d es divisible para %d \n",numero,i);
		}
	}
	
	if (numdivi==2) //condicion para que sea primo
		printf("El numero %d es primo",numero);
		
	if (sumadiv-numero==numero) //condicion para que sea perfecto
		printf("El numero %d es perfecto",numero);
	return 0;
}
