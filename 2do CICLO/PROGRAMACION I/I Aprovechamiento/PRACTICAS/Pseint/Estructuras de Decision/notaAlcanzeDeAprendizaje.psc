Algoritmo notaAlcanzeDeAprendizaje
	
	Definir nota Como Real ;
	
	Escribir "Ingrese su nota del examen quimestral sobre 10" ;
	Leer nota ;
	
	Si nota<0 o nota>10 Entonces ;
		Escribir "Su nota ingresada es incorrecta" ;
	Sino 
		Si nota<=1.4 Entonces ;
			Escribir "NO ALCANZA EL APRENDIZAJE" ;
		SiNo
			Escribir "Su nota es: ",nota ;
		FinSi
	FinSi

FinAlgoritmo
