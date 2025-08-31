#include<stdio.h>

int main(){
	
	int numero; //numero ingresado
	int contdig; //contador de digitos
	int numerorestante; //es el numero que queda luego de cada division por 10

	printf("...................................................................\n");
	printf("    Algortimo que cuenta los numeros de caracteres de un numero\n");
	printf("...................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	printf("Ingrese un numero:\n");
	scanf("%d",&numero);
	
	numerorestante=numero;//inicializo la variable
	contdig=0; //inicializo el contador de digitos
	
	while (numerorestante!=0) //bucle que cuenta los numeros de digitos
	{
		numerorestante=(numerorestante/10);
		contdig=contdig+1; //contador de los digitos
	}
	printf("El numero %d tiene %d digitos.",numero,contdig);
	return 0;
}
