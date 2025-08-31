Algoritmo areaDeUnCirculo
	
	Definir radio como real ;
	
	Escribir "Ingrese el valor del radio del circulo en centimetros" ;
	Leer radio ;
	
	Si radio<0 Entonces ;
		Escribir "El radio ingresado es incorrecto" ;
	Sino ;
		area=PI*radio^2 ;
		Escribir "El area del circulo es: ", area " cm^2";
	FinSi
FinAlgoritmo
