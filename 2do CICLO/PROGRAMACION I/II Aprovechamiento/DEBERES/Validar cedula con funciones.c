#include <stdio.h>
#include <string.h>

void validarCedula(char cedula[10]);
void ingresoNombres();

int main (){
	int npersonas; //cantidad de persons que van a ingresar sus datos
	int i; //contador del bucle
	int opcion; //opcion que escoge el ususario
	int bandera=0; //bandera que indica si ya se ingreso cuantas personas van a ingresar sus datos
	
	printf("..............................................................\n");
	printf("  PROGRAMA QUE VALIDA EL NUMERO DE CEDULA Y PIDE SUS NOMBRES\n");
	printf("..............................................................\n");
	printf("Autor: Bryan Mendoza\n\n");
	
	do{
	printf("-------------------------------------------------------------------------\n");
	printf("                    M E N U    D E    O P C I O N E S\n");
	printf("-------------------------------------------------------------------------\n");
	printf("1. Cantidad de personas de las que se van a ingresar los datos\n");
	printf("2. Ingreso de los datos\n");
	printf("3. Salir del programa\n");	
	scanf("%d",&opcion);
	switch(opcion){
		case 1:
			printf("Ingrese la cantidad de personas que van a ingresar sus datos:\n");
			scanf("%d",&npersonas);
			bandera=1;
		break; 
			
		case 2:
			if(bandera==1){
				for(i=1;i<=npersonas;i++){
					char numcedu[10];
					validarCedula(numcedu);
					ingresoNombres();
					printf("su cedula es %s. \n",numcedu);
				}
			}
			else
				printf("ERROR:Primero debe ingresar la cantidad de personas de las cuales va a ingresar los datos\n\n");
		break;
		
		case 3:
			printf("Gracias por usar mi programa.\n");
		break;
		
		default:
			printf("Opcion no valida.\n");
	}
	}while(opcion!=3);
	
	return 0;
}

void validarCedula(char cedula[10]){
	int bandera=0;  //indica si la cedula fue ingresada correctamente
	int longitudCedula; //almacena la longitud de la cedula
	int i;  //contador para el bucle
	int digitoCedula;  //digito de la cedula que se va a examinar
	int sumaDigitosCedula;  //suma de los digitos 
	int contador;  //encuentra la proxima decena
	int ultimoD;  //almacena el ultimo digito de la cedula
	do{
		fflush(stdin);
		printf("Ingrese el numero de cedula: ");
		fgets(cedula,11,stdin);
		
		contador=0;
		bandera=0;
		
		longitudCedula=strlen(cedula);  //longitud de la cedula
		
		digitoCedula=0; //inicializo 
		sumaDigitosCedula=0; //inicializo
		
		if(longitudCedula==10){ 
		for(i=0; i<longitudCedula-1; i++){
			digitoCedula= cedula[i] - '0';  //se resta el cero para encontrar el real
			if(i%2==0){ 
				digitoCedula=digitoCedula*2;  //si i es par, se realiza la multiplicacion del digito de la cedula
				if(digitoCedula>=10){  
					digitoCedula=digitoCedula-9;  //Si el resultado es de dos cifras, se resta nueve
				}
			}
			sumaDigitosCedula=sumaDigitosCedula+digitoCedula;  //sa va realizando la suma de los digitos
		} //fin del for
		if(sumaDigitosCedula%10==0){  
			sumaDigitosCedula=0;
		}
		else{
			do{
				contador++;  //cuenta los numeros faltantes para completar la decena
			}while((sumaDigitosCedula+contador)%10!=0);
			sumaDigitosCedula=(sumaDigitosCedula+contador)-sumaDigitosCedula;  //resta la suma de la proxima decena
		}
		ultimoD=cedula[9]-'0';  //encuentra el ultimo digito de la cedula
		if(sumaDigitosCedula==ultimoD){ //si la suma de los digitos es igual al ultimo digito, la cedula es valida
			bandera=1;
		}	
	}
	if(bandera==1){
		printf("Cedula almacenada correctamente.\n");
	}	
	else
		printf("ERROR. Cedula Invalida\n");	
	}while(bandera<1);
}//fin funcion validar

void ingresoNombres(){
	char nombre[8]; //nombre de la persona
	char apellido1[8]; //primer apellido de la persona
	char apellido2[8]; //segundo apellido de la persona
	char espacio[]=" ";
	char concatenacion1[9]; //concatenacion1 de palabras
	char concatenacion2[17]; //concatenacion2 de palabras
	char concatenacion3[18]; //concatenacion3 de palabras
	printf("Ingrese su primer nombre: \n");
	scanf("%s",&nombre);
	printf("Ingrese su primer apellido: \n");
	scanf("%s",&apellido1);
	printf("Ingrese su segundo apellido: \n");
	scanf("%s",&apellido2);
	strcpy(concatenacion1,strcat(apellido1,espacio));
	strcpy(concatenacion2,strcat(concatenacion1,apellido2));
	strcpy(concatenacion3,strcat(concatenacion2,espacio));
	printf("%s ",strcat(concatenacion3,nombre));
}//fin funcion ingresoNombres
