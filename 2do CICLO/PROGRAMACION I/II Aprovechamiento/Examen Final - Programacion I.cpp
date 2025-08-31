#include <stdio.h>
#include <string.h>
#include <time.h>
#include<stdlib.h>
#include<conio.h>

int menu();
void juego(int k,char nombre[][10],int inf[][2]);
int numeroRandom();
void vecesJugo(char nombre[][10]);
void puntajeJugador(char nombre[][10],int inf[][2],int k);
void guardaArchivo(int inf[][2],char nombre[][10],int k);

int main(){
	int opcion;
	int bandera=0;
	int k=0; //contador de juegos
	char nombre[10][10];
	int inf[10][2];
	
	do{
		opcion=menu();
	switch(opcion){
		case 1:{ //jugar
		juego(k,nombre,inf);
		bandera=1;
		guardaArchivo(inf,nombre,k);
		k++;
			break;
		}
		
		case 2:{ //numero de veces que jugo
		if(bandera==1){
			vecesJugo(nombre);
		}
		else
			printf("ERROR: Primero debe jugar al menos una vez.\n");
			break;
		}
		
		case 3:{ //puntaje de jugador
		if(bandera==1){
			puntajeJugador(nombre,inf,k);
		}
		else
			printf("ERROR: Primero debe jugar al menos una vez.\n");
			break;
		}
		
		case 4:{ //ordenado segun puntaje
		if(bandera==1){
			
		}
		else
			printf("ERROR: Primero debe jugar al menos una vez.\n");	
			break;
		}
		
		case 5:{ //salir
			printf("Gracias por usar mi programa.");
			break;
		}
		default:
			printf("Opcion no valida.\n");
	} //fin switch
	}while(opcion!=5); 	
	
	return 0;
} //fin funcion funcion principal

int menu(){
	int op;
	printf("------------------------------------------------------\n");
	printf("             M E N U   D E   O P C I O N E S\n");
	printf("------------------------------------------------------\n");
	printf("1. Jugar\n");
	printf("2. Numero de veces que jugo\n");
	printf("3. Puntaje de un jugador\n");
	printf("4. Ordenado segun puntaje\n");
	printf("5. Salir\n");
	printf("Ingrese una opcion: \n");
	scanf("%d",&op);
	return op;
} //fin funcion menu

void juego(int k,char nombre[][10],int inf[][2]){
	char cTecla;
	int i=0; //contador de lanzamientos
	int j;
	int NumJ1=0,NumJ2=0,NumC1=0,NumC2=0;
	int puntajeJ1=0,puntajeJ2=0;
	
	printf("Ingrese su nombre: ");
	fflush(stdin);
	gets(nombre[k]);
	do{
		printf("Presione ENTER para realizar el lanzamiento del dado\n");
		if(i==0)
			printf("PRIMER LANZAMIENTO\n");
		if(i==1)
			printf("SEGUNDO LANZAMIENTO\n");
		if(i==2)
			printf("TERCER LANZAMIENTO\n");
		
		cTecla = getch();
		if(cTecla==32){
			for(j=0;j<2;j++){
            	NumJ1=numeroRandom();
            	printf("%s\nDADO %d= %d\n",nombre[k],j+1,NumJ1);
           		puntajeJ1+=NumJ1;
            	NumJ2=numeroRandom();
            	printf("COMPUTADORA\nDADO %d= %d\n",j+1,NumJ2);
            	puntajeJ2+=NumJ2;
            }
            printf("Puntaje %s= %d\n",nombre[k],puntajeJ1); 
			printf("Puntaje COMPUTADORA= %d\n",puntajeJ2);
			if(i==2){
				inf[k][1]=puntajeJ1;
				inf[k][2]=puntajeJ2;
				if(puntajeJ1>puntajeJ2)
					printf("GANADOR: %s\n",nombre[k]);
				else
					printf("GANADOR: COMPUTADORA\n");
			}
			i++;
		}
	}while(i<3);
} //fin funcio juego

int numeroRandom(){
	int n; //numero random que se generara
	
	n=(rand()%6); //genera un valor random del 1 al 5
	n=n+1; //sumo uno porque el dado no tiene el valor 0
	return n;	
} //fin funcion numeroRandom

void vecesJugo(char nombre[][10]){
	char name[10];
	int i;
	int cont=0;
	printf("Ingrese el nombre del jugador del cual desea saber el numero de veces que jugo:\n");
	fflush(stdin);
	gets(name);
	for(i=0;i<10;i++){
		if(strcmp(nombre[i],name)==0)
			cont++;
	}
	printf("El jugador \"%s\" jugo %d veces.\n",name,cont);
} //fin funcion vecesJugo

void puntajeJugador(char nombre[][10],int inf[][2],int k){
	char name[10];
	int i;
	int sen=0;

	printf("Ingrese el nombre del jugador del cual desea saber el puntaje:\n");
	fflush(stdin);
	gets(name);
	for(i=0;i<k;i++){
		if(strcmp(nombre[i],name)==0){
			printf("El jugador %s tuvo un puntaje de: %d\n",name,inf[i][1]);
			sen=1;
		}
		else{
			if(i==k-1 && sen==0)
				printf("No se encontro un jugador con el nombre ingresado.\n");
		}		
	}// fin for
} //fin funcion puntajeJugador

void guardaArchivo(int inf[][2],char nombre[][10],int k){
	FILE* archivo;
	int i; //contador 
	
	archivo=fopen("Juego dados.txt","a");
	fprintf(archivo,"Juego %d\nNombre jugador:%s\n",k+1,nombre[k]);
	fprintf(archivo,"Puntaje %s: %d\n",nombre[k],inf[k][1]);
	fprintf(archivo,"Puntaje COMPUTADORA: %d\n\n",inf[k][2]);
	fclose(archivo);
} //fin funcion guardaArchivo

