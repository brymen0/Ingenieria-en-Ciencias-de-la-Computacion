Algoritmo determinarRaicesDeUnaEcuacionDeSegundoGrado
	//Calculara las raices de las ecuacion de segundo grado de la forma Ax^2+Bx+C=0 en numeros reales o complejos
	
	Definir A Como Real
	Definir B Como Real
	Definir C Como Real
	Definir x1 Como Real
	Definir x2 Como Real
	Definir discriminante como Real
	Definir parteReal Como Real
	Definir parteImaginaria Como Real
	
	Escribir "Sea la ecuacion de segundo grado de la forma Ax^2+Bx+C=0"
	Escribir "Introduzca el valor de A"
	Leer A
	Escribir "Introduzca el valor de B"
	Leer B	
	Escribir "Introduzca el valor de C"
	Leer C
	
	discriminante=(B*B-4*A*C)
	
	Si discriminante>0 entonces
		x1=(-B+raiz(discriminante))/(2*A)
		x2=(-B-raiz(discriminante))/(2*A)
		Escribir "Las raices son x1=",x1 " y x2=",x2
	Sino
		parteReal=-B/(2*A)
		parteImaginaria=(raiz(-1*(discriminante)))/(2*A)
		Escribir "Las raices son x1=",parteReal "+",parteImaginaria "i y x2=",parteReal "-",parteImaginaria "i"
		
	FinSi
FinAlgoritmo
