Algoritmo calculaCostoDeLlamada
	
	Definir minutos Como Entero ;
	Definir costo1,costo2 Como Real ;
	
	Escribir "Ingrese la duracion de su llamada minutos" ;
	Leer minutos
	
	Si minutos<0 Entonces
		Escribir "La duracion ingresada es incorrecta" ;
	SiNo
		Si minutos=0 Entonces
			Escribir "No debe pagar nada";
		Sino
			Si minutos<=5 Entonces
				costo1=3.5 ;
				Escribir "El costo a pagar por su llamada telefonica es de: ",costo1 " dolares." ;
			Sino 
				costo2=3.5+((minutos-5)*1.2)
				Escribir "El costo a pagar por su llamada telefonica es de: ",costo2 " dolares." ;
			Finsi
		FinSi
	FinSi
	
FinAlgoritmo
