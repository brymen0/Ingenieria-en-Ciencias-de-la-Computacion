#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define maxlin 4 //la opcion listar, va a mostrar de 4 en 4 lineas

void abreArchivo(char nombreArchivo[]);//funcion que abre un archivo 
int menu(); //funcion que muestra menu de opciones
int ingresaNPersonas(); //funcion que pide y valida el numero de personas que ingresaran sus datos
void ingresaTodosLosDatos(int npersonas,char infcompleta[][6][100]);//funcion que guardara toda la informacion en un arreglo
void ingresarCedula(char cedula[]); //funcion que pide la cedula
int validaNumDigitos(char cedula[]); //funcion que valida que la cedula tenga 10 digitos
int validaCedula(char cedula[]); //funcion que valida que la cedula sea ecuatoriana
void ingresayValidaNombres(char name[]); //funcion que pide y valida los nombres
void ingresayValidaApellidos(char apellido[]); //funcion que pide y valida los apellidos
void ingresayValidaCargo(char cargo[]); //funcion que pide y valida el cargo
void ingresayValidaSueldo(char sueldo[]); //funcion que pide y valida el suedo por hora
void ingresayValidaHoras(char horas[]); //funcion que pide y valida las horas trabajadas al mes
int menuModificacion(); //funcion que muestra el menu de modificacion
int modificarNPersona(int npersonas); //funcion que pregunta de que persona desea modificar los datos
int numeroDatoAModificar(); //funcion que pregunta que dato desea modificar
void modificaSoloUnDato(int numpersona,int numdato,char infcompleta[][6][100]); //funcion que modifica solo un dato
void modificaTodosLosDatosDeUnaPersona(int numpersona,char infcompleta[][6][100]); //funcion que modifica todos los datos de una personas
int menuEliminar(); //funcion que muestra el menu eliminar
void eliminaSoloUnDato(int numpersona,int numdato,char infcompleta[][6][100]); //funcion que elimina solo un dato de una persona
void eliminaTodosLosDatosDeUnaPersona(int numpersona,char infcompleta[][6][100]); //funcion que elimina todos los datos de una persona
void eliminaTodosLosDatosDeTodasLasPersonas(int npersonas,char infcompleta[][6][100]); //funcion que elimina todos los datos de todas las personas
int numeroPersonaACalcularSueldo(int npersonas); //funcion que pide la persona de la cual se quiere saber el sueldo
int tipoTrabajador(); //funcion que pide si es empleado o empleador
void calculaSueldo(int numepersona,char infcompleta[][6][100],int tt); //funcion que calcula el sueldo de la persona
void cambiaHoja(char texto [][100], int max); //funcion que va cambiando de hoja
void mostrarLineas(char texto [][100], int a, int b, int max); //funcion que lista cada 4 lineas
void opcionesPagina();//funcion que muestra las opciones de pagina
void listar(char nombreArchivo[]); //funcion que lista los datos cambiando de pagina
void grabaDatosArchivo(char nombreArchivo[],char infcompleta[][6][100],int npersonas); //funcion que graba los datos ingresados en el archivo

