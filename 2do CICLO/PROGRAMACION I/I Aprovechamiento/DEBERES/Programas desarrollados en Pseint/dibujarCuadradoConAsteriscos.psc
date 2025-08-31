Algoritmo dibujarCuadradoConAsteriscos
	//Algortimo que dibuja un cuadrado con n asteriscos por lado, el valor de n lo decide el usuario y debe estar entre 3 y 11
	
	Definir numingresado Como Entero //Numero ingresado para saber cuantos asteriscos tendra cada lado
	Definir bandera Como Entero //Condicion para pasar al paso donde se realiza el cuadrado
	Definir filas Como Entero //Filas de asteriscos para hacer el cuadrado
	Definir columnas como entero //Columnas de asteriscos para hacer el cuadrado
	
	Escribir "========================================================="
	Escribir "   Algoritmo que dibuja un cuadrado con n asteriscos"
	Escribir "========================================================="
	Escribir "AUTOR: BRYAN MENDOZA"
	Escribir ""
	
	bandera=0
	Repetir //Valida el numero que debe estar entre 3 y 11
		Escribir "Ingrese un numero mayor a 3 y menor a 11"
		Leer numingresado
		Si numingresado<=3 o numingresado>=11 Entonces
			Escribir "ERROR:El numero ingresado esta fuera del rango permitido"
		FinSi
	Hasta Que numingresado<11 y numingresado>3
	bandera=1
	
	Si bandera=1 Entonces 
		Para filas=1 Hasta numingresado Con Paso 1 Hacer //Bucle para escribir las filas de asteriscos
			Para columnas=1 Hasta numingresado con paso 1 Hacer //Bucle para escribir las columnas de asteriscos
				Escribir sin saltar " " //Para que los asteriscos en las filas no esten juntos
				Si filas=1 o filas=numingresado o columnas=1 o columnas=numingresado Entonces //Condiciones que se deben cumplir para que se escriba un asterisco
					Escribir sin saltar "*"
				Sino 
					Escribir sin saltar " " 
				FinSi
			FinPara
			Escribir " " //Para que cuando se acabe de escribir una fila, se salte a la siguiente en la que debe escribir
		Fin Para
	FinSi
Finalgoritmo
