#include<stdio.h>
#include<math.h>

int main() 
{
	float area;
	int ladoa;
	int ladob;
	int ladoc;
	int perimetro;
	float semiperimetro;

	printf("..........................................................................................\n");
	printf("     Programa que determina si forma un triangulo, ingresando el valor de los lados\n");
	printf("..........................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	printf("Ingrese el primer lado:\n");
	scanf("%d",&ladoa);
	printf("Ingrese el segundo lado\n");
	scanf("%d",&ladob);
	printf("Ingrese el tercer lado:\n");
	scanf("%d",&ladoc);
	
	if ((ladoa+ladob>ladoc) || (ladoa+ladoc>ladob) || (ladob+ladoc>ladoa)) 
	{
		printf("Si forman un triangulo\n");
		if ((ladoa==ladob) && (ladob==ladoc) && (ladoa==ladob)) {
			printf("Forman un triangulo equilatero\n");
		} 
		else {
			if ((ladoa==ladob) || (ladoa==ladoc) || (ladob==ladoc)) {
				printf("Forman un triangulo isosceles\n");
			} 
			else 
				printf("Forman un tringulo escaleno\n");
		}
		perimetro = ladoa+ladob+ladoc;
		semiperimetro = perimetro/2;
		area = (sqrtf(semiperimetro*(semiperimetro-ladoa)*(semiperimetro-ladob)*(semiperimetro-ladoc)));
		printf("El perimetro es: %i\n",perimetro);
		printf("El area es: %f\n",area);
	} 
	else 
		printf("Los numeros ingresados no forman un triangulo\n");
	
	return 0;
}

