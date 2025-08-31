#include<stdio.h>
#include<string.h>

int menu(); //funcion que muestra el menu de opciones
void ingresoNumeroEntero(char numero[]); //funcion que pide el numero entero 
int validaNumeroEntero(char numero[]); //funcion que valida el numero en cifras
void transformaNumeroALetras(char numero[]); //funcion que transforma el numero en cifras a letras
void ingresoNumeroEscrito(char numeroLetras[]); //funcion que pide el numero escrito
int validaNumeroEscrito(char numeroLetras[]); //funcion que valida el numero escrito en letras
void transformaLetrasANumeros(char numeroLetras[]); //funcion que transforma de numero escrito en letras a cifras 

int main(){
	int opcion; //opcion ingresada por el usuario
	char numeroEntero[11]; //numero maximo en cifras 
	char numeroLetras[100]; //numero en letras
	int valido; //indica si el numero entero ingresado es valido o no
	int validoL; //indica si el numero en letras ingresado es valido o no
	
	printf(".....................................................................\n");
	printf("  PROGRAMA CON MENU QUE CONVIERTE DE NUMERO A LETRAS Y VICEVERSA\n");
	printf(".....................................................................\n");
	printf("Autor: Bryan Mendoza\n\n");
	do{
		opcion=menu();
		switch(opcion){
			case 1:{ //Ingresar una cifra en numeros y convertirla a letras
				printf("El numero a ingresar debe tener maximo hasta la centena de mil y hasta 3 decimales\nSeparado por punto para los miles y por la coma para los decimales\n");
				printf("Ejemplos: 256.895,365  -  28.569  -  258  -  32,89\n");
				do{
					ingresoNumeroEntero(numeroEntero);
					valido=validaNumeroEntero(numeroEntero);
					if(valido==1)
						printf("ERROR: El numero ingresado es incorrecto\n");
				}while(valido==1);
				printf("El numero en letras es: ");
				transformaNumeroALetras(numeroEntero);
				
				break;
			}
			
			case 2:{ //Ingresar una cifra en letras  y convertirla a numeros
				printf("El numero en letras a ingresar debe estar en minusculas\nSi el numero supera la cantidad de 1000 debe contener la palabra \"mil\" y si tiene decimales debe contener la palabra \"con\"\n");
				printf("Ejemplos:\ndoscientos cincuenta y cinco mil trescientos noventa y nueve\n");
				printf("veinte y cuatro mil trescientos sesenta y ocho con veinte y tres centesimas\nochenta y cinco\n");
				printf("quince mil ciento catorce con novecientos noventa y nueve milesimas\n");
				do{
					ingresoNumeroEscrito(numeroLetras);
					validoL=validaNumeroEscrito(numeroLetras);
					if(validoL==1)
						printf("ERROR: El numero ingresado es incorrecto\n");
				}while(validoL==1);
				printf("El numero en cifras es: ");
				transformaLetrasANumeros(numeroLetras);
				break;
			}
			
			case 3:{
				printf("Gracias por usar mi programa");
				break;
			}
			
			default:
				printf("Opcion no valida\n\n");
		} //fin del switch	
	}while(opcion!=3);
	
	return 0;
} //fin funcion principal