int main(){
	FILE *archivo;
	char nombreArchivo[20]; //nombre del archivo a abrir
	int npersonas; //numero de personas que van a ingresar sus datos
	char infcompleta[100][6][100]; //vector que almacena toda la informacion de todas las personas
	int opcion; //opcion escogida por el usuario del menu principal
	int opcionModificar; //opcion escogida por el usuario del menu modificar
	int opcionEliminar; //opcion escogida por el usuario del menu eliminar
	int bandera=0; //indica si se ingreso los datos
	int numeroPersona; //numero de la persona que el usuario desea cambiar algun dato
	int numeroDato; //numero de dato que desea cambiar el usuario
	int personaSueldo; //numero de la persona que se desea saber el suelgo
	int tTrabajador; //empleado o empleador	
	int noSueldoPersona=-1; //indica si se puede calcular el sueldo de esa persona
	
	printf(".............................................................................................................\n");
	printf("   P R O G R A M A   C O N   M E N %c   S O B R E  C A L C U L O  D E   S U E L D O   Y   L I S T A D O\n",233);
	printf(".............................................................................................................\n");
	printf("AUTOR: BRYAN MENDOZA\n\n");
	
	abreArchivo(nombreArchivo);
		do{
		opcion=menu();
		switch(opcion){
			case 1:{ //Ingreso de datos
				npersonas=ingresaNPersonas();
				ingresaTodosLosDatos(npersonas,infcompleta);
				grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
				bandera=1; //indica que ya se ingresaron los datos y se puede escoger las siguientes opciones
				break;
			}
			
			case 2:{ //Modificacion de datos
				if(bandera==1){
				opcionModificar=menuModificacion();
				switch(opcionModificar){
					case 1:{ // Desea cambiar solo un dato de una persona
						numeroPersona=modificarNPersona(npersonas);
						numeroDato=numeroDatoAModificar();
						modificaSoloUnDato(numeroPersona,numeroDato,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han modificado exitosamente!\n");
						break;
					}
					case 2:{ //Desea cambiar todos los datos de una sola persona
						numeroPersona=modificarNPersona(npersonas);
						modificaTodosLosDatosDeUnaPersona(numeroPersona,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han modificado exitosamente!\n");
						break;
					}
					case 3:{ //Desea cambiar todos los datos de todas las personas
						ingresaTodosLosDatos(npersonas,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han modificado exitosamente!\n");
						break;
					}
					case 4: //salir del menu modificar	
					default:
						printf("Opcion no valida.\n");
					} //fin del switch(opcionModificar)
				} //fin del if
				else
					printf("ERROR: Primero debe ingresar datos.\n");
				break;
			}
			
			case 3:{ //Eliminación de datos
				if(bandera==1){
					opcionEliminar=menuEliminar();
				switch(opcionEliminar){
					case 1:{ // Desea eliminar solo un dato de una persona
						numeroPersona=modificarNPersona(npersonas);
						numeroDato=numeroDatoAModificar();
						if(numeroDato==3)
							noSueldoPersona=numeroPersona; //indica de que persona se elimino el sueldo y no se podra calcular 
						eliminaSoloUnDato(numeroPersona,numeroDato,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han eliminado exitosamente!\n");
						break;
					}
					case 2:{ //Desea eliminar todos los datos de una sola persona
						numeroPersona=modificarNPersona(npersonas);
						noSueldoPersona=numeroPersona; //indica de que persona se elimino los datos y no se podra calcular el sueldo
						eliminaTodosLosDatosDeUnaPersona(numeroPersona,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han eliminado exitosamente!\n");
						bandera=3;
						break;
					}
					case 3:{ //Desea eliminar todos los datos de todas las personas
						eliminaTodosLosDatosDeTodasLasPersonas(npersonas,infcompleta);
						grabaDatosArchivo(nombreArchivo,infcompleta,npersonas);
						printf("Los datos se han eliminado exitosamente!\n");
						bandera=2;
						break;
					}
					case 4: //salir del menu eliminar	
					default:
						printf("Opcion no valida.\n");
					} //fin del switch(opcionModificar)
				} //fin del if
				else
					printf("ERROR: Primero debe ingresar datos.\n");
				break;
			}
			
			case 4:{ //Calculo de sueldo
				if(bandera==1){
					personaSueldo=numeroPersonaACalcularSueldo(npersonas);	
					if(personaSueldo==noSueldoPersona)
						printf("El dato del sueldo fue eliminado de esta persona, por lo tanto no se puede calcular.\n");
					else{
						tTrabajador=tipoTrabajador();
						calculaSueldo(personaSueldo,infcompleta,tTrabajador);
					}
				}// fin if(bandera==1)
				else
					if(bandera==0)
						printf("ERROR: Primero debe ingresar datos.\n");
					if(bandera==2)
						printf("ERROR: Debe ingresar datos nuevamente, porque los que se tenian fueron eliminados.\n");
				break;
			}
			
			case 5:{ //Listado de personal
				if(bandera==1){
					listar(nombreArchivo);	
				}
				else
					if(bandera==0)
						printf("ERROR: Primero debe ingresar datos.\n");
					if(bandera==2)
						printf("ERROR: No hay datos que listar, porque los que se tenian fueron eliminados.\n");
				break;
			}
			
			case 6:{ //Salir
				printf("Gracias por usar mi programa");
				break;
			}
			
			default:
				printf("Opcion no valida.\n");
		} //fin del switch(opcion)
	}while(opcion!=6);
	
	return 0;
} //fin funcion principal

void abreArchivo(char nombreArchivo[]){ //funcion que abre un archivo
	FILE *archivo;
	int i;//contador del bucle
	int validoArchivo=0; //indica si el nombre del archivo es valido
	char nA[20]; //se copia el nombre del archivo
	do{
		printf("Ingrese el nombre del archivo: ");
		gets(nombreArchivo);
		strcpy(nA,nombreArchivo);
		for(i=0;i<strlen(nA);i++){
			if(nA[i]=='.'&&nA[i+1]=='t'&&nA[i+2]=='x'&&nA[i+3]=='t'&&nA[i+4]=='\0')
				validoArchivo=1;
		} //fin del for
		if(validoArchivo!=1)
			printf("ERROR: Archivo no valido.\n");
	}while(validoArchivo!=1);
	archivo=fopen(nombreArchivo,"wt");
	printf("Archivo abierto con exito.\n");
	fclose(archivo);
} //fin funion abreArchivo

int menu(){ //funcion que muestra el menu de opciones
	int op;
	printf("....................................................................\n");
	printf("      M E N %c   D E   O P C I O N E S   P R I N C I P A L\n",233);
	printf("....................................................................\n\n");
	printf("1. Ingreso de datos\n");
	printf("2. Modificacion de datos\n");
	printf("3. Eliminacion de datos\n");
	printf("4. Calculo de sueldo\n");
	printf("5. Listado de personal\n");
	printf("6. Salir\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&op);
	return op;
}//fin funcion menu

int ingresaNPersonas(){ //funcion que pide y valida el numero de personas que ingresaran sus datos
	int n; //numero de personas que ingresa el usuario
	do{
		printf("Ingrese el numero de personas a registrar: ");
		scanf("%d",&n);	
		if(n<0 || n>100)
			printf("ERROR: Debe ingresar entre 1 y 100 personas.\n");
	}while(n<0 || n>100);
	return n;
} //fin funcion ingresaNPersonas

void ingresaTodosLosDatos(int npersonas,char infcompleta[][6][100]){
	int i,j; //contadores
	char name[20]; //almacena el nombre temporalmente
	char apellido[20]; //almacena el apellido temporalmente
	char cedula[10]; //almacena la cedula temporalmente
	char sueldo[2]; //almacena el sueldo temporalmente
	char cargo[20]; //almacena el cargo temporalmente
	char horas[3]; //almacena las horas trabaas al mes temporalmente
	int validadordigitos; //indica si la cedula tiene 10 digitos 
	int validadorcedula; //indica si la cedula es valida
	
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
			ingresayValidaCargo(cargo);
			strcat(cargo,", ");
			strcpy(infcompleta[i][j],cargo);
			
			j++;
			ingresayValidaSueldo(sueldo);
			strcat(sueldo,", ");
			strcpy(infcompleta[i][j],sueldo);
			
			j++;
			ingresayValidaHoras(horas);
			strcpy(infcompleta[i][j],horas);
			}
}//fin funcion ingresaTodosLosDatos

void ingresarCedula(char cedula[]){ //funcion que pide la cedula
	printf("Ingrese su numero de cedula:");
	fflush(stdin);
	gets(cedula);
}//fin funcion ingresarCedula

int validaNumDigitos(char cedula[]){ //funcion que valida que la cedula tenga 10 digitos
	int correcto;
		if(strlen(cedula)==10)
			correcto=0;
		else 
			correcto=1;
	return correcto;
}//fin funcion validaNumDigitos

int validaCedula(char cedula[]){ //funcion que valida que la cedula sea ecuatoriana
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

void ingresayValidaNombres(char name[]){ //funcion que pide y valida los nombres
	int i; //contador del bucle
		do{
			printf("Ingrese el nombre: ");
			fflush(stdin); //limpia el buffer
			gets(name);	
			if(strlen(name)<3)
				printf("ERROR: Nombre ingresado invalido.\n");
		}while(strlen(name)<3);
}//fin funcion ingresayValidaNombres

void ingresayValidaApellidos(char apellido[]){ //funcion que pide y valida los apellidos
		do{
			printf("Ingrese el apellido: ");
			fflush(stdin);
			gets(apellido);	
			if(strlen(apellido)<3)
				printf("ERROR: Apellido ingresado invalido.\n");
		}while(strlen(apellido)<3);
}// fin funcion ingresayValidaApellidos

void ingresayValidaCargo(char cargo[]){ //funcion que pide y valida el cargo
	do{
		printf("Ingrese el cargo que ocupa en la empresa: ");
		fflush(stdin);
		gets(cargo);	
		if(strlen(cargo)<4)
			printf("ERROR: Cargo ingresado no valido.\n");
	}while(strlen(cargo)<4);
} //fin funcion ingresayValidaCargo

void ingresayValidaSueldo(char sueldo[]){ //funcion que pide y valida el sueldo por hora
	int n; //valor en entero del ascii
	do{
		printf("Ingrese el sueldo por hora en entero: ");
		fflush(stdin);
		gets(sueldo);
		n=atoi(sueldo);
		if(n<1||n>20)
			printf("ERROR: Sueldo por hora ingresado no valido.\n");	
	}while(n<1||n>20);
}//fin funcion ingresayValidaSueldo

void ingresayValidaHoras(char horas[]){ //funcion que pide y valida las horas trabajadas al mes
	int n; //valor en entero del ascii
	do{
		printf("Ingrese las horas trabajadas al mes en entero: ");
		fflush(stdin);
		gets(horas);
		n=atoi(horas);
		if(n<1||n>200)
			printf("ERROR: Horas trabajadas al mes ingresadas no validas.\n");	
	}while(n<1||n>200);
}//fin funcion ingresayValidaSueldo

int menuModificacion(){ //funcion que muestra el menu de modificacion
	int opMod; //opcion escogida por el usuario del menu modificar
	printf("....................................................................\n");
	printf("                M E N %c   M O D I F I C A R\n",233);
	printf("....................................................................\n");
	printf("1. Desea cambiar solo un dato de una persona.\n");
	printf("2. Desea cambiar todos los datos de una sola persona.\n");
	printf("3. Desea cambiar todos los datos de todas las personas.\n");
	printf("4. Salir del menu modificar.\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&opMod);
	return opMod;
} ///fin funcion menuModificacion

int modificarNPersona(int npersonas){ //funcion que pregunta de que persona desea modificar los datos
	int numpersona;
	do{
		printf("Ingrese el numero de persona que desea cambiar los datos: ");
		scanf("%d",&numpersona);
		if(numpersona<1||numpersona>npersonas)
			printf("ERROR: El numero de la persona ingresada no existe.\n");
	}while(numpersona<1||numpersona>npersonas);
	numpersona=numpersona-1; //sera el dato que debera leer la computadora
	return numpersona;
}//fin funcion modificarNPersona

int numeroDatoAModificar(){ //funcion que pregunta que dato desea modificar
	int numdato;//numero de dato que desea cambiar el usuario
	do{
		printf("1. Cedula.\n");
		printf("2. Nombre.\n");
		printf("3. Apellido.\n");
		printf("4. Cargo.\n");
		printf("5. Sueldo.\n");
		printf("6. Horas trabajadas.\n");
		printf("Ingrese el dato: ");
		scanf("%d",&numdato);
		numdato=numdato-1; //resto 1 porque ese sera el valor que leera el programa para cambiar el dato ingresado
		if(numdato<0||numdato>5)
			printf("ERROR: El dato a cambiar no existe.\n");
	}while(numdato<0||numdato>5);
	return numdato;
} //fin funcion numeroDatoAModificar

void modificaSoloUnDato(int numpersona,int numdato,char infcompleta[][6][100]){ //funcion que modifica solo un dato
	char name[20]; //almacena el nombre temporalmente
	char apellido[20]; //almacena el apellido temporalmente
	char cedula[10]; //almacena la cedula temporalmente
	char sueldo[2]; //almacena el sueldo temporalmente
	char cargo[20]; //almacena el cargo temporalmente
	char horas[3]; //almacena las horas trabaas al mes temporalmente
	int validadordigitos; //indica si la cedula tiene 10 digitos 
	int validadorcedula; //indica si la cedula es valida
	printf("Ingrese el nuevo dato que reemplazara al anterior\n");
	switch(numdato){
		case 0:{//modificar cedula
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
			strcpy(infcompleta[numpersona][numdato],cedula);
			break;
		}
		case 1:{ //modificar nombre
			ingresayValidaNombres(name);
			strcat(name,", ");
			strcpy(infcompleta[numpersona][numdato],name);
			break;
		}
		case 2:{ //modificar apellido
			ingresayValidaApellidos(apellido);
			strcat(apellido,", ");
			strcpy(infcompleta[numpersona][numdato],apellido);
			break;
		}
		case 3:{ //modificar cargo
			ingresayValidaCargo(cargo);
			strcat(cargo,", ");
			strcpy(infcompleta[numpersona][numdato],cargo);
			break;
		}
		case 4:{ //modificar sueldo
			ingresayValidaSueldo(sueldo);
			strcat(sueldo,", ");
			strcpy(infcompleta[numpersona][numdato],sueldo);
			break;
		}
		case 5:{ //modificar horas trabajadas
			ingresayValidaHoras(horas);
			strcpy(infcompleta[numpersona][numdato],horas);
			break;
		}
	}//fin switch(numdato)
} //fin funcion modificaSoloUnDato

void modificaTodosLosDatosDeUnaPersona(int numpersona,char infcompleta[][6][100]){ //funcion que modifica todos los datos de una personas
	int j; //contador
	char name[20]; //almacena el nombre temporalmente
	char apellido[20]; //almacena el apellido temporalmente
	char cedula[10]; //almacena la cedula temporalmente
	char sueldo[2]; //almacena el sueldo temporalmente
	char cargo[20]; //almacena el cargo temporalmente
	char horas[3]; //almacena las horas trabaas al mes temporalmente
	int validadordigitos; //indica si la cedula tiene 10 digitos 
	int validadorcedula; //indica si la cedula es valida
	j=0;
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
	strcpy(infcompleta[numpersona][j],cedula);
		
	j++;
	ingresayValidaNombres(name);
	strcat(name,", ");
	strcpy(infcompleta[numpersona][j],name);
		
	j++;
	ingresayValidaApellidos(apellido);
	strcat(apellido,", ");
	strcpy(infcompleta[numpersona][j],apellido);
	
	j++;
	ingresayValidaCargo(cargo);
	strcat(cargo,", ");
	strcpy(infcompleta[numpersona][j],cargo);
			
	j++;
	ingresayValidaSueldo(sueldo);
	strcat(sueldo,", ");
	strcpy(infcompleta[numpersona][j],sueldo);
			
	j++;
	ingresayValidaSueldo(horas);
	strcpy(infcompleta[numpersona][j],horas);
} //fin funcion modificaTodosLosDatosDeUnaPersonas

int menuEliminar(){ //funcion que muestra el menu eliminar
	int opEli; //opcion escogida por el usuario del menu modificar
	printf("....................................................................\n");
	printf("                M E N %c   E L I M I N A R\n",233);
	printf("....................................................................\n");
	printf("1. Desea eliminar solo un dato de una persona.\n");
	printf("2. Desea eliminar todos los datos de una sola persona.\n");
	printf("3. Desea eliminar todos los datos de todas las personas.\n");
	printf("4. Salir del menu modificar.\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&opEli);
	return opEli;
} ///fin funcion menuEliminar

void eliminaSoloUnDato(int numpersona,int numdato,char infcompleta[][6][100]){ //funcion que elimina solo un dato de una persona
	strcpy(infcompleta[numpersona][numdato],"");
} //fin funcion eliminaSoloUnDato

void eliminaTodosLosDatosDeUnaPersona(int numpersona,char infcompleta[][6][100]){ //funcion que elimina todos los datos de una persona
	int i;//contador del bucle
	for(i=0;i<6;i++){
		strcpy(infcompleta[numpersona][i],"");
	}
}// fin funcion eliminaTodosLosDatosDeUnaPersona

void eliminaTodosLosDatosDeTodasLasPersonas(int npersonas,char infcompleta[][6][100]){ //funcion que elima todos los datos de todas las personas
	int i,j;//contadores del bucle
	for(i=0;i<npersonas;i++){
		for(j=0;j<6;j++)
			strcpy(infcompleta[i][j],"");
	}
}// fin funcion eliminaTodosLosDatosDeTodasLasPersonas

int numeroPersonaACalcularSueldo(int npersonas){ //funcion que pide la persona de la cual se quiere saber el sueldo
	int numepersona;
	do{
		printf("Ingrese el numero de la persona que desea saber el sueldo: ");
		scanf("%d",&numepersona);
		if(numepersona<0||numepersona>npersonas)
			printf("ERROR: El numero de persona ingresado ni existe.\n");
	}while(numepersona<0||numepersona>npersonas);
	numepersona=numepersona-1; //valor q leera la computadora
	return numepersona;
} //fin funcion numeroPersonaACalcularSueldo

int tipoTrabajador(){ //funcion que pide si es empleado o empleador
	int tt;//tipo de trabador
	printf("Usted es:\n");
	do{
		printf("1. Empleado.\n");
		printf("2. Empleador.\n");
		printf("Ingrese una opcion: ");
		scanf("%d",&tt);
		if(tt>2||tt<1)
			printf("ERROR: Opcion ingresada incorrecta.\n");
	}while(tt>2||tt<1);
} //fin funcion tipoTrabajador

void calculaSueldo(int numepersona,char infcompleta[][6][100],int tt){ //funcion que calcula el sueldo de la persona
	int nhoras; //horas en entero
	int ndolares; //sueldo por hora en entero
	int sueldobruto; //sueldo bruto
	float sueldoneto; //sueldo que recibe la persona
	float descuentoiess; //descuento por el iess
	ndolares=atoi(infcompleta[numepersona][4]);
	nhoras=atoi(infcompleta[numepersona][5]);
	sueldobruto=ndolares*nhoras;
	printf("Sueldo bruto: %d\n",sueldobruto);
	if(tt==1){
		descuentoiess=(float)(9.45*sueldobruto)/100;
		printf("Descuento IEES: %.2f\n",descuentoiess);
		sueldoneto=sueldobruto-descuentoiess;
		printf("Sueldo neto: %.2f\n",sueldoneto);
	}
	if(tt==2){
		descuentoiess=(float)(11.15*sueldobruto)/100;
		printf("Descuento IEES: %.2f\n",descuentoiess);
		sueldoneto=sueldobruto-descuentoiess;
		printf("Sueldo neto: %.2f\n",sueldoneto);
	}
} //fin funcion calculaSueldo

void mostrarLineas(char texto [][100], int a, int b, int max){ //funcion que muestra cada 4 lineas
	int i;
	system("cls");	
	for(i=a; i<b; i++){
		if(a<=max){
			if(a>=0){
				puts(texto[i]);	
			}		
		}
	}	
	opcionesPagina();	
}//fin mostrar lineas

void cambiaHoja(char texto [][100], int max){ //funcion que va cambiando de hoja
	char cTecla; int pos=maxlin; int flag=0;
	while(cTecla!=69&&cTecla!=101){
    	cTecla = getch();
    	if(cTecla == 0){
    		cTecla = getch();	
		}
       	else{
        	switch(cTecla){
        		case 71:{
        			mostrarLineas(texto, 0, maxlin, max); 
					pos=maxlin; 
					break;
				} 
            	case 72:{
            		flag=0;
            		if(pos!=maxlin){
            			mostrarLineas(texto, (pos-maxlin)-maxlin, pos-maxlin, max); 
            			if(pos>0){
            				pos=(pos-maxlin);	
						}	
					}
					break;	
				}
            	case 80:{
            		if(pos!=max&&flag!=1){
            			mostrarLineas(texto, pos, pos+maxlin, max);
            			pos+=maxlin; flag=0;
					}
					if(pos>max){
						flag=1;
					}
					break;					
				}
            	case 79:{
            		mostrarLineas(texto, max-maxlin, max, max);  pos=max; break;
					break;
				}			
			}
    	}  
	}
}//fin funcion cambiaPagina

void opcionesPagina(){//funcion que muestra las opciones de pagina
   	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("Pasar Pag(Flecha Abajo)  |  Regresar Pag(Flecha Arriba)  |  Volver al inicio(HOME)  |  Ir al final(FIN)  |  Salir(E)  ");	
}//fin funcion opcionesPagina

void listar(char nombreArchivo[]){ //funcion que lista los datos cambiando de pagina
	FILE *archivo;
	char linea[100]; //almacena cada linea
	char texto[100][100]; //almacena todo el texto en lineas
	int j=0;
	archivo=fopen(nombreArchivo,"rt");
	while(!(feof(archivo))){
		fgets(linea, 100, archivo);
		if(!(feof(archivo))){
			strcpy(texto[j], linea); 
				j+=1;
		}
	}
	fclose(archivo);
	mostrarLineas(texto, 0, maxlin, j);
	cambiaHoja(texto, j);
} //fin funcion listar

void grabaDatosArchivo(char nombreArchivo[],char infcompleta[][6][100],int npersonas){ //funcion que graba los datos ingresados en el archivo
	FILE *archivo;
	int i,j; //contadores del bucle
	archivo=fopen(nombreArchivo,"wt");
	for(i=0;i<npersonas;i++){
		for(j=0;j<6;j++){
			fprintf(archivo,"%s",infcompleta[i][j]);
		}
		fprintf(archivo,"\n");
	}
	fclose(archivo);
} //fin funcion grabaDatosArchivo
