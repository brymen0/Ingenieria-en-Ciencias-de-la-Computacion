#include<stdio.h>
#include<math.h>

int main() 
{
	
	int numlados; //numero de lados de la figura
	int bandera; //validador
	int longlado; //lontitud de los lados de la figura
	int opcion; //opcion seleccionada por el usuario
	int perimetro; //valor del perimetro
	float area; //valor de la area
	float pi; //numero pi
	int i; //contador del bucle del perimetro
	float radio; //valor del radio
	
	printf("=======================================================================================\n");
	printf("    Algoritmo que mediante un menu calcula el perimetro y area de una figura regular\n");
	printf("=======================================================================================\n");
	printf("AUTOR: BRYAN MENDOZA\n");
	printf("\n");
	bandera = -1; //inicializo el validador

	do { //repite el menu hasta que el usuario quiera salir
		printf("                    M E N U   D E   O P C I O N E S\n");
		printf("\n");
		printf("1. Ingresar numero de lados\n");
		printf("2. Calcular el perimetro\n");
		printf("3. Calcular el area\n");
		printf("4. Salir del programa\n");
		printf("Ingrese una opcion: \n");
		scanf("%d",&opcion);

		switch (opcion) { //realiza la opcion requerida por el usuario
		case 1:
			do { //valida el numero de lados
				printf("Ingrese el numero de lados:\n");
				scanf("%i",&numlados);
				if (numlados<1 || numlados>20) {
					printf("ERROR: El numero de lados debe estar entre 1 y 20\n");
				}
			} while (!(numlados>=1 && numlados<=20));

			do { //valida la longitud de los lados
				printf("Ingrese la longitud del lado de la figura:\n");
				scanf("%d",&longlado);
				if (longlado<=0) 
					printf("ERROR: El lado debe ser positivo\n");
			} while (longlado<=0);
			bandera = 1; //valida cuando ya se ingresaron los datos iniciales
			break;
			
		case 2: //calcula el perimetro
			if (bandera==1) //condicion para calcular el perimetro
			{
				for (i=1;i<=numlados;i+=1) //bucle que calcula el perimetro
					perimetro = perimetro+longlado;
				printf("El perimetro de la figura es: %d unidades\n",perimetro);
			} 
			else 
				printf("ERROR: Primero debe ingresar el numero de lados y su longitud\n");
			break;
			
		case 3: //calcula el area
			if (bandera==1) //condicion para calcula el area
			{
				if (numlados==1) 
				{
					printf("Ingrese el radio\n");
					scanf("%f",&radio);
					area = M_PI*pow(radio,2);
					printf("El area de la figura es: %f unidades cuadradas\n",area);
				} 
				else 
				{
					if (numlados==2) 
						printf("No se puede calcular el area\n");
					else 
					{
						if (numlados==3) 
						{
							area = (sqrtf(3)*pow(longlado,2))/4;
							printf("El area de la figura es: %f unidades cuadradas\n",area);
						} 
						else 
						{
							if (numlados==4) 
							{
								area = pow(longlado,2);
								printf("El area de la figura es: %f unidades cuadradas\n",area);
							} 
							else 
							{
								area = (numlados*pow(longlado,2))/(4*tan(M_PI/numlados));
								printf("El area de la figura es: %f unidades cuadradas\n",area);
							}
						}
					}
				}
			} 
			else 
				printf("ERROR: Primero debe ingresar el numero de lados y su longitud\n");
			break;
			
		case 4: //salir del programa
			printf("Gracias por usar mi programa\n");
			break;
		
		default:
			printf("Opcion no valida");
		}
	} while (opcion!=4);
	return 0;
}

