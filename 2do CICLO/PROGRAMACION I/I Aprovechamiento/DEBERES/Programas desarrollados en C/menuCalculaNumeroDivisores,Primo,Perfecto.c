#include<stdio.h>

int main()
{
	int numero; //numero ingresado
	int opcion; //opcion ingresada
	int bandera; //validador de que ya se ingreso un numero
	int i; //contador para dividir al numero
	int numdivisores; //contador del numero de divisores
	int sumadivisores; //acumulador de divisores
	
	printf("......................................................................................................\n");
	printf("Programa que muestra un menu y puede calcular el numero de divisores, si es perfecto y si es primo\n");
	printf("......................................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	do
	{
		printf("MENU DE OPCIONES \n");
		printf("1.Ingresar un numero\n");
		printf("2.Calcular el numero de divisores, si es primo y si es perfecto\n");
		printf("3.Salir del algoritmo\n");
		printf("Ingrese una opcion\n");
		scanf("%d",&opcion);
		
		switch(opcion)
		{
			case 1: //ingresa un numero
				numero=0; //inicializo la variable numero
				do
				{
					printf("Ingrese un numero entre 1 y 100\n");
					scanf("%d",&numero);
					if (numero<1 || numero>100)
					printf("ERROR: El numero ingresado esta fuera del rango permitido\n");
				}while (numero<1 || numero>100);
				bandera=1; //ya se ingresaron los datos
			break;
			
			case 2: //calcula los divisores
				numdivisores=0; //inicializo el contador de divisores
				sumadivisores=0; //inicializo el acumulador de divisores
				if (bandera==1)
				{
					for (i=1;i<=numero;i++)
					{
						if (numero%i==0)
						{
							numdivisores=numdivisores+1;	
							sumadivisores=sumadivisores+i;
						}
					}
					printf("El numero %d tiene %d divisores\n",numero,numdivisores);
					printf("La suma de sus divisores es: %d\n",sumadivisores);
					
					if (numdivisores==2)
						printf("El numero %d es primo\n",numero);
					if (sumadivisores=numero+numero)
						printf("El numero %d es perfecto\n",numero);
				}
			break;
			
			case 3: //salir del algoritmo
				printf("Gracias por usar mi programa");
			break;
			
			default:
				printf("Opcion no valida");
		}
	}while (opcion<3);
	return 0;
}
