#include<stdio.h>
#include<time.h>

int menu(); //funcion que muestra el menu de opciones
int pideMesyValida(); //funcion que pide el mes y lo valida
void llenarTemperaturas(int temperaturas[12][31][24],int max,int min); //funcion que llena el vector de las temperaturas durante el año con valores aleatorios
int diasMes(int mes); //determina cuantos dias tiene cada mes
void tempPromedioMes(int mes, int dias,int temperaturas[12][31][24]); //funcion que calcula la temperatura promedio de un mes dado
void tempMaxyMin(int mes,int dias,int temperaturas[12][31][24]); //funcion que determina la temperatura maxima y la minima de un mes dado
void promedioTempMedioDiaMes(int mes,int dias,int temperaturas[12][31][24]); //funcion que calcula el promedio de la temperatura al medio de dia de un mes dado
int pideDia(int dias); //funcion que pide el dia del cual el usuario quiere saber las temperaturas
void muestraTempDeUnDia(int mes,int diaespecifico,int temperaturas[12][31][24]); //funcion que muestra las temperaturas de todo un dia

int main(){
	int temperaturas[12][31][24]; //vector que almacena las temperaturas de todo el año
	int tempmax; //temperatura maxima a la que se va a generar una temperatura aleatoria
	int tempmin; //temperatura minima a la que se va a generar una temperatura aleatoria
	int opcion; //opcion que elige el usuario del menu
	int mes; //mes que leera el programa para determinar la informacion requerida
	int dias; //numero de dias que tiene el mes ingresado
	int diaespecifico; //dia del cual el usuario solicita saber las temperaturas en todas las horas
	
	tempmax=20; //la temperatura maxima sera 30, sin embargo defino como 20 para que en la funcion de llenar vector sumarle 10, con el fin que en determinadas horas del dia la temperatura sea mayor a 10 grados
	tempmin=12; //es la temperatura maxima que se puede llegar por la noche o madrugada
	
	printf("..............................................................................................\n");
	printf("   P R O G R A M A   C O N   M E N %c   S O B R E   T E M P E R A T U R A S   D E L   A %c O\n",233,165);
	printf("..............................................................................................\n");
	printf("AUTOR: BRYAN MENDOZA\n\n");
	do{
		opcion=menu();
		switch(opcion){
			case 1:{ //temperatura promedio de un mes dado
				llenarTemperaturas(temperaturas,tempmax,tempmin);
				mes=pideMesyValida();
				dias=diasMes(mes);
				tempPromedioMes(mes,dias,temperaturas);
				break;
			}
			
			case 2:{ //temperatura maxima y minima de un mes dado
				llenarTemperaturas(temperaturas,tempmax,tempmin);
				mes=pideMesyValida();
				dias=diasMes(mes);
				tempMaxyMin(mes,dias,temperaturas);
				break;
			}
			
			case 3:{ //temperatura promedio al medio dia de todo un mes dado
				llenarTemperaturas(temperaturas,tempmax,tempmin);
				mes=pideMesyValida();
				dias=diasMes(mes);
				promedioTempMedioDiaMes(mes,dias,temperaturas);
				break;
			}
			
			case 4:{ //Temperaturas de un dia dado
				llenarTemperaturas(temperaturas,tempmax,tempmin);
				mes=pideMesyValida();
				dias=diasMes(mes);
				diaespecifico=pideDia(dias);
				muestraTempDeUnDia(mes,diaespecifico,temperaturas);
				break;
			}
			
			case 5:{
				printf("Gracias por usar mi programa");
				break;
			}
			
			default:
				printf("Opcion no valida\n\n");
		} //fin del switch	
	}while(opcion!=5);
	return 0;
}

