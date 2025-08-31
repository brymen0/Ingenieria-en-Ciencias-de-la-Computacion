Algoritmo factorialDeUnNumero
	//Algortimo que calcula el factorial de un numero entre 1 y 40
	
	Definir numingresado Como Entero //Numero ingresado por el usuario
	Definir factorial Como real //Acumulador de las multiplicaciones de 1 hasta el numero ingresdo, para calcular factorial del numero
	Definir i como entero //Contador de los numeros que se deberan multiplicar para calcular el factorial
	
	Escribir "==========================================================="
	Escribir "       Algoritmo que calcula el factorial de un numero"
	Escribir "==========================================================="
	Escribir "AUTOR: BRYAN MENDOZA"
	Escribir ""
	
	factorial=1
	Repetir //Realiza las acciones de calcular el factorial si se ingresa bien el numero, sino vuelve a pedir el numero
		Escribir "Ingrese un numero entre 1 y 40"
		Leer numingresado
		Si numingresado>=1 y numingresado<=40 Entonces //Valida el numero
			Para i=1 hasta numingresado con paso 1 //Calcula los numeros a multiplicar para calcular el factorial
				factorial=factorial*i
			FinPara
		Sino 
			Escribir "ERROR: EL numero ingresado esta fuera del rango aceptado"
		FinSi
	Hasta Que numingresado>=1 y numingresado<=40
	
	Escribir "El factorial de numero ",numingresado " es: ",factorial

FinAlgoritmo
