Algoritmo determinarMultiplo
	
	Definir numero1,numero2 Como Entero ;
	
	Escribir "Ingrese dos numeros enteros" ;
	Leer numero1,numero2 ;
	
	Si (numero1 MOD numero2)<>0 y (numero2 MOD numero1)<>0 Entonces
		Escribir "Ningun numero es multiplo del otro" ;
	Sino
		Si (numero1 MOD numero2)=0 Entonces
			Escribir "El numero ",numero1 " es multiplo del numero ",numero2 ;
		SiNo
			Si (numero2 MOD numero1)=0 Entonces
				Escribir "El numero ",numero2 " es multiplo del numero ",numero1 ;
			Finsi
		FinSi
	FinSi
	
FinAlgoritmo