int menu(){ //funcion que muestra el menu de opciones
	int op;
	printf("....................................................................\n");
	printf("                   M E N %c   D E   O P C I O N E S\n",233);
	printf("....................................................................\n\n");
	printf("1. Temperatura promedio de un mes dado\n");
	printf("2. Temperatura maxima y minima de un mes dado\n");
	printf("3. Temperatura promedio al medio dia de todo un mes dado\n");
	printf("4. Temperaturas de un dia dado\n");
	printf("5. Salir\n");
	printf("Ingrese una opcion: ");
	scanf("%d",&op);
	return op;
}//fin funcion menu

int pideMesyValida(){ //funcion que pide el mes y lo valida
	int n;//valor que digita el usuario
	int mes=0; //nuemero de mes que va a leer el programa, ya que los vectores inician en 0
	
	do{
		printf("Ingrese el mes del que solicita la informaci%cn en numero:",162);
		scanf("%d",&n);
		if(n<1||n>12)	
			printf("ERROR: El mes ingresado es incorrecto\n");
	}while(n<1||n>12);
	mes=n-1;
	return mes;
}//fin funcion pideMesyValida

void llenarTemperaturas(int temperaturas[12][31][24],int max, int min){//funcion que llena el vector de las temperaturas durante el año con valores aleatorios
	int i,j,k;//contadores de bucle
	int n; //numero random que se generara
	srand(time(NULL));
	for(i=0;i<12;i++){
		if(i==0||i==2||i==4||i==6||i==7||i==9||i==11){
			temperaturas[i][31];
			for(j=0;j<31;j++){
				for(k=0;k<24;k++){
					if((k>=20 && k<24) || (k>=0 && k<10)){ //en este rango de horas la temperatura maxima solo podra ser min=12 grados
						rand(time(NULL));
						n=(rand()%min);
						temperaturas[i][j][k]=n;
					}
					else{
						rand(time(NULL));
						n=(rand()%max)+10; //se le suma 10 a la temperatura random generada, con el fin que a estas horas la temperatura sea mayor a 10 grados para que sea mas realista
						temperaturas[i][j][k]=n;
						}
				}//fin for con k
			}//fin for con j
		}
		if(i==1){
			temperaturas[i][28];
			for(j=0;j<28;j++){
				for(k=0;k<24;k++){
					if((k>=20 && k<24) || (k>=0 && k<10)){ //en este rango de horas la temperatura maxima solo podra ser min=15 grados
						rand(time(NULL));
						n=(rand()%min);
						temperaturas[i][j][k]=n;
					}
					else{
						rand(time(NULL));
						n=(rand()%max)+10; //se le suma 10 a la temperatura random generada, con el fin que a estas horas la temperatura sea mayor a 10 grados para que sea mas realista
						temperaturas[i][j][k]=n;
					}
				}//fin for con k
			}//fin for con j
		}
		if(i==3||i==5||i==8||i==10){
			temperaturas[i][30];
			for(j=0;j<30;j++){
				for(k=0;k<24;k++){
					if ((k>=20 && k<24) || (k>=0 && k<10)){ //en este rango de horas la temperatura maxima solo podra ser min=15 grados
						rand(time(NULL));
						n=(rand()%min);
						temperaturas[i][j][k]=n;
					}
					else{
						rand(time(NULL));
						n=(rand()%max)+10; //se le suma 10 a la temperatura random generada, con el fin que a estas horas la temperatura sea mayor a 10 grados para que sea mas realista
						temperaturas[i][j][k]=n;
					}
				}//fin for con k
			}//fin for con j
		}
	}//fin for con i
} //fin funcion llenarTemperaturas

int diasMes(int mes){ //determina cuantos dias tiene cada mes
	int dias;
	int i;
	
	if(mes==0||mes==2||mes==4||mes==6||mes==7||mes==9||mes==11){
		dias=31;
	}
	if(mes==1)
		dias=28;
	if(mes==3||mes==5||mes==8||mes==10){
		dias=30;
	}
	return dias;
}

