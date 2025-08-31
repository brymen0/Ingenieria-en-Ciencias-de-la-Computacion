#include<stdio.h>
#include<math.h>

int main() 
{
	float a; //valor de a
	float b; //valor de b
	float c; //valor de c
	float discriminante; //discriminante de la ecuacion
	float parteimaginaria; //parte imaginaria si el determinante es negativo
	float partereal; //parte real de la respuesta
	float x1; //primera raiz
	float x2; //segunda raiz
	
	printf("..........................................................................................\n");
	printf("         Programa que calcula las raices de una ecuacion de segundo grado\n");
	printf("..........................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	printf("Sea la ecuacion de segundo grado de la forma Ax^2+Bx+C=0\n");
	printf("Introduzca el valor de A\n");
	scanf("%f",&a);
	printf("Introduzca el valor de B\n");
	scanf("%f",&b);
	printf("Introduzca el valor de C\n");
	scanf("%f",&c);
	
	discriminante = (b*b-4*a*c);
	
	if(a==0) //condicion si A es igual a 0
	{
		printf("La ecuacion no es cuadratica \n");
		if (b!=0)  
		printf("La raiz es: %f",(float)-c/b);
	}
	else
	{
		if (discriminante>0) 
		{
		x1 = (-b+sqrtf(discriminante))/(2*a);
		x2 = (-b-sqrtf(discriminante))/(2*a);
		printf("Las raices son x1=%f y x2=%f\n",x1,x2);
		} 
		else 
		{
		partereal = -b/(2*a);
		parteimaginaria = (sqrtf(-1*(discriminante)))/(2*a);
		printf("Las raices son x1=%f+%fi y x2=%f-%fi\n",partereal,parteimaginaria,partereal,parteimaginaria);
		}
	}
	return 0;
}

