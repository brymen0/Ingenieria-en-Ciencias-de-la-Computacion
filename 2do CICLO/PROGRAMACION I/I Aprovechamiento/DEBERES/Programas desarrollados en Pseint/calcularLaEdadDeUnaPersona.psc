Algoritmo calcularLaEdadDeUnaPersona
	//Dada la fecha de nacimiento, calcula la edad de la persona con respecto a una fecha posterior
	
	Definir dianacimiento como Entero
	Definir mesnacimiento como Entero
	Definir a�onacimiento como Entero
	Definir diaposterior como Entero
	Definir mesposterior como Entero
	Definir a�oposterior como Entero
	Definir diaposterior2 como Entero
	Definir mesposterior2 como Entero
	Definir mesposterior3 como Entero
	Definir a�oposterior2 como Entero
	Definir a�ototal Como Entero
	Definir diatotal como Entero
	Definir mestotal como Entero
	
	Escribir "Ingrese el dia de nacimiento"
	Leer dianacimiento
	
	Escribir "Ingrese el mes de nacimiento"
	Leer mesnacimiento
	
	Escribir "Ingrese el a�o de nacimiento"
	Leer a�onacimiento
	
	Escribir "Ingrese el dia de la fecha posterior"
	Leer diaposterior
	
	Escribir "Ingrese el mes de la fecha posterior"
	Leer mesposterior
	
	Escribir "Ingrese el a�o de la fecha posterior"
	Leer a�oposterior
	
	Si diaposterior>=dianacimiento y mesposterior>=mesnacimiento Entonces
		a�ototal=a�oposterior-a�onacimiento
		mestotal=mesposterior-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",a�ototal " a�os,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior<dianacimiento y mesposterior>mesnacimiento Entonces
		diaposterior2=diaposterior+30 
		mesposterior2=mesposterior-1
		a�ototal=a�oposterior-a�onacimiento
		mestotal=mesposterior2-mesnacimiento
		diatotal=diaposterior2-dianacimiento
		Escribir "Su edad es ",a�ototal " a�os,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior>dianacimiento y mesposterior<mesnacimiento Entonces
		mesposterior3=mesporterior+12
		a�oposterior2=a�oposterior-1
		
		a�ototal=a�oposterior2-a�onacimiento
		mestotal=mesposterior3-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",a�ototal " a�os,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior<dianacimiento y mesposterior<=mesnacimiento Entonces
		diaposterior=diaposterior+30
		mesposterior=mesposterior+11
		a�oposterior=a�oposterior-1
		
		a�ototal=a�oposterior-a�onacimiento
		mestotal=mesposterior-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",a�ototal " a�os,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si a�oposterior<a�onacimiento Entonces
		Escribir "Los datos ingresados son incorrectos"
	FinSi
FinAlgoritmo
