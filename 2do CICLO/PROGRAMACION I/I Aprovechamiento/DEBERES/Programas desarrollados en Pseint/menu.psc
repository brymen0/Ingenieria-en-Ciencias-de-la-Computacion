Algoritmo menuOpciones
	
	Definir numDivisores Como Entero ; 
	Definir num Como Entero ;
	Definir bandera Como Entero ;
	Definir opcion Como Entero ;
	Definir divisor Como Entero ;
	Definir suma Como Entero ;
	Definir contador Como Entero ;

	bandera=-1 ;
	
	Repetir
		Escribir "                    M E N Ú   D E   O P C I O N E S" ;
		Escribir ""
		Escribir "1. Ingresar un numero" ;
		Escribir "2. Calcula los divisores" ;
		Escribir "3. Salir del algoritmo" ;
		Escribir sin saltar "Ingrese una opcion" ;
		Leer opcion
	
		Segun opcion Hacer
			1: //ingreso de numero
				Repetir
					Escribir sin saltar "Ingrese un numero entre 1 y 100" ;
					leer num ;
					Si num<1 o num>100 Entonces
						Escribir "ERROR: El numero debe estra entre 1 y 100" ;
					FinSi
				Hasta Que num>=1 y num<=100
				bandera=1
			2: //Calculo los divisores
				Si bandera=1 Entonces
					numDivisores=0 ;
					Escribir "El valor ingresado es ", num ;
					suma=0 ;
					Para contador=1 hasta num con paso 1 Hacer
						Si (num MOD contador)=0 Entonces
							suma=suma+contador
							numDivisores=numDivisores+1
						FinSi
					FinPara
					
					Escribir "La suma de los divisores es: ",suma
					Si numDivisores=2 Entonces 
						Escribir "El numero ingresado ",num " es primo"
					FinSi
					Si suma-num=num Entonces 
						Escribir "El numero ingresado ",num " es perfecto"
					FinSi
				Sino 
					Escribir "Debe ingresar datos primero"
				FinSi
			3: //Salir del algortimo
				Escribir "Gracias"
		De Otro Modo:
			Escribir "Opcion ingresada no valida"
		FinSegun
	Hasta que opcion=3

FinAlgoritmo	
