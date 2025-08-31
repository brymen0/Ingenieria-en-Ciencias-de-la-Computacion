#include<stdio.h>

int main(){
	
	int numero; //numero ingresado
	int i; //contador de los numeros a multiplicar para calcular el factorial
	unsigned long int factorial; //es el acumulador de las multiplicacion que calculan el factorial
	
	printf("........................................................\n");
	printf("    Programa que calcula el factorial de un numero\n");
	printf("........................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	do //bucle que valida el numero ingresado
	{
		printf("Ingrese un numero entre 1 y 12\n");
		scanf("%d",&numero);
		if (numero<1 || numero>12)
			printf("ERROR: El numero ingresado esta fuera del rango permitido\n");
	}while (numero<1 || numero>12);
	
	factorial=1; //inicializo el acumulador de factorial
	for (i=1;i<=numero;i++) //bucle para multiplicar los numeros y calcular el factorial
		factorial=factorial*i;//calcula el factorial
	printf("El factorial del numero %d es %ld.",numero,factorial);
	return 0;
}
