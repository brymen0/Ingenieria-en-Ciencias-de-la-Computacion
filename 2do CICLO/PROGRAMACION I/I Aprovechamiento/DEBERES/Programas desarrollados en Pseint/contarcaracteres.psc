Algoritmo sin_titulo
	Definir n Como Entero
	Definir contdig Como Entero
	Definir res Como Real
	
	Escribir "Ingrese un numero"
	Leer n
	
	contdig=0
	Mientras n<>0 Hacer
		n=trunc(n/10)
		contdig=contdig+1
	FinMientras

	Escribir "El numero de digitos es: ",contdig
FinAlgoritmo
