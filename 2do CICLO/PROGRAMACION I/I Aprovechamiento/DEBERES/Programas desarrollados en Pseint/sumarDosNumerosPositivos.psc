Algoritmo sumarDosNumerosPositivos
	//Sumara dos numeros reales postivos, caso contrario no ejecutara ningun calculo y mostrara el mensaje "Los numeros introducidos son incorrectos"
	
	Definir primerSumando Como Real 
	Definir segundoSumando Como Real
	Definir resultado Como Real 
	
	Escribir "Introduzca el primer numero" 
	Leer primerSumando 
	
	Escribir "Introduzca el segundo numero" 
	Leer segundoSumando 
	
	Si primerSumando>=0 y segundoSumando>=0 Entonces 
		resultado=primerSumando+segundoSumando
		Escribir "El resultado es: ",resultado
	SiNo
		Escribir "Los numeros introducidos son incorrectos"
	FinSi
	
FinAlgoritmo


