#include<stdio.h>
#include<string.h>

void ingresaFraseyValida(char palabra[]); //funcion que pide y valida la frase
void copiaFrase(char palabra[],char palabracopia[]); //funcion que copia la frase original en otro vector
int cuentaEspacios(char palabra[]); //funcion que cuenta las veces que hay dos espacios consecutivos
void recortaEspacios(char palabra[],int espacio); //funcion que elimina los espacios sobrantes de la frase
void pasaAMayuscula(char palabra[]); //funcion que pasa la frase mayusculas
void muestraFrases(char palabra[],char palabracopia[]); //funcion que muestra la frase original y la modificada
void cuentaVocalesConsonantesNumeros(char palabra[]); //funcion que cuenta las vocales, las consonantes y los numeros que hay en la frase

int main(){
	char palabra[1000];
	char palabracopia[1000];
	int n;
	int espacio;
	
	printf("........................................................................................................................\n");
	printf(" PROGRAMA QUE BORRA EXCESO DE ESPACIOS, TRANSFORMA A MAYUSCULAS Y CUENTA VOCALES, CONSONANTES Y NUMEROS DE UNA FRASE\n");
	printf("........................................................................................................................\n");
	printf("Autor: Bryan Mendoza\n\n");

	ingresaFraseyValida(palabra);
	copiaFrase(palabra,palabracopia);
	espacio=cuentaEspacios(palabra);
	recortaEspacios(palabra,espacio);
	pasaAMayuscula(palabra);
	muestraFrases(palabra,palabracopia);
	cuentaVocalesConsonantesNumeros(palabra);
	
	return 0;
}

void ingresaFraseyValida(char palabra[]){ //funcion que pide y valida la frase
	do{
		printf("Ingrese la frase a modificar: ");
		gets(palabra);	
		if(strlen(palabra)>1000)
			printf("La frase ingresada solo puede tener 1000 caracteres.\n");
	}while(strlen(palabra)>1000);
} //fin funcion ingresaFraseyValida

void copiaFrase(char palabra[],char palabracopia[]){ //funcion que copia la frase original en otro vector
	strcpy(palabracopia,palabra); 
}//fin funcion copiaFrase

int cuentaEspacios(char palabra[]){ //funcion que cuenta las veces que hay dos espacios consecutivos
	int i; //contador del bucle
	int espacios=0; //contador de espacios consecutivos
	
	for(i=0;i<strlen(palabra);i++){
		if(palabra[i]==' ' && palabra[i-1]==' ')
			espacios++;
	}
	return espacios;	
} //fin funcion cuentaEspacios

void recortaEspacios(char palabra[],int espacio){ //funcion que elimina los espacios sobrantes de la frase
	int i,j,k;
	
	for(i=0;i<espacio;i++){
		for(j=0;j<strlen(palabra);j++){
			if(palabra[j]==' ' && palabra[j-1]==' '){
				for(k=j;k<strlen(palabra);k++){
					palabra[k-1]=palabra[k];
					palabra[k]=palabra[k+1];
				}
			}
		}
	}
}//fin funcion recortaEspacios

void pasaAMayuscula(char palabra[]){ //funcion que pasa la frase mayusculas
	int i; //contador del bucle
	int n; //codigo ascii de cada letra de la palabra
	for(i=0;i<strlen(palabra);i++){
		n=palabra[i];
		if(n>96 && n<123)
			palabra[i]=n-32;	
	}
}//fin funcion pasaAMayuscula

void muestraFrases(char palabra[],char palabracopia[]){ //funcion que muestra la frase original y la modificada
	printf("\nLa frase original es:\n");
	printf("%s\n\n",palabracopia);
	printf("La frase modificada es:\n");
	printf("%s\n\n",palabra);
} //fin de la funcion muestraFrases

void cuentaVocalesConsonantesNumeros(char palabra[]){ //funcion que cuenta las vocales, las consonantes y los numeros que hay en la frase
	int i;//contador del bucle
	int n; //codigo ascii de cada letra de la palabra
	int contvocales=0; //contador de vocales
	int contnumeros=0; //contador de numeros
	int contconsonantes=0; //contador del consonantes
	for(i=0;i<strlen(palabra);i++){
		n=palabra[i]; //pasa la letra a codigo ascii
		if(n==65||n==69||n==73||n==79||n==85)
			contvocales++;
		else{
			if(n>47 && n<58)
				contnumeros++;
			else
				if(n>35 && n<91)
				contconsonantes++;
		}
	}
	printf("La frase tiene %d vocales, %d consonantes y %d numeros.",contvocales,contconsonantes,contnumeros);
} //fin funcion cuentaVocalesConsonantesNumeros
