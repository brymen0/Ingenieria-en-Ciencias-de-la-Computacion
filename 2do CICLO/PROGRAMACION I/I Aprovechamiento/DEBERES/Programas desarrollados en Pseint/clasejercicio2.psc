Algoritmo clasejercicio2
	
	Definir N Como Entero ;
	Definir sumadivisores,numerodivisores,perfecto como entero ;
	
	Escribir "Ingrese un numero entre 0 y 9000" ;
	Leer N ;
	
	numerodivisores=0

	Si N<=0 O N>=900 Entonces 
		Escribir "El numero ingresado es incorrecto" ;
	Sino ;
		Para i=1 Hasta N con paso 1 Hacer
			Si ((N MOD i)=0) Entonces
				Escribir "El numero es divisible para ",i ;
				numerodivisores=numerodivisores+1 ;
				perfecto=perfecto+(N/i)
			FinSi 
		FinPara 
	FinSi 
	
	Si numerodivisores=2 Entonces
	Escribir "Es un numero primo" ;
FinSi

Si perfecto-N==N Entonces
	Escribir "Es un numero perfecto" ;
FinSi

FinAlgoritmo
