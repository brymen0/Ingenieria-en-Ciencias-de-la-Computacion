#include <stdio.h>

int ingresarDatos (char mensaje[30]);
int validar(int valor,int ano,int mes,int dia);

int main () { 
	
	int anoNacido, mesNacido, diaNacido; //fecha de nacimiento
	int mesActual, diaActual; //fecha actuale  (el año actual se toma como 2022)
	int diaValido, mesValido, anoValido; //variables para validar
	int anos, meses, dias; //calculo de la edad en años meses y dias
	int edad [3]; //vector para la edad
	int i=1; //contador de bucle
	
	printf ("...........................................................\n");
	printf ("       PROGRAMA QUE CALCULA LA EDAD DE UNA PERSONA   \n");
	printf ("...........................................................\n");
	printf ("AUTOR: BRYAN MENDOZA \n\n");	
	
	printf("FECHA NACIMIENTO\n");
	do { //pide el mes de nacimiento y valida 
		mesNacido=ingresoDatos("Ingrese el mes de nacimiento: \n");
		mesValido=validar(mesNacido,0,-1,0);
		if (mesValido==1)
			printf ("ERROR: El mes ingresado es incorrecto. \n");
	} while(mesValido==1);
	
	do { //pide el dia de nacimiento y valida 
		diaNacido=ingresoDatos("Ingrese el dia de nacimiento: \n");
		diaValido=validar(diaNacido,0,mesNacido,-1);
		if (diaValido==1)
			printf ("ERROR: El dia ingresado es incorrecto. \n");
	} while (diaValido==1);
	
	do { //pide el año de naicimiento y valida
		anoNacido=ingresoDatos("Ingrese el año de nacimiento: \n");
		anoValido=validar(anoNacido,-1,0,0);
		if (anoValido==1)
			printf ("ERROR: El año ingresado es incorrecto. \n");
	} while(anoValido==1);
	
	printf("\nFECHA ACTUAL\n");
	do { //pide el dia actual y valida
		diaActual=ingresoDatos("Ingrese el dia actual: \n");
		diaValido=validar(diaActual,0,mesActual,-1);
		if (diaValido==1)
			printf ("ERROR: El dia ingresado es incorrecto. \n");
	} while (diaValido==1);
	
	do { //pide el mes actual y valida 
		mesActual=ingresoDatos("Ingrese el mes actual: \n");
		mesValido=validar(mesActual,0,-1,0);
		if (mesValido==1)
			printf ("ERROR: El mes ingresado es incorrecto. \n");
	} while(mesValido==1);
	
	if (mesActual<mesNacido) //condicion para calcular los años
		anos=((2022-anoNacido)-1);
	else
		anos=(2022-anoNacido);
		
	edad[i]=anos;
	i++;
	
	if ((mesActual>mesNacido)&&(diaActual>diaNacido)) { //condiciones para calcular los meses y los dias
		meses=((mesActual-mesNacido));
		dias=(diaActual-diaNacido);
	}
	else {
		if ((mesActual>mesNacido)&&(diaActual<diaNacido)) {
			meses=((mesActual-mesNacido)-1);	
			dias=(30-(diaNacido-diaActual));
		}
		else {
			if ((mesActual<mesNacido)&&(diaActual>diaNacido)) {
				meses=(12-(mesNacido-mesActual));
				dias=(diaActual-diaNacido);
			}
			else {
				if ((mesActual<mesNacido)&&(diaActual<diaNacido)) {
					meses=((11-(mesNacido-mesActual)));
					dias=(30-(diaNacido-diaActual));
				}
			}
		}
	}
	edad[i]=meses;
	i++;
	edad[i]=dias;
	
	printf("Su edad es:\n");
	printf("%d años, %d meses y %d dias.\n",edad[1],edad[2],edad[3]);
	
	return 0;
} //fin funcion principal

int ingresoDatos (char mensaje[30]) { //funcion que ingresa los datos
	int valor;
	printf ("%s", mensaje);
	scanf ("%d", &valor);
	return valor;
}//fin de la funcion ingresoDatos

int validar(int fecha, int ano, int mes, int dia) { //funcion que valida las fechas 
	int esCorrecto;
	if (ano==-1) { //condicion para validar el año ingresado
		if ((fecha>=0)&&(fecha<=2022))
			esCorrecto=0;
		else 
			esCorrecto=1;
	}
	else{ // condicion para validar el mes ingresado
		if (mes==-1) {
			if ((fecha>=1) && (fecha<=12)) 
				esCorrecto=0;
			else 
				esCorrecto=1;
		}
		else { 
			if (dia==-1) {
				switch (mes) { // condiciones para validar el dia ingresado segun el mes
					case 1: 
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:
						if ((fecha>=1) && (fecha<=31)) 
							esCorrecto=0;
						else 
							esCorrecto=1;
						break;
					case 2:
						if ((fecha>=1) && (fecha<=28))
							esCorrecto=0;
						else 
							esCorrecto=1;	
						break;
					case 4:
					case 6:
					case 9:
					case 11:
						if ((fecha>=1) && (fecha<=30))
							esCorrecto=0;
						else 
							esCorrecto=1;	
						break;		
				}
			}
		}
	}
	return esCorrecto;
} //fin de la funcion validar
