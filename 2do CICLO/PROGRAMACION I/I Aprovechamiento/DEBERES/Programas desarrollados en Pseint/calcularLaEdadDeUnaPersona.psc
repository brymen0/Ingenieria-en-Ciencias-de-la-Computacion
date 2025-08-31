Algoritmo calcularLaEdadDeUnaPersona
	//Dada la fecha de nacimiento, calcula la edad de la persona con respecto a una fecha posterior
	
	Definir dianacimiento como Entero
	Definir mesnacimiento como Entero
	Definir añonacimiento como Entero
	Definir diaposterior como Entero
	Definir mesposterior como Entero
	Definir añoposterior como Entero
	Definir diaposterior2 como Entero
	Definir mesposterior2 como Entero
	Definir mesposterior3 como Entero
	Definir añoposterior2 como Entero
	Definir añototal Como Entero
	Definir diatotal como Entero
	Definir mestotal como Entero
	
	Escribir "Ingrese el dia de nacimiento"
	Leer dianacimiento
	
	Escribir "Ingrese el mes de nacimiento"
	Leer mesnacimiento
	
	Escribir "Ingrese el año de nacimiento"
	Leer añonacimiento
	
	Escribir "Ingrese el dia de la fecha posterior"
	Leer diaposterior
	
	Escribir "Ingrese el mes de la fecha posterior"
	Leer mesposterior
	
	Escribir "Ingrese el año de la fecha posterior"
	Leer añoposterior
	
	Si diaposterior>=dianacimiento y mesposterior>=mesnacimiento Entonces
		añototal=añoposterior-añonacimiento
		mestotal=mesposterior-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",añototal " años,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior<dianacimiento y mesposterior>mesnacimiento Entonces
		diaposterior2=diaposterior+30 
		mesposterior2=mesposterior-1
		añototal=añoposterior-añonacimiento
		mestotal=mesposterior2-mesnacimiento
		diatotal=diaposterior2-dianacimiento
		Escribir "Su edad es ",añototal " años,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior>dianacimiento y mesposterior<mesnacimiento Entonces
		mesposterior3=mesporterior+12
		añoposterior2=añoposterior-1
		
		añototal=añoposterior2-añonacimiento
		mestotal=mesposterior3-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",añototal " años,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si diaposterior<dianacimiento y mesposterior<=mesnacimiento Entonces
		diaposterior=diaposterior+30
		mesposterior=mesposterior+11
		añoposterior=añoposterior-1
		
		añototal=añoposterior-añonacimiento
		mestotal=mesposterior-mesnacimiento
		diatotal=diaposterior-dianacimiento
		Escribir "Su edad es ",añototal " años,",mestotal " meses,",diatotal " dias"
	FinSi
	
	Si añoposterior<añonacimiento Entonces
		Escribir "Los datos ingresados son incorrectos"
	FinSi
FinAlgoritmo
