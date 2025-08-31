#include<stdio.h>

int main() 
{
	int dianacimiento; //dia de nacimiento del usuario
	int mesnacimiento; //mes de nacimiento del usuario
	int anonacimiento; //año de nacimiento del usuario
	int diaposterior; //dia hasta donde quiere calcular su edad
	int mesposterior; //mes hasta donde quiere calcular su edad
	int anoposterior; //año hasta donde quiere calcular su edad
	int diaposterior2;	//dia posterior si el dia posterior ingresado es menor al dia de nacimiento
	int mesposterior2; //mes posterior si el mes posterior ingresado es mayor al mes de nacimiento
	int mesposterior3; //mes posterior si el mes posterior ingresado es menor al mes de nacimiento
	int anoposterior2; //año posterior si el mes posterior ingresado es menor al mes de nacimiento
	int diatotal; //dias totales de la edad calculada
	int mestotal; //meses totales de la edad calculada
	int anototal; //años totales de la persona
	
	printf("..........................................................................................\n");
	printf("                 Programa que calcula la edad de una persona \n");
	printf("..........................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	printf("Ingrese el dia de nacimiento\n");
	scanf("%d",&dianacimiento);
	printf("Ingrese el mes de nacimiento\n");
	scanf("%d",&mesnacimiento);
	printf("Ingrese el año de nacimiento\n");
	scanf("%d",&anonacimiento);
	printf("Ingrese el dia de la fecha posterior\n");
	scanf("%d",&diaposterior);
	printf("Ingrese el mes de la fecha posterior\n");
	scanf("%d",&mesposterior);
	printf("Ingrese el año de la fecha posterior\n");
	scanf("%d",&anoposterior);
	
	if (diaposterior>=dianacimiento && mesposterior>=mesnacimiento) //condiciones a realizar si el mes posterior es mayor o igual a dia de nacimeinto y el mes posterior mayor o igual al mes de nacimiento
	{
		anototal = anoposterior-anonacimiento;
		mestotal = mesposterior-mesnacimiento;
		diatotal = diaposterior-dianacimiento;
		printf("Su edad es %i años,%i meses,%i dias\n",anototal,mestotal,diatotal);
	}
	
	if (diaposterior<dianacimiento && mesposterior>mesnacimiento) //condiciones a realizar si el dia posterior es menor al dia de nacimiento y si es el posterior es mayor al mes de nacimiento
	{
		diaposterior2 = diaposterior+30;
		mesposterior2 = mesposterior-1;
		anototal = anoposterior-anonacimiento;
		mestotal = mesposterior2-mesnacimiento;
		diatotal = diaposterior2-dianacimiento;
		printf("Su edad es %i años,%i meses,%i dias\n",anototal,mestotal,diatotal);
	}
	
	if (diaposterior>dianacimiento && mesposterior<mesnacimiento) //condiciones a realizar si el dia posterior es mayor al dia de nacimiento y el mes posterior es menor al mes de nacimiento
	{ 
		mesposterior3 = mesposterior+12;
		anoposterior2 = anoposterior-1;
		anototal = anoposterior2-anonacimiento;
		mestotal = mesposterior3-mesnacimiento;
		diatotal = diaposterior-dianacimiento;
		printf("Su edad es %i años,%i meses,%i dias\n",anototal,mestotal,diatotal);
	}
	
	if (diaposterior<dianacimiento && mesposterior<=mesnacimiento) //condiciones a realizar si el dia posterior es menor al dia de nacimiento y el mes posterior menor o gual al mes de nacimiento
	{
		diaposterior = diaposterior+30;
		mesposterior = mesposterior+11;
		anoposterior = anoposterior-1;
		anototal = anoposterior-anonacimiento;
		mestotal = mesposterior-mesnacimiento;
		diatotal = diaposterior-dianacimiento;
		printf("Su edad es %i años,%i meses,%i dias\n",anototal,mestotal,diatotal);
	}
	if (anoposterior<anonacimiento) //condicion si el año posterior es menor al año de nacimiento
		printf("Los datos ingresados son incorrectos\n");
	
	return 0;
}

