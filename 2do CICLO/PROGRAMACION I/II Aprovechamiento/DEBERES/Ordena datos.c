#include<stdio.h>
#include<string.h>

int menuPrincipal(); //funcion que muestra el menu principal
int ingresaNPersonas(); //funcion que pide y valida el numero de personas que ingrsaran sus datos
void ingresarCedula(char ced[]); //funcion que pide la cedula
int validaNumDigitos(char ced[]); //funcion que valida que la cedula tenga 10 digitos
int validaCedula(char ced[]); //funcion que la cedula sea ecuatoriana
void ingresayValidaNombres(char name[]); //funcion que pide y valida los nombres
void ingresayValidaApellidos(char apellido[]); //funcion que pide y valida los apellidos
void ingresayValidaEdad(char age[]); //funcion que pide y valida la edad
int menuOrdenar(); //funcion que muestra el menu de ordenar
void ordenarCedula(char infcompleta[][4][70], int npersonas); //funcion que ordena por cedula
void ordenarApellido(char infcompleta[][4][70], int npersonas); //funcion que ordena por apellido
void ordenarEdad(char infcompleta[][4][70], int npersonas); //funcion que ordena por edad
void mostrarInfCompleta (char infcompleta[][4][70], int npersonas); //fucion que muestra toda la informacion ordenada

int main(){
	int opcion;// opcion que escoge el usuario del menu principal
	int npersonas;//numero de personas que van a ingresar sus infcompleta
	int i; //contador del bucle
	char name[20]; //almacena el nombre temporalmente
	char apellido[20]; //almacena el apellido temporalmente
	char cedula[10]; //almacena la cedula temporalmente
	char age[2]; //alamcena la edad temporalmente
	int validadordigitos; //indica si la cedula tiene 10 digitos 
	int validadorcedula; //indica si la cedula es valida
	int bandera=0; //indica si ya se ingreso los datos
	int opcionOrdenar; //opcion de como quiere ordenar los datos el usuario
	int j; //contador
	char infcompleta[100][4][70]; //vector que almacena toda la informacion junta
	
	printf(".........................................................................\n");
	printf("                           PROGRAMA QUE ORDENA DATOS\n");
	printf(".........................................................................\n");
	printf("AUTOR: BRYAN MENDOZA\n\n");
	do{
	opcion=menuPrincipal();
	switch(opcion)
	{
		case 1://Ingresar datos
		{
			npersonas=ingresaNPersonas();
		
			for(i=0;i<npersonas;i++){
				j=0;//inicializo el contador
				printf("PERSONA %d\n",i+1);
				do{
					ingresarCedula(cedula);
					validadordigitos=validaNumDigitos(cedula);
					if(validadordigitos==1)
						printf("ERROR: La cedula ingresada no tiene 10 digitos\n");
					validadorcedula=validaCedula(cedula);
					if(validadorcedula==1)
						printf("Cedula invalida\n");
				}while(validadordigitos==1||validadorcedula==1);
				strcat(cedula,", ");
				strcpy(infcompleta[i][j],cedula);
		
				j++;
				ingresayValidaNombres(name);
				strcat(name,", ");
				strcpy(infcompleta[i][j],name);
		
				j++;
				ingresayValidaApellidos(apellido);
				strcat(apellido,", ");
				strcpy(infcompleta[i][j],apellido);
		
				j++;
				ingresayValidaEdad(age);
				strcat(age,".");
				strcpy(infcompleta[i][j],age);
			}
			bandera=1;
		break;
		}
		case 2: //Ordenar 
		{
			if(bandera==1){
				opcionOrdenar=menuOrdenar();
				switch(opcionOrdenar){
					case 1: //Por cedula
					{
						ordenarCedula (infcompleta,npersonas);
						bandera=2;	
					break;
					}
					
					case 2: //por apellido
					{
						ordenarApellido(infcompleta,npersonas);
						bandera=2;	
					break;
					}
					
					case 3: //por edad
					{
						ordenarEdad(infcompleta,npersonas);
						bandera=2;	
					break;
					}
					
					case 4:
					break;
					
					default:
						printf("Opcion no valida.\n");
				}	
			}
			else
				printf("ERROR: Primero debe ingresar datos.\n");
		break;
		}
		
		case 3: //Listar
		{
			if(bandera==2){
				printf ("Los datos ordenados serian: \n");
				mostrarInfCompleta(infcompleta,npersonas);
			}
			else
				if(bandera==0)
					printf("ERROR: Primero debe ingresar datos.\n");
				if(bandera==1)
					printf("ERROR: Primero debe escoger el orden en el que se va a listar los datos.\n");
		break;
		}
		
		case 4: //Salir
			printf("Gracias por usar mi programa.\n");
		break;
		
		default:
			printf("Opcion no valida.\n");
	}
	}while(opcion!=4);
	
	return 0;
} //fin funcion principal