void tempPromedioMes(int mes, int dias, int temperaturas[12][31][24]){ //funcion que calcula la temperatura promedio de un mes dado
	int i,j; //contadores del bucle
	int temptot=0; //acumulador de las temperaturas
	int n; //auxiliar que almacena la temperatura
	int cont=0; //contador de las horas en todo el mes
	float promedio; //promedio de temperaturas

	for(i=0;i<dias;i++){
		for(j=0;j<24;j++){
			n=temperaturas[mes][i][j];
			temptot=temptot+n;
			cont++;
		}//fin for con k
	}//fin for con j
	promedio=(float)temptot/cont;
	printf("El promedio de temperaturas del mes %d es %.2f C%c.\n",mes+1,promedio,248);
}

void tempMaxyMin(int mes,int dias,int temperaturas[12][31][24]){ //funcion que determina la temperatura maxima y la minima de un mes dado
	int tmax; //temperatura maxima
	int tmin; //temperatura minima
	int i,j; //contadores del bucle
	
	tmax=temperaturas[mes][0][0];
	tmin=temperaturas[mes][0][0];
	for(i=0;i<dias;i++){
		for(j=0;j<24;j++){
			if(temperaturas[mes][i][j]>tmax)
				tmax=temperaturas[mes][i][j];
			if(temperaturas[mes][i][j]<tmin)
				tmin=temperaturas[mes][i][j];
		}// fin bucle con j(horas)
	} //fin bucle con i(dias)
	printf("La temperatura maxima del mes %d es %d C%c y la temperatura minima es %d C%c\n",mes+1,tmax,248,tmin,248);
}//fin funcion temMaxyMin

void promedioTempMedioDiaMes(int mes,int dias,int temperaturas[12][31][24]){ //funcion que calcula el promedio de la temperatura al medio de dia de un mes dado
	int i;//contadores del bucle
	int n;//auxiliar que almacena la temperatura en un dia dado
	int temptotmediodia=0;//acumulador de las temperaturas del media dia de un mes dado
	float promedio=0;//promedio de las temperaturas al medio dia de un mes dado
	
	for(i=0;i<dias;i++){
		n=temperaturas[mes][i][11];
		temptotmediodia=temptotmediodia+n;
	}
	promedio=(float)temptotmediodia/dias;
	printf("El promedio de temperaturas al medio dia del mes %d es %.2f C%c\n",mes+1,promedio,248);
}//fin funcion promedioTempMedioDiaMes

int pideDia(int dias){ //funcion que pide el dia del cual el usuario quiere saber las temperaturas
	int diaingresado; //dia ingresado por el usuario
	int diaespecifico; //dia que leera el programa
	do{
		printf("Ingrese el dia del cual quiere saber las temperaturas: ");
		scanf("%d",&diaingresado);	
		if(diaingresado>dias||diaingresado<1)
			printf("ERROR: El dia ingresado es incorrecto de acuerdo al mes ingresado.\n");
	}while(diaingresado>dias||diaingresado<1);
	diaespecifico=diaingresado-1; //dia que leera el programa
	return diaespecifico;
} //fin funcion pideDia

void muestraTempDeUnDia(int mes,int diaespecifico,int temperaturas[12][31][24]){ //funcion que muestra las temperaturas de todo un dia
	int i,j; //contadores del bucle
	printf("Estas son las temperaturas del dia %d del mes %d\n\n",diaespecifico+1,mes+1);
	printf("--------------------------\n");
	printf("|   Hora   | Temperatura |\n");
	printf("--------------------------\n");
	for(i=0;i<24;i++){
		printf("|    %d",i+1);
		if(i<9)
		printf("     |");
		else
		printf("    |");
		printf("     %d C%c",temperaturas[mes][diaespecifico][i],248);
		if(temperaturas[mes][diaespecifico][i]<10)
		printf("    |\n");
		else
		printf("   |\n");
		printf("--------------------------\n");
	}
} //fin funcion muestraTempDeUnDia
