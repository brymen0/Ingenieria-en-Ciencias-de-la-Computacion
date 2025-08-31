#include<stdio.h>

int main(){
	
	int cant; //cantidad de numeros a ingresar
	int vecnumeros[20]; //vector que almacena los  numeros ingresados
	int i; //contador del bucle
	int contpos=0; //contador de numeros positivos
	int contneg=0; //contador de numeros negativos
	int contceros=0; //contador de numeros ceros
	int vecpos[contpos]; //vector que almacena los numeros positivos
	int vecneg[contneg]; //vector que almacena los numeros negativos
	int h=1; //contador que guarda los positivos
	int g=1; //contador que guarda los negativos
	
	printf(".............................................................................................................\n");
	printf("          Programa que indica cuantos numeros positivos o negativos y ceros se han ingresado y cuales son\n");
	printf(".............................................................................................................\n");
	printf("AUTOR: BRYAN MENDOZA");
	printf("\n");
	
	do { //bucle para validar el numero de datos a ingresar
		printf ("\nIngrese la cantidad de numeros que se ingresaran entre 1 y 20: \n");
		scanf ("%d", &cant);
		if ((cant<1)||(cant>20)) {
			printf ("ERROR: La cantidad ingresada esta fuera del rango permitido. \n");
		}
	} while ((cant<1)||(cant>20));
	
	for(i=1;i<=cant;i++){ //bucle que pide los numeros 
		printf("Ingrese el numero: ");
		scanf("%d",&vecnumeros[i]);
		if(vecnumeros[i]>0){
			contpos++;
			vecpos[h]=vecnumeros[i];
			h++;
		}
		else{
			if(vecnumeros[i]<0){
				contneg++;
				vecneg[g]=vecnumeros[i];
				g++;
			}
			else
				contceros++;
		}
	}
	
	if(contpos!=0){
		printf("Se ingresaron %d numeros positivos y son:\n",contpos);
		for(i=1;i<=contpos;i++)
			printf("%d\n",vecpos[i]);
	}
	else
		printf("Se ingresaron %d numeros positivos\n",contpos);

	if(contneg!=0){
		printf("Se ingresaron %d numeros negativos y son:\n",contneg);
			for(i=1;i<=contneg;i++)
			printf("%d\n",vecneg[i]);
	}
	else
		printf("Se ingresaron %d numeros negativos\n",contneg);
		
	printf("Se ingresaron %d ceros\n",contceros);
	return 0;
}
