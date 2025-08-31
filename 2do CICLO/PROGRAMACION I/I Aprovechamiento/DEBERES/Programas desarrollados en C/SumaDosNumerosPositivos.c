#include<stdio.h>

int main(){
	
	int num1; //primer numero a sumar
	int num2; //segundo numero a sumar
	int suma; //resultado de la suma
	
	printf("........................................................\n");
	printf(" Algortimo que calcula la suma de dos numero positivos\n");
	printf("........................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	do { //bucle que valida el primer numero
		printf("Ingrese el primer numero\n");
		scanf("%d",&num1);
		
		if (num1<0)
			printf("ERROR: El numero ingresado debe ser positivo\n");
	}while (num1<0);
	
	do{ //bucle que valida el segundo numero
		printf("Ingrese el segundo numero\n");
		scanf("%d",&num2);	
		
		if (num2<0)
			printf("ERROR: El numero ingresado debe ser positivo\n");	
	}while (num2<0);
	
	suma=0; //inicializo suma
	suma=num1+num2; //suma los dos numeros
	
	printf("La suma de los numeros %d y %d es: %d",num1,num2,suma);
	return 0;
}
