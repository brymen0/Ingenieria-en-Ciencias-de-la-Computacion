#include<stdio.h>
#define MAXIMO 120

int main(){
	int cant; //cantidad de numeros a ingresar
	int i; //contador del bucle
	int vnum[MAXIMO]; //vector que almacena los numeros ingresados
	int mayor; //almacena el numero mayor
	int vecesmayor=0; //contador del numero mayor
	
	printf(".......................................................................................\n");
	printf("    Programa que lee N numeros y calcula cual es el mayor y cuantas veces se repite\n");
	printf(".......................................................................................\n");
	printf("\n");
	printf("AUTOR: BRYAN MENDOZA\n\n");

	do{ //valida la cantidad de numeros a ingresar
		printf("Ingrese la cantidad de numeros que va a registrar en el programa: ");
		scanf("%d",&cant);
		if(cant>MAXIMO || cant<=0)
			printf("ERROR: Solo se pueden ingresar maximo 120 numeros\n");
	}while(cant<=0 || cant>MAXIMO);
	
		for(i=1;i<=cant;i++){ //bucle que pide los numeros
		printf("Ingrese el numero: ");
		scanf("%d",&vnum[i]);
	}
	mayor=vnum[1];
	for(i=1;i<=cant;i++){
		if(vnum[i]>=mayor) //condicion para calcular el mayor
			mayor=vnum[i];	
	}
	
	for(i=1;i<=cant;i++){ //bucle que cuenta las veces que se repite el mayor numero
		if(vnum[i]==mayor)
			vecesmayor++;	
	}
	
	printf("El numero mayor es %d y se repite %d veces.\n",mayor,vecesmayor);
	
	return 0;
}
