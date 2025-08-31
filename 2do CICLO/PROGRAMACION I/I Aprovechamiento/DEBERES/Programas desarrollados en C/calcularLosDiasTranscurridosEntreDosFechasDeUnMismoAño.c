#include<stdio.h>

int main() 
{
	int diainicial; //dia de la fecha previa
	int diaposterior; //dia de la fecha posterior
	int diastotales; //dias totales que transcurrieron
	int diatotal; //calcula la resta de los dias de la fecha posterior con la inicial
	int mesinicial; //mes de la fecha previa
	int mesposterior; //mes de la fecha posterior
	int mestotal; //meses totales transcurridos

	printf("..........................................................................................\n");
	printf("     Programa que calcula los dias transcurridos entre dos fechas de un mismo año\n");
	printf("..........................................................................................\n");
	printf("\n");
	printf("AUTOR: Bryan Mendoza\n");
	printf("\n");
	
	printf("Ingrese el dia de la fecha inicial\n");
	scanf("%d",&diainicial);
	printf("Ingrese el mes de la fecha inicial\n");
	scanf("%d",&mesinicial);
	printf("Ingrese el dia de la fecha posterior\n");
	scanf("%d",&diaposterior);
	printf("Ingrese el mes de la fecha posterior\n");
	scanf("%d",&mesposterior);
	
	if (diaposterior>=diainicial && mesposterior>=mesinicial) //condiciones si el dia posterior es mayor o igual al dia inicial y el mes posterior es mayor o igual al mes inicial
	{
		mestotal = mesposterior-mesinicial; //calcula los meses transcurridos
		diatotal = diaposterior-diainicial; //dias transcurridos entre las fechas
		diastotales = mestotal*30+diatotal; //dias totales transcurridos
		printf("Los dias trancurridos son %i\n",diastotales);
	} else {
		if (diaposterior<diainicial && mesposterior>mesinicial) //condiciones si el dia posterior es menos al dia inicial y el mes posterior mayor al mes inicial
		{
			diaposterior = diaposterior+30; //suma a los dias un mes
			mesposterior = mesposterior-1; //resta al mes posterior 1
			mestotal = mesposterior-mesinicial; //cacula los meses totales
			diatotal = diaposterior-diainicial; //dias trancurridos entre las fechas
			diastotales = mestotal*30+diatotal; //dias totales transcurridos
			printf("Los dias trancurridos son %i\n",diastotales);
		} 
		else 
			printf("Los datos ingresados son incorrectos\n");
	}
	return 0;
}

