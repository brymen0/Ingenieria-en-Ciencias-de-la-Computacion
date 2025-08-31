#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "windows.h"
#include <stdlib.h>

void opcionesPagina(); //muestra las opciones de cambiar pagina
void muestraPaginas(char nombre);

int main()
{
	
   char nombre[40];
	FILE *archivo;
	char linea[100]; //almacena la linea del archivo
	int i=0; //contador del bucle
	char cTecla; //tecla presionada por el usuario para cambiar pagina
	int n=0,h=0; //contadores
	
	printf("....................................................................\n");
	printf("  PROGRAMA QUE ABRE UN ARCHIVO Y MUESTRA SU CONTENIDO CADA LINEAS\n"); 
	printf("....................................................................\n");
	printf("Autor: Bryan Mendoza\n\n");
	
	do{
		printf("Ingrese el nombre del archivo:");
		fflush(stdin);
		gets(nombre);
		
		archivo=fopen(nombre,"rt");
		
		if(archivo==NULL){
			printf("ERROR: No existe el archivo.\n");
			i++;
			if(i==5){
				printf("ERROR: Muchos intentos.\n");
				exit(1);
			}
		}
		
	}while(archivo==NULL);
	
		for(i=0;i<10;i++){ //el programa mostrara de 10 en 10 lineas
			fgets(linea,80,archivo);
			if(!feof(archivo))
				puts(linea);
		}
		printf("\n");
	
    while(cTecla != 27 ||cTecla!=79){
    	
    	printf("\n");
    	opcionesPagina();
		cTecla = getch();
		
    	   if(cTecla == 0)
        	   cTecla = getch();
        	   
      		else
      		
           		switch(cTecla){
            		case 80:{
            			n+=20;
                 		printf("\r\n Presiono pagina siguiente\n");
                 		archivo=fopen(nombre,"rt");
                 		for(i=0+n;i<10+n;i++){ //el programa mostrara de 10 en 10 lineas
							fgets(linea,80,archivo);
							if(!feof(archivo))
								puts(linea);
						}
						printf("\n");
						break;
					}

            case 72:{
            	h+=20;
                printf("\r\n Presiono pagina anterior\n");
                archivo=fopen(nombre,"rt");
                if(n==0)
                 	printf("ERROR: Estamos en la primera pagina\n");
                else{
                	for(i=0+n-h;i<10+n-h;i++){ //el programa mostrara de 10 en 10 lineas
					fgets(linea,80,archivo);
					if(!feof(archivo))
						puts(linea);
					}
				}
				printf("\n");
				break;
			}

            case 79:
                 printf("\r\n Presiono FIN\n");
            break;

            case 71:
                 printf("\r\n Presiono HOME\n");
            break;
            }   // switch
    }  // bucle
    	fclose(archivo);
    	return 0;
}

void opcionesPagina(){
void opcionesPagina(){
   	printf("================================================================================================================\n");
	printf("Continuar(Flecha Abajo)  |  Regresar(Flecha Arriba)  |  Volver al inicio(HOME)  |  Ir al final(FIN)  |  Salir(E)  ");	
}//fin funcion opcionesPagina
