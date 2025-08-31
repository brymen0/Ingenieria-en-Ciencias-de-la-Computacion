Algoritmo ordernarDosNumeros
	//Ordena dos numeros de menor a mayor
	
	Definir valor1 Como Real ;
	Definir valor2 Como Real ;
	
	Escribir sin saltar "Ingrese el primer numero" ;
	Leer valor1 ;
	
	Escribir sin saltar "Ingrese el segundo numero" ;
	Leer valor2 ;
	
	Si valor1<valor2 Entonces ;
		Escribir "El orden de mayor a menor de los numeros es de: ",valor1 ", " valor2 ;
	SiNo ;
		Si valor1>valor2 Entonces ;
			Escribir "El orden de mayor a menor de los numeros es de: ",valor2 ", " valor1 ;
		Sino ;
			Escribir "Los numeros son iguales" ;
		FinSi ;
	FinSi ;
FinAlgoritmo
