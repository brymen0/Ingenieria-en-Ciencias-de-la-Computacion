#include<stdio.h>
#include<string.h>

/*Un número se dice que es palíndromo cuando se lo puede leer de izquierda a derecha igual que de derecha a
izquierda, por ejemplo, 4556554 es un número de este tipo.
Escriba un programa con funciones que lea un número de hasta 10 cifras y verifique que se trata de un número
palíndromo*/

int main(){
	char numero[10]; //Cadena numero ingresado
	
	ingresarNum(numero);
	validar(numero);
	return 0;
}

void ingresarNum (char numero[]){
	do{
		fflush(stdin); //limpie
		printf("Ingrese un numero de hasta 10 digitos\n");
		gets(numero);	
		if(strlen(numero)<0 || strlen(numero)>10) //valida el numero de digitos
			printf("ERROR: El numero debe tener entre 1 y 10 digitos\n");
	}while((strlen(numero)<0 || strlen(numero)>10));
} //fin funcion ingresarNum


void validar(char cadena[]){
	int i; //contador del bucle
	int numero[strlen(cadena)]; //vector del numero
	int numinverso[strlen(cadena)]; //vector del inverso del numero
	int correcto; //condicion
	
	(strrev(cadena));

	for(i=0;i<strlen(cadena);i++){ //bucle que almacena la cadena en un vector de entero
		numero[i]=(cadena[i]-'0');
	}
	
	for(i=0;i<strlen(cadena);i++){ //bucle que almacena la cadena inversa en un vector de entero
		numinverso[i]=(cadena[i]-'0');
	}
	
	for(i=0;i<strlen(cadena);i++){ //compara los dos valores
		if(numero[i]==numinverso[i]) //condicion
			correcto=0;
		else
			correcto=1;
	}
	if(correcto==0)
		printf("El numero es palidromo\n");
	else
		printf("El numero no es palidromo\n");
} //fin Funcion validar

  