int menu(){ //funcion que muestra el menu de opciones
	int op;
	printf("....................................................................\n");
	printf("                   M E N %c   D E   O P C I O N E S\n",233);
	printf("....................................................................\n\n");
	printf("1. Ingresar una cifra en numeros y convertirla a letras\n");
	printf("2. Ingresar una cifra en letras  y convertirla a numeros\n");
	printf("3. Salir\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&op);
	return op;
}//fin funcion menu

void ingresoNumeroEntero(char numero[]){ //funcion que pide el numero entero 
	printf("Ingrese el numero:");
	fflush(stdin);
	gets(numero);
} //fin funcion numeroEntero

int validaNumeroEntero(char numero[]){ //funcion que valida el numero en cifras
	int correcto;
	int i;
	char n[100];
	int coma=0,punto=0;
	strcpy(n,numero);
	correcto=0;
	for(i=0;i<strlen(n);i++){
		if(n[i]=='.')
			punto++;
		if(n[i]==',')
			coma++;
	}
	if(punto>1||coma>1){
		correcto=1;
		printf("Por demasiados puntos o comas\n");
	}
	if(punto==0 && coma==0 && strlen(n)>3){
		correcto=1;
		printf("No hay coma o punto\n");
	}
	if(strlen(n)>11){
		correcto=1;
		printf("Por mucho digitos");
	}
	for(i=0;i<strlen(n);i++){
		if(n[i]=='.'){
			if((n[i-1]=='\0'||n[i+1]=='\0'||n[i+2]=='\0'||n[i+3]=='\0'||n[i+3]==',')){
				correcto=1;
				printf("Por punto\n");
			}
			if(punto==1&coma==1){
				if(n[i+4]!=','){
					correcto=1;
					printf("Por punto y coma\n");
				}
			}
		}
		if(n[i]==','){
			if((n[i-1]=='\0')||n[i+1]=='\0'){
				correcto=1;
				printf("Por coma\n");
			}
		}
	}//fin for	
	return correcto;
}//fin funcion validanNumeroEntero

void transformaNumeroALetras(char numero[]){ //funcion que transforma el numero en cifras a letras
	char *token; //puntero que separa los miles, cientos y decimales del numero
	char miles[3]; //vector que almacena los miles
	char cientos[3]; //vector que almacena los cientos
	char decimales[3]; //vector que almacena los decimales
	int veces; //indica cuantas veces se repetira el bucle que escribe en letras los numeros
	int i,j; //contadores del bucle
	int punto=0,coma=0; //variable que avisa si el numero ingresado tiene punto y coma
	int m,ci,pd; //variables que contienen el numero como entero y no como ascii
	int cm,dm,um; //variables correspondiente de la centena de mil, decena de mil y unidad de mil
	int c,d,u; //variables correspondiente de la centena, decena y unidad
	int ud,cd,dd; //variables correspondiente de la centesimas, decimas y milesimas
	int centenas,decenas,unidades; //almacena las variables segun el numero de repeticion en la que este el bucle
	int x; //auxiliar usada cuando la decena es 1
	
	for(i=0;i<strlen(numero);i++){ //bucle que informa contiene puntos o comas
		if(numero[i]=='.')
			punto=1;
		if(numero[i]==',')
			coma=1;
	}
	
	if(punto==1 && coma==1){ //separa el numero en miles,cientos y decimales
		token=strtok(numero, ".");
  	  	strcpy(miles,token);
		token=strtok(NULL,",");
    	strcpy(cientos,token);
		token=strtok(NULL," ");
		strcpy(decimales,token);
		veces=3;
	}
	
	if(punto==1 && coma==0){ //separa el numero en miles y cientos
		token=strtok(numero, ".");
		strcpy(miles,token);
		token=strtok(NULL," ");
    	strcpy(cientos,token);
    	strcpy(decimales,"");
		veces=2;	
	}
	
	if(punto==0 && coma==1){ //separa el numero en cientos y decimales
		token=strtok(numero, ",");
  	  	strcpy(cientos,token);
		token=strtok(NULL," ");
    	strcpy(decimales,token);
    	strcpy(miles,"");
		veces=2;
	}
	
	if(punto==0 && coma==0){ //separa el numero en cientos
		strcpy(cientos,numero);
		strcpy(decimales,"");
		strcpy(miles,"");
		veces=1;
	}
	
	if(strlen(miles)!=0){ //separa a los miles en centena,decena y unidad
		m=atoi(miles); //convirte los miles de ascii a entero
		um=(m-m/10*10); //almacena la unidad de mil 
		dm=(m-m/100*100)/10; //almacena la decena de mil
		cm=(m-m/1000*1000-um-dm)/100; //almacena la centena de mil
	}
	if(strlen(cientos)!=0){ //separa a los cientos en centena,decena y unidad
		ci=atoi(cientos); //convirte los cientos de ascii a entero
		u=(ci-ci/10*10); //almacena la unidad
		d=(ci-ci/100*100)/10; //almacena la decena
		c=(ci-ci/1000*1000-u-d)/100; //almacena la centena
	}
	if(strlen(decimales)!=0){//separa a los decimales en centena,decena y unidad
		pd=atoi(decimales); //convirte los decimales de ascii a entero
		ud=(pd-pd/10*10); //almacena las milesimas
		dd=(pd-pd/100*100)/10; //almacena las centesimas
		cd=(pd-pd/1000*1000-ud-dd)/100; //almacena las milesimas
	}
	
	for(j=0;j<veces;j++){ //bucle que escribe el numero en letras
		if(j==0 && punto==1){
			centenas=cm;
			decenas=dm;
			unidades=um;
		}
		if((j==1 && punto==1)||(j==0 && coma==1 && punto==0)||(j==0 && punto==0 && coma==0)){
			centenas=c;
			decenas=d;
			unidades=u;
		}
		if((j==2 && coma==1)||(j==1 && punto==0 && coma==1)){
			centenas=cd;
			decenas=dd;
			unidades=ud;
		}
		
		if(strlen(decimales)!=0 && j==(veces-1)) //condicion para que imprima la palabra "con" para iniciar decimales
			printf("con ");
			
		switch(centenas){
			case 1:{
				if(decenas==0 && unidades==0)
					printf("cien");
				else
					printf("ciento ");
				break;
			}
			case 2:
				printf("doscientos ");
				break;
			case 3:
				printf("trescientos ");
				break;
			case 4:
				printf("cuatrocientos ");
				break;
			case 5:
				printf("quinientos ");
				break;
			case 6:
				printf("seiscientos ");
				break;
			case 7:
				printf("setecientos ");
				break;
			case 8:
				printf("ochocientos ");
				break;
			case 9:
				printf("novecientos ");
				break;
		}//fin switch centenas mil
			
		switch(decenas){
			case 1:{
				x=decenas+unidades;
				switch(x){
					case 1:
						printf("diez ");
						break;
					case 2:
						printf("once ");
						break;
					case 3:
						printf("doce ");
						break;
					case 4:
						printf("trece ");
						break;
					case 5:
						printf("catorce ");
						break;
					case 6:
						printf("quince ");
						break;
					case 7:
						printf("diecises ");
						break;
					case 8:
						printf("diecisiete ");
						break;
					case 9:
						printf("dieciocho ");
						break;
					case 10:
						printf("diecinueve ");
						break;
				}//fin switch x
				break;
			}
			case 2:
				printf("veinte ");
				break;
			case 3:
				printf("treinta ");
				break;
			case 4:
				printf("cuarenta ");
				break;
			case 5:
				printf("cincuenta ");
				break;
			case 6:
				printf("sesenta ");
				break;
			case 7:
				printf("setenta ");
				break;
			case 8:
				printf("ochenta ");
				break;
			case 9:
				printf("noventa ");
				break;
		}//fin switch decenas
			
		if(decenas!=0 && decenas!=1 && unidades!=0)
			printf("y ");
			
		if(decenas!=1){
			switch(unidades){
			case 1:{
				if(decenas==0)
					printf("un ");
				else
					printf("uno ");
				break;
			}
			case 2:
				printf("dos ");
				break;
			case 3:
				printf("tres ");
				break;
			case 4:
				printf("cuatro ");
				break;
			case 5:
				printf("cinco ");
				break;
			case 6:
				printf("seis ");
				break;
			case 7:
				printf("siete ");
				break;
			case 8:
				printf("ocho ");
				break;
			case 9:
				printf("nueve ");
				break;
		}//fin switch unidades	
		}//fin if (decenas!=1)	
	
		if(strlen(miles)!=0 && j==0)	
			printf("mil ");
			
		if(strlen(decimales)==3 && j==veces-1)	
			printf("milesimas.");
			
		if(strlen(decimales)==2 && j==veces-1)	
			printf("centesimas.");
			
		if(strlen(decimales)==1 && j==veces-1)	
			printf("decimas.");
	}// fin for con j
	printf("\n\n");
} //fin funcion transformaNumeroALetras

void ingresoNumeroEscrito(char numeroLetras[]){ //funcion que pide el numero escrito
	printf("Ingrese el numero escrito en letras:");
	fflush(stdin);
	gets(numeroLetras);
} //fin funcion ingresoNumeroEscrito

int validaNumeroEscrito(char numeroLetras[]){ //funcion que valida el numero escrito en letras
	int i; //contador del bucle
	int espacios=0; //contador de espacios
	int correcto1=0; //valor que retorna
	for(i=0;i<strlen(numeroLetras);i++){
		if(numeroLetras[i]==' ')
			espacios++;
	}
	if(espacios>14)
		correcto1=1;
	return correcto1;
}// fin funcion validaNumeroEscrito

void transformaLetrasANumeros(char numeroLetras[]){
	int i; //contador del bucle
	char n[100]; //cadena donde se copiara el numero
	
	strcpy(n,numeroLetras);//copia el numero en letras en otr vector con un nombre mas corto
    
	for(i=0;i<strlen(n);i++){
		if(n[i]=='c'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='n'&&(n[i+4]==' '||n[i+4]=='\0'))
			printf("100");
		if(n[i]=='c'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='n'&&n[i+4]=='t'&&n[i+5]=='o'&&n[i+6]==' '){
			if(n[i+7]=='u' && n[i+8]=='n' && n[i+9]==' ')
				printf("101");
			if(n[i+7]=='d' && n[i+8]=='o' && n[i+9]=='s' && (n[i+10]==' '||n[i+10]=='\0'))
				printf("102");
			if(n[i+7]=='t' && n[i+8]=='r' && n[i+9]=='e' && n[i+10]=='s' && (n[i+11]==' '||n[i+11]=='\0'))
				printf("103");
			if(n[i+7]=='c' && n[i+8]=='u' && n[i+9]=='a' && n[i+10]=='t' && n[i+11]=='r'&& n[i+12]=='o' && (n[i+13]==' '||n[i+13]))
				printf("104");
			if(n[i+7]=='c' && n[i+8]=='i' && n[i+9]=='n' && n[i+10]=='c' && n[i+11]=='o' && n[i+12]==' ')
				printf("105");
			if(n[i+7]=='s' && n[i+8]=='e' && n[i+9]=='i' && n[i+10]=='s' && n[i+11]==' ')
				printf("106");
			if(n[i+7]=='s' && n[i+8]=='i' && n[i+9]=='e' && n[i+10]=='t' && n[i+11]=='e' && n[i+12]==' ')
				printf("107");
			if(n[i+7]=='o' && n[i+8]=='c' && n[i+9]=='h' && n[i+10]=='o' && n[i+11]==' ')
				printf("108");
			if(n[i+7]=='n' && n[i+8]=='u' && n[i+9]=='e' && n[i+10]=='v' && n[i+11]=='e' && n[i+12]==' ')
				printf("109");
			if(((n[i+7]=='d'||n[i+7]=='o'||n[i+7]=='c'||n[i+7]=='q'||n[i+7]=='v'))||(n[i+7]=='t'&&n[i+8]=='r'&&n[i+9]=='e'&&n[i+10]!='s')||(n[i+7]=='c'&&n[i+8]=='u'&&n[i+9]=='a'&&n[i+10]!='t')||(n[i+7]=='c'&&n[i+8]=='i'&&n[i+9]=='n'&&n[i+10]=='c'&&n[i+11]!='c')||(n[i+7]=='s'&&n[i+8]=='e'&&n[i+9]!='i')||(n[i+7]=='o'&&n[i+8]=='c'&&n[i+9]=='h'&&n[i+10]!=0)||(n[i+7]=='n'&&n[i+8]!='u'))
				printf("1");
		}
	
		if(n[i]=='d'&&n[i+1]=='o'&&n[i+2]=='s'&&n[i+3]=='c'&&n[i+4]=='i'&&n[i+5]=='e'&&n[i+6]=='n'&&n[i+7]=='t'&&n[i+8]=='o'&&n[i+9]=='s'){
			if((n[i+10]==' ' && n[i+11]=='m')||(n[i+10]=='\0')||(n[i+10]==' ' && n[i+11]=='c' && n[i+12]=='o'))
				printf("200");
			if(n[i+10]==' ' && n[i+11]=='u' && n[i+12]=='n' && n[i+13]=='o' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("201");
			if(n[i+10]==' ' && n[i+11]=='d' && n[i+12]=='o' && n[i+13]=='s' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("202");
			if(n[i+10]==' ' && n[i+11]=='t' && n[i+12]=='r' && n[i+13]=='e' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("203");
			if(n[i+10]==' ' && n[i+11]=='c' && n[i+12]=='u' && n[i+13]=='a' && n[i+14]=='t' && n[i+15]=='r'&& n[i+16]=='o' && (n[i+17]==' '||n[i+18]=='\0'))
				printf("204");
			if(n[i+10]==' ' && n[i+11]=='c' && n[i+12]=='i' && n[i+13]=='n' && n[i+14]=='c' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("205");
			if(n[i+10]==' ' && n[i+11]=='s' && n[i+12]=='e' && n[i+13]=='i' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("206");
			if(n[i+10]==' ' && n[i+11]=='s' && n[i+12]=='i' && n[i+13]=='e' && n[i+14]=='t' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("207");
			if(n[i+10]==' ' && n[i+11]=='o' && n[i+12]=='c' && n[i+13]=='h' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("208");
			if(n[i+10]==' ' && n[i+11]=='n' && n[i+12]=='u' && n[i+13]=='e' && n[i+14]=='v' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("209");
			if((n[i+10]==' '&&(n[i+11]=='d'||n[i+11]=='o'||n[i+11]=='c'||n[i+11]=='q'||n[i+11]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("2");
		}	
		if(n[i]=='t'&&n[i+1]=='r'&&n[i+2]=='e'&&n[i+3]=='s'&&n[i+4]=='c'&&n[i+5]=='i'&&n[i+6]=='e'&&n[i+7]=='n'&&n[i+8]=='t'&&n[i+9]=='o'&&n[i+10]=='s'){
			if((n[i+11]==' ' && n[i+12]=='m')||(n[i+11]=='\0')||(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='o'))
				printf("300");
			if(n[i+11]==' ' && n[i+12]=='u' && n[i+12]=='n' && n[i+13]=='o' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("301");
			if(n[i+11]==' ' && n[i+12]=='d' && n[i+12]=='o' && n[i+13]=='s' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("302");
			if(n[i+11]==' ' && n[i+12]=='t' && n[i+12]=='r' && n[i+13]=='e' && n[i+14]=='s' && (n[i+15]==' '||n[1+15]=='\0'))
				printf("303");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+12]=='u' && n[i+13]=='a' && n[i+14]=='t' && n[i+15]=='r'&& n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("304");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+12]=='i' && n[i+13]=='n' && n[i+14]=='c' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("305");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+12]=='e' && n[i+13]=='i' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("306");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+12]=='i' && n[i+13]=='e' && n[i+14]=='t' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("307");
			if(n[i+11]==' ' && n[i+12]=='o' && n[i+12]=='c' && n[i+13]=='h' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("308");
			if(n[i+11]==' ' && n[i+12]=='n' && n[i+12]=='u' && n[i+13]=='e' && n[i+14]=='v' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("309");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("3");	
		}	
		if(n[i]=='c'&&n[i+1]=='u'&&n[i+2]=='a'&&n[i+3]=='t'&&n[i+4]=='r'&&n[i+5]=='o'&&n[i+6]=='c'&&n[i+7]=='i'&&n[i+8]=='e'&&n[i+9]=='n'&&n[i+10]=='t'&&n[i+11]=='o'&&n[i+12]=='s'){
			if((n[i+13]==' ' && n[i+14]=='m')||(n[i+13]=='\0')||(n[i+13]==' ' && n[i+14]=='c' && n[i+15]=='o'))
				printf("400");
			if(n[i+13]==' ' && n[i+14]=='u' && n[i+15]=='n' && n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("401");
			if(n[i+13]==' ' && n[i+14]=='d' && n[i+15]=='o' && n[i+16]=='s' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("402");
			if(n[i+13]==' ' && n[i+14]=='t' && n[i+15]=='r' && n[i+16]=='e' && n[i+17]=='s' && (n[i+18]==' '||n[1+18]=='\0'))
				printf("403");
			if(n[i+13]==' ' && n[i+14]=='c' && n[i+15]=='u' && n[i+16]=='a' && n[i+17]=='t' && n[i+18]=='r'&& n[i+19]=='o' && (n[i+20]==' '||n[i+20]=='\0'))
				printf("404");
			if(n[i+13]==' ' && n[i+14]=='c' && n[i+15]=='i' && n[i+16]=='n' && n[i+17]=='c' && n[i+18]=='o' && (n[i+19]==' '||n[i+19]=='\0'))
				printf("405");
			if(n[i+13]==' ' && n[i+14]=='s' && n[i+15]=='e' && n[i+16]=='i' && n[i+17]=='s' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("406");
			if(n[i+13]==' ' && n[i+14]=='s' && n[i+15]=='i' && n[i+16]=='e' && n[i+17]=='t' && n[i+18]=='e' && (n[i+19]==' '||n[i+19]=='\0'))
				printf("407");
			if(n[i+13]==' ' && n[i+14]=='o' && n[i+15]=='c' && n[i+6]=='h' && n[i+17]=='o' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("408");
			if(n[i+13]==' ' && n[i+14]=='n' && n[i+15]=='u' && n[i+16]=='e' && n[i+17]=='v' && n[i+18]=='e' && (n[i+19]==' '||n[i+19]=='\0'))
				printf("409");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("4");
		}
		if(n[i]=='q'&&n[i+1]=='u'&&n[i+2]=='i'&&n[i+3]=='n'&&n[i+4]=='i'&&n[i+5]=='e'&&n[i+6]=='n'&&n[i+7]=='t'&&n[i+8]=='o'&&n[i+9]=='s'){
			if((n[i+10]==' ' && (n[i+11]=='m'||(n[i+11]=='c'&&n[i+12]=='o')))||(n[i+10]=='\0'))
				printf("500");
			if(n[i+10]==' ' && n[i+11]=='u' && n[i+12]=='n' && n[i+13]=='o' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("501");
			if(n[i+10]==' ' && n[i+11]=='d' && n[i+12]=='o' && n[i+13]=='s' && (n[i+14]==' '||n[i+14]=='\0'))
				printf("502");
			if(n[i+10]==' ' && n[i+11]=='t' && n[i+12]=='r' && n[i+13]=='e' && n[i+14]=='s' && (n[i+15]==' '||n[1+15]=='\0'))
				printf("503");
			if(n[i+10]==' ' && n[i+11]=='c' && n[i+12]=='u' && n[i+13]=='a' && n[i+14]=='t' && n[i+15]=='r'&& n[i+16]=='o' && (n[i+17]==' '||n[i+18]=='\0'))
				printf("504");
			if(n[i+10]==' ' && n[i+11]=='c' && n[i+12]=='i' && n[i+13]=='n' && n[i+14]=='c' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("505");
			if(n[i+10]==' ' && n[i+11]=='s' && n[i+12]=='e' && n[i+13]=='i' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("506");
			if(n[i+10]==' ' && n[i+11]=='s' && n[i+12]=='i' && n[i+13]=='e' && n[i+14]=='t' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("507");
			if(n[i+10]==' ' && n[i+11]=='o' && n[i+12]=='c' && n[i+13]=='h' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("508");
			if(n[i+10]==' ' && n[i+11]=='n' && n[i+12]=='u' && n[i+13]=='e' && n[i+14]=='v' && n[i+15]=='e' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("509");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("5");
		}
		if(n[i]=='s'&&n[i+1]=='e'&&n[i+2]=='i'&&n[i+3]=='s'&&n[i+4]=='c'&&n[i+5]=='i'&&n[i+6]=='e'&&n[i+7]=='n'&&n[i+8]=='t'&&n[i+9]=='o'&&n[i+10]=='s'){
			if((n[i+11]==' ' && n[i+12]=='m')||(n[i+11]=='\0')||(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='o'))
				printf("600");
			if(n[i+11]==' ' && n[i+12]=='u' && n[i+13]=='n' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("601");
			if(n[i+11]==' ' && n[i+12]=='d' && n[i+13]=='o' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("602");
			if(n[i+11]==' ' && n[i+12]=='t' && n[i+13]=='r' && n[i+14]=='e' && n[i+15]=='s' && (n[i+16]==' '||n[1+16]=='\0'))
				printf("603");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='u' && n[i+14]=='a' && n[i+15]=='t' && n[i+16]=='r'&& n[i+17]=='o' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("604");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='i' && n[i+14]=='n' && n[i+15]=='c' && n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("605");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='e' && n[i+14]=='i' && n[i+15]=='s' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("606");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='i' && n[i+14]=='e' && n[i+15]=='t' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("607");
			if(n[i+11]==' ' && n[i+12]=='o' && n[i+13]=='c' && n[i+14]=='h' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("608");
			if(n[i+11]==' ' && n[i+12]=='n' && n[i+13]=='u' && n[i+14]=='e' && n[i+15]=='v' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("609");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("6");
		}
		if(n[i]=='s'&&n[i+1]=='e'&&n[i+2]=='t'&&n[i+3]=='e'&&n[i+4]=='c'&&n[i+5]=='i'&&n[i+6]=='e'&&n[i+7]=='n'&&n[i+8]=='t'&&n[i+9]=='o'&&n[i+10]=='s'){
			if((n[i+11]==' ' && n[i+12]=='m')||(n[i+11]=='\0')||(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='o'))
				printf("700");
			if(n[i+11]==' ' && n[i+12]=='u' && n[i+13]=='n' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("701");
			if(n[i+11]==' ' && n[i+12]=='d' && n[i+13]=='o' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("702");
			if(n[i+11]==' ' && n[i+12]=='t' && n[i+13]=='r' && n[i+14]=='e' && n[i+15]=='s' && (n[i+16]==' '||n[1+16]=='\0'))
				printf("703");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='u' && n[i+14]=='a' && n[i+15]=='t' && n[i+16]=='r'&& n[i+17]=='o' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("704");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='i' && n[i+14]=='n' && n[i+15]=='c' && n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("705");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='e' && n[i+14]=='i' && n[i+15]=='s' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("706");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='i' && n[i+14]=='e' && n[i+15]=='t' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("707");
			if(n[i+11]==' ' && n[i+12]=='o' && n[i+13]=='c' && n[i+14]=='h' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("708");
			if(n[i+11]==' ' && n[i+12]=='n' && n[i+13]=='u' && n[i+14]=='e' && n[i+15]=='v' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("709");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("7");
		}
		if(n[i]=='o'&&n[i+1]=='c'&&n[i+2]=='h'&&n[i+3]=='o'&&n[i+4]=='c'&&n[i+5]=='i'&&n[i+6]=='e'&&n[i+7]=='n'&&n[i+8]=='t'&&n[i+9]=='o'&&n[i+10]=='s'){
			if((n[i+11]==' ' && n[i+12]=='m')||(n[i+11]=='\0')||(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='o'))
				printf("800");
			if(n[i+11]==' ' && n[i+12]=='u' && n[i+13]=='n' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("801");
			if(n[i+11]==' ' && n[i+12]=='d' && n[i+13]=='o' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("802");
			if(n[i+11]==' ' && n[i+12]=='t' && n[i+13]=='r' && n[i+14]=='e' && n[i+15]=='s' && (n[i+16]==' '||n[1+16]=='\0'))
				printf("803");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='u' && n[i+14]=='a' && n[i+15]=='t' && n[i+16]=='r'&& n[i+17]=='o' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("804");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='i' && n[i+14]=='n' && n[i+15]=='c' && n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("805");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='e' && n[i+14]=='i' && n[i+15]=='s' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("806");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='i' && n[i+14]=='e' && n[i+15]=='t' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("807");
			if(n[i+11]==' ' && n[i+12]=='o' && n[i+13]=='c' && n[i+14]=='h' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("808");
			if(n[i+11]==' ' && n[i+12]=='n' && n[i+13]=='u' && n[i+14]=='e' && n[i+15]=='v' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("809");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("8");	
		}
		if(n[i]=='n'&&n[i+1]=='o'&&n[i+2]=='v'&&n[i+3]=='e'&&n[i+4]=='c'&&n[i+5]=='i'&&n[i+6]=='e'&&n[i+7]=='n'&&n[i+8]=='t'&&n[i+9]=='o'&&n[i+10]=='s'){
			if((n[i+11]==' ' && n[i+12]=='m')||(n[i+11]=='\0')||(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='o'))
				printf("900");
			if(n[i+11]==' ' && n[i+12]=='u' && n[i+13]=='n' && n[i+14]=='o' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("901");
			if(n[i+11]==' ' && n[i+12]=='d' && n[i+13]=='o' && n[i+14]=='s' && (n[i+15]==' '||n[i+15]=='\0'))
				printf("902");
			if(n[i+11]==' ' && n[i+12]=='t' && n[i+13]=='r' && n[i+14]=='e' && n[i+15]=='s' && (n[i+16]==' '||n[1+16]=='\0'))
				printf("903");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='u' && n[i+14]=='a' && n[i+15]=='t' && n[i+16]=='r'&& n[i+17]=='o' && (n[i+18]==' '||n[i+18]=='\0'))
				printf("904");
			if(n[i+11]==' ' && n[i+12]=='c' && n[i+13]=='i' && n[i+14]=='n' && n[i+15]=='c' && n[i+16]=='o' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("905");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='e' && n[i+14]=='i' && n[i+15]=='s' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("906");
			if(n[i+11]==' ' && n[i+12]=='s' && n[i+13]=='i' && n[i+14]=='e' && n[i+15]=='t' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("907");
			if(n[i+11]==' ' && n[i+12]=='o' && n[i+13]=='c' && n[i+14]=='h' && n[i+15]=='o' && (n[i+16]==' '||n[i+16]=='\0'))
				printf("908");
			if(n[i+11]==' ' && n[i+12]=='n' && n[i+13]=='u' && n[i+14]=='e' && n[i+15]=='v' && n[i+16]=='e' && (n[i+17]==' '||n[i+17]=='\0'))
				printf("909");
			if((n[i+11]==' '&&(n[i+12]=='d'||n[i+12]=='o'||n[i+12]=='c'||n[i+12]=='q'||n[i+12]=='v'))||(n[i+11]==' '&&n[i+12]=='t'&&n[i+13]=='r'&&n[i+14]=='e'&&n[i+15]!='s')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='u'&&n[i+14]=='a'&&n[i+15]!='t')||(n[i+11]==' '&&n[i+12]=='c'&&n[i+13]=='i'&&n[i+14]=='n'&&n[i+15]=='c'&&n[i+16]!='c')||(n[i+11]==' '&&n[i+12]=='s'&&n[i+13]=='e'&&n[i+14]!='i')||(n[i+11]==' '&&n[i+12]=='o'&&n[i+13]=='c'&&n[i+14]=='h'&&n[i+15]!=0)||(n[i+11]==' '&&n[i+12]=='n'&&n[i+13]!='u'))
				printf("9");	
		}	
		if(n[i]=='d'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='z')
			printf("10");
		if(n[i]=='o'&&n[i+1]=='n'&&n[i+2]=='c'&&n[i+3]=='e')
			printf("11");
		if(n[i]=='d'&&n[i+1]=='o'&&n[i+2]=='c'&&n[i+3]=='e')
			printf("12");
		if(n[i]=='t'&&n[i+1]=='r'&&n[i+2]=='e'&&n[i+3]=='c'&&n[i+4]=='e')
			printf("13");
		if(n[i]=='c'&&n[i+1]=='a'&&n[i+2]=='t'&&n[i+3]=='o'&&n[i+4]=='r')
			printf("14");
		if(n[i]=='q'&&n[i+1]=='u'&&n[i+2]=='i'&&n[i+3]=='n'&&n[i+4]=='c')
			printf("15");
		if(n[i]=='d'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='c'&&n[i+4]=='i'&&n[i+5]=='s'&&n[i+6]=='e')
			printf("16");
		if(n[i]=='d'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='c'&&n[i+4]=='i'&&n[i+5]=='s'&&n[i+6]=='i')
			printf("17");
		if(n[i]=='d'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='c'&&n[i+4]=='i'&&n[i+5]=='o'&&n[i+6]=='c')
			printf("18");
		if(n[i]=='d'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='c'&&n[i+4]=='i'&&n[i+5]=='n'&&n[i+6]=='u')
			printf("19");
		if(n[i]=='v'&&n[i+1]=='e'&&n[i+2]=='i'&&n[i+3]=='n'&&n[i+4]=='t'&&n[i+5]=='e'){
			if(n[i+6]==' ' && n[i+7]=='y')
				printf("2");
			else
				printf("20");
		}
		if(n[i]=='t'&&n[i+1]=='r'&&n[i+2]=='e'&&n[i+3]=='i'&&n[i+4]=='n'&&n[i+5]=='t'&&n[i+6]=='a'){
			if(n[i+7]==' ' && n[i+8]=='y')
				printf("3");
			else
				printf("30");
		}
		if(n[i]=='c'&&n[i+1]=='u'&&n[i+2]=='a'&&n[i+3]=='r'&&n[i+4]=='e'&&n[i+5]=='n'&&n[i+6]=='t'&&n[i+7]=='a'){
			if(n[i+8]==' ' && n[i+9]=='y')
				printf("4");
			else
				printf("40");
		}
		if(n[i]=='c'&&n[i+1]=='i'&&n[i+2]=='n'&&n[i+3]=='c'&&n[i+4]=='u'&&n[i+5]=='e'&&n[i+6]=='n'&&n[i+7]=='t'&&n[i+8]=='a'){
			if(n[i+9]==' ' && n[i+10]=='y')
				printf("5");
			else
				printf("50");
		}
		if(n[i]=='s'&&n[i+1]=='e'&&n[i+2]=='s'&&n[i+3]=='e'&&n[i+4]=='n'&&n[i+5]=='t'&&n[i+6]=='a'){
			if(n[i+7]==' ' && n[i+8]=='y')
				printf("6");
			else
				printf("60");
		}
		if(n[i]=='s'&&n[i+1]=='e'&&n[i+2]=='t'&&n[i+3]=='e'&&n[i+4]=='n'&&n[i+5]=='t'&&n[i+6]=='a'){
			if(n[i+7]==' ' && n[i+8]=='y')
				printf("7");
			else
				printf("70");
		}
		if(n[i]=='o'&&n[i+1]=='c'&&n[i+2]=='h'&&n[i+3]=='e'&&n[i+4]=='n'&&n[i+5]=='t'&&n[i+6]=='a'){
			if(n[i+7]==' ' && n[i+8]=='y')
				printf("8");
			else
				printf("80");
		}
		if(n[i]=='n'&&n[i+1]=='o'&&n[i+2]=='v'&&n[i+3]=='e'&&n[i+4]=='n'&&n[i+5]=='t'&&n[i+6]=='a'){
			if(n[i+7]==' ' && n[i+8]=='y')
				printf("9");
			else
				printf("90");
		}
		if(n[i]=='u'&&n[i+1]=='n'&&n[i+2]=='o'){
			if((n[0]=='u'&&n[1]=='n'&&n[2]=='o')||(n[i-1]==' '&&n[i-2]!='s'))
				printf("1");
		}
		if(n[i]=='d'&&n[i+1]=='o'&&n[i+2]=='s'&&n[i+3]!='c'){
			if((n[i-1]==' '&&n[i-2]=='y')||(n[0]=='d'&&n[1]=='o'&&n[2]=='s'&&n[3]!='c'))
				printf("2");
		}
		if(n[i]=='t'&&n[i+1]=='r'&&n[i+2]=='e'&&n[i+3]=='s'&&n[i+4]!='c'){
			if((n[i-1]==' '&&n[i-2]=='y')||(n[0]=='t'&&n[1]=='r'&&n[2]=='e'&&n[3]=='s'&&n[4]!='c'))
				printf("3");	
		}
		if(n[i]=='c'&&n[i+1]=='u'&&n[i+2]=='a'&&n[i+3]=='t'&&n[i+4]=='r'&&n[i+5]=='o'&&(n[i+6]!='c')){
			if((n[i-1]==' '&&n[i-2]=='y')||(n[0]=='c'&&n[1]=='u'&&n[2]=='a'&&n[3]=='t'&&n[4]=='r'&&n[5]=='o'&&n[6]!='c'))
				printf("4");
		}
		if(n[i]=='c'&&n[i+1]=='i'&&n[i+2]=='n'&&n[i+3]=='c'&&n[i+4]=='o'){
			if((n[i-1]=='\0')||(n[i-1]==' '&&n[i-2]!='s'))
				printf("5");
		}
		if(n[i]=='s'&&n[i+1]=='e'&&n[i+2]=='i'&&n[i+3]=='s'&&n[i+4]!='c'){
			if((n[i-1]!='i')||(n[i-1]==' '&&n[i-2]=='y')||(n[0]=='s'&&n[1]=='e'&&n[2]=='i'&&n[3]=='s'&&n[4]!='c'))
				printf("6");
		}
		if(n[i]=='s'&&n[i+1]=='i'&&n[i+2]=='e'&&n[i+3]=='t'&&n[i+4]=='e'){
			if((n[-1]!='i')||(n[i-1]==' '&&n[i-2]=='y')||(n[0]=='s'&&n[1]=='i'&&n[2]=='e'&&n[3]=='t'&&n[4]=='e'))
				printf("7");
		}
		if(n[i]=='o'&&n[i+1]=='c'&&n[i+2]=='h'&&n[i+3]=='o'&&n[i+4]!='c'){
			if((n[i-1]!='i')||(n[i-1]==' '&&n[i-2]=='y')||(n[0]=='o'&&n[1]=='c'&&n[2]=='h'&&n[3]=='o'&&n[4]!='c'))
			printf("8");
		}
		if(n[i]=='n'&&n[i+1]=='u'&&n[i+2]=='e'&&n[i+3]=='v'&&n[i+4]=='e'){
			if((n[i-1]!='i')||(n[i-1]==' '&&n[i-2]=='y')||(n[0]=='n'&&n[1]=='u'&&n[2]=='e'&&n[3]=='v'&&n[4]=='e'))
				printf("9");
		}
		if(n[i]=='m'&&n[i+1]=='i'&&n[i+2]=='l'){
			if(n[i+3]==' '){
				if(n[i+4]=='c' && n[i+5]=='o' && n[i+6]=='n')
					printf(".000");
				else
					printf(".");
			}
			if(n[i+3]=='\0')
				printf(".000");
		}
		if(n[i]=='c'&&n[i+1]=='o'&&n[i+2]=='n')
			printf(",");
	} //fin del for
	printf("\n\n");
} //fin funcion transformeLetrasANumeros
