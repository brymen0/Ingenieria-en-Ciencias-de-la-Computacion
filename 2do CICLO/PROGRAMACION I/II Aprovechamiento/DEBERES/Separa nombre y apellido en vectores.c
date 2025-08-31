#include<stdio.h>
#include<string.h>

void ingresoNombres(int npersonas,char nombresCompletos[][30]);
void cuentaCaracteres(int npersonas,char nombresCompletos[][30],int longitudes[]);
void separaNombresyApellidos(int npersonas,char nombresCompletos[][30],char name[][15],char apellido[][15]);
void muestraApellidoyNombres(int npersonas,char vnames[][15],char vapellidos[][15]);

int main(){
	int npersonas; //numero de personas
	
	printf("-------------------------------------------------------------------------------------\n");
	printf("Programa que lee n nombres y los separa en apellidos y nombres en vectores diferentes\n");
	printf("-------------------------------------------------------------------------------------\n");
	printf("AUTOR: BRYAN MENDOZA\n\n");
	
	printf("Ingrese la cantidad de personas que va a digitar el nombre:");
	scanf("%d",&npersonas);
	
	char nombresCompletos[npersonas][30];// vector que almacena los nombres completos de las personas
	int longitudes[npersonas]; //vector que almacena las longitudes de los nombres completos
	char vnombres[npersonas][15]; //vector que almacena solo los nombres
	char vapellidos[npersonas][15]; //vector que alamacena solo los apellidos
	
	ingresoNombres(npersonas,nombresCompletos);
	cuentaCaracteres(npersonas,nombresCompletos,longitudes);
	separaNombresyApellidos(npersonas,nombresCompletos,vnombres,vapellidos);
	muestraApellidoyNombres(npersonas,vnombres,vapellidos);
	
	return 0;
}

void ingresoNombres(int npersonas,char nombresCompletos[][30]){
	int i; //contador del bucle
	for(i=0;i<npersonas;i++){
		printf("Ingrese el nombre de la %d persona: ",i+1);
		fflush(stdin); //limpia el buffer
		gets(nombresCompletos[i]);
	}
}//fin de la funcion ingresoNombres

void cuentaCaracteres(int npersonas,char nombresCompletos[][30],int longitudes[]){
	int i; //contador del bucle
	char nombreaux[20];
	for(i=0;i<npersonas;i++){
		strcpy(nombreaux,nombresCompletos[i]); //copia los nombresCompletos en la cadena nombreaux
		longitudes[i]=strlen(nombreaux);
		printf("El nombre %d tiene %d caracteres\n",i+1,longitudes[i]);
	}
}// fin de la funcion cuentaCaracteres

void separaNombresyApellidos(int npersonas,char nombresCompletos[][30],char vnames[][15],char vapellidos[][15]){
	int i;
    char *token;
    for (i=0;i<npersonas;++i) {
        token = strtok(nombresCompletos[i], " "); //almacena en token la cadena antes del espacio, es decir solo el nombre
        strcpy(vnames[i],token); //copia el token antes almacenado en el vector de nombres
        token = strtok(NULL, " "); //almacena en token la cadena despues del espacio, es decir solo el apellido
        strcpy(vapellidos[i],token);//copia el token antes almacenado en el vector de apellidos
    }
}//fin de la funcion separaNombresyApellidos

void muestraApellidoyNombres(int npersonas,char vnames[][15],char vapellidos[][15]){
	int i;
	for(i=0;i<npersonas;i++){
		printf("%s, %s\n",vapellidos[i],vnames[i]);
	}
}//fin de la funcion muestraApellidoyNombres
