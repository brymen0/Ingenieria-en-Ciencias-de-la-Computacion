#include<stdio.h>
#include<string.h>

int main(){
	char nombre[20];
	int h;
	
	ingresoNombre(nombre);
	nombreMayuscula(nombre);
	printf("\n");
	nombreReves(nombre);
	h=numCaracteres(nombre);
	printf("\nEl nombre tiene %d caracteres\n",h);
	return 0;
}

void ingresoNombre (char n[20]){
	printf("Ingrese su nombre:\n");
	gets(n);
}

void nombreMayuscula(char n[20]){
	int nombremayus[20];
	int i;
	for(i=0;i<strlen(n);i++){
		nombremayus[i]=n[i]-32;
		printf("%c",nombremayus[i]);
	}
}

void nombreReves(char n[20]){
	int nombremayus[20];
	int i;
	for(i=strlen(n)-1;i>=0;i--){
		nombremayus[i]=n[i]-32;
		printf("%c",nombremayus[i]);
	}
}

int numCaracteres(char n[20]){
	int num;
	num=strlen(n);
	return num;
}
