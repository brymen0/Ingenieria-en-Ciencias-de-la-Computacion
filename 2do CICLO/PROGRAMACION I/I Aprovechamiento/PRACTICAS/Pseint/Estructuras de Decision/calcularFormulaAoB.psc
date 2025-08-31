Algoritmo calcularFormulaAoB
	
	Definir a,b,c,d Como Entero ;
	Definir x como real ;
	
	Escribir "Ingrese cuatro numeros enteros" ;
	Leer a,b,c,d ;
	
	Si d<>0 Entonces 
		x=(a+(b/c))/((a/b)+c) ;
		Escribir "El valor de x es de: ",x ;
	Sino
		x=(a+((a+b)/(c+d)))/(a+(a/b)) ;
		Escribir "El valor de x es de: ",x ;
	FinSi
FinAlgoritmo