int menuPrincipal(){
	int op; //opcion que ingresa el usuario
	printf("---------------------------------------------------------------\n");
	printf("               M E N U   D E    O P C I O N E S\n");
	printf("---------------------------------------------------------------\n\n");
	printf("1. Ingresar datos\n");
	printf("2. Ordenar\n");
	printf("3. Listar\n");
	printf("4. Salir\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&op);
	return op;
} //fin de la funcion menuPrincipal

int ingresaNPersonas(){
	int n; //numero de personas que ingresa el usuario
	do{
		printf("Ingrese el numero de personas a registrar: ");
		scanf("%d",&n);	
		if(n<0 || n>100)
			printf("ERROR: Debe ingresar entre 1 y 100 personas.\n");
	}while(n<0 || n>100);
	return n;
} //fin funcion ingresaNPersonas

void ingresarCedula(char cedula[]){
	printf("Ingrese su numero de cedula:");
	fflush(stdin);
	gets(cedula);
}//fin funcion ingresarCedula

int validaNumDigitos(char cedula[]){
	int correcto;
		if(strlen(cedula)==10)
			correcto=0;
		else 
			correcto=1;
	return correcto;
}//fin funcion validaNumDigitos

int validaCedula(char cedula[]){
	int i; //contador del bucle
	int n=0; //variable que almacena el valor entero del digito
	int res; //residuo de la multiplicacion
	int sumaDigitos; //suma de los digitos resultantes de la multiplicacion
	int sobrante; //valor que sobra al dividir por 10 a la suma de digitos
	int verificador; //numero verificador de la cedula
	int aux; //auxiliar
	int valido; //indica si la cedula es valida o no
	
	for(i=0;i<10;i++){
		n=cedula[i]-'0';
		if(i%2==0){
			res=n*2;
			if(res>=10)
			res=res-9;	
		}
		else{
			res=n*1;
		}
		sumaDigitos+=res;
	}
	aux=sumaDigitos-(cedula[9]-'0');
	sobrante=aux%10;
	if(sobrante==0)
		verificador=0;
	else
		verificador=10-sobrante;
	
	if(verificador==(cedula[9]-'0'))
		valido=0;
	else
		valido=1;

	return valido;
}//fin funcion validaCedula

void ingresayValidaNombres(char name[]){
	int i; //contador del bucle
		do{
			printf("Ingrese el nombre: ");
			fflush(stdin); //limpia el buffer
			gets(name);	
			if(strlen(name)<3)
				printf("ERROR: Nombre ingresado invalido.\n");
		}while(strlen(name)<3);
}//fin funcion ingresayValidaNombres

void ingresayValidaApellidos(char apellido[]){
	int i; //contador del bucle
		do{
			printf("Ingrese el apellido: ");
			fflush(stdin);
			gets(apellido);	
			if(strlen(apellido)<3)
				printf("ERROR: Apellido ingresado invalido.\n");
		}while(strlen(apellido)<3);
}// fin funcion ingresayValidaApellidos

void ingresayValidaEdad(char age[]){
	int n; //valor en entero del ascii
	do{
		printf("Ingrese la edad: ");
		gets(age);
		n=atoi(age);
		if(n<1||n>=100)
			printf("ERROR: Edad ingresada incorrecta.\n");	
	}while(n<1||n>=100);
}//fin funcion ingresayValidaEdad

int menuOrdenar(){
	int opOr; //opcion q ingresa el usuario para ordenar
	printf("1. Por cedula\n");
	printf("2. Por apellido\n");
	printf("3. Por edad\n");
	printf("4. Regresar al menu principal\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&opOr);
	return opOr;
}//fin funcion menuOrdenar

void ordenarCedula(char infcompleta[][4][70], int npersonas){
	int i,j,k; //contadores del bucle
	char temporal [4][70];//varible temporal para la cedula
	
	for (i=0;i<npersonas;i++){
		for (j=0;j<npersonas-1;j++){
			if (strcmp(infcompleta[j][0],infcompleta[j+1][0])==1){
				for (k=0;k<4;k++) {
					strcpy(temporal[k], infcompleta[j][k]);
					strcpy (infcompleta[j][k], infcompleta[j+1][k]);
					strcpy (infcompleta[j+1][k], temporal[k]);
				}
			}
		}
	}						
	printf ("La informacion se ha ordenado con exito.\nDe menor a mayor segun el numero de cedula.\n");
}//fin funcion ordenarCedula

void ordenarApellido(char infcompleta[][4][70], int npersonas){
	int i,j,k; //contadores del bucle
	char temporal [4][70]; //variable que alamacena el apellido temporalmente
	
	for (i=0;i<npersonas;i++) {
		for (j=0;j<npersonas-1;j++) {
			if (strcmp(infcompleta[j][2],infcompleta[j+1][2])==1) {
				for (k=0;k<4;k++) {
					strcpy(temporal[k], infcompleta[j][k]);
					strcpy (infcompleta[j][k], infcompleta[j+1][k]);
					strcpy (infcompleta[j+1][k], temporal[k]);
				}
			}
		}
	}				
	printf ("La informacion se ha ordenado con exito.\nEn orden alfabetico segun el apellido.\n");	
}//fin funcion ordenarApellido

void ordenarEdad(char infcompleta[][4][70], int npersonas){
	int i,j,k; //contadores del bucle
	char temporal [4][70]; //variable que alamcena temporalmente la edad
	
	for (i=0;i<npersonas;i++) {
		for (j=0;j<npersonas-1;j++) {
			if (strcmp(infcompleta[j][3],infcompleta[j+1][3])==1) {
				for (k=0;k<4;k++) {
					strcpy(temporal[k], infcompleta[j][k]);
					strcpy (infcompleta[j][k], infcompleta[j+1][k]);
					strcpy (infcompleta[j+1][k], temporal[k]);
				}
			}
		}
	}				
	printf ("La informacion se ha ordenado con exito.\nDe menor a mayor segun la edad.\n");
}//fin funcion ordenarEdad

void mostrarInfCompleta (char infcompleta[][4][70], int npersonas){
	int i,j; //contadores del bucle
	for (i=0;i<npersonas;i++) {
		printf ("PERSONA %d:\n", i+1);
		for (j=0;j<4;j++) {
			printf ("%s", infcompleta[i][j]);
		}
		printf ("\n");
	}
}//fin funcion mostrarInformacionCompleta
