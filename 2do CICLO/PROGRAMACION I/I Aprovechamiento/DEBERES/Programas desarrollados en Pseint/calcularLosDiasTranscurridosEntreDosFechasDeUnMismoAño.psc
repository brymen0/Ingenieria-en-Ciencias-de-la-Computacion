Algoritmo DadaUnaFechaCalcularLosDiasTranscurridosEnUnMismoAño
	// Calcula los dias totales transcurridos entre dos fechas de un mismo año

	Definir mesinicial Como Entero
	Definir diainicial como Entero
	Definir mesporterior Como Entero
	Definir diaposterior como Entero
	Definir diastotales como Entero
	//No se pide los años de la fecha, ya que el programa es para calcular los dias transcurridos entre dos fechas del mismo año
	
	Escribir "Ingrese el dia de la fecha inicial"
	Leer diainicial
	
	Escribir "Ingrese el mes de la fecha inicial"
	Leer mesinicial
	
	Escribir "Ingrese el dia de la fecha posterior"
	Leer diaposterior
	
	Escribir "Ingrese el mes de la fecha posterior"
	Leer mesposterior
	
	Si diaposterior>=diainicial y mesposterior>=mesinicial Entonces
		mestotal=mesposterior-mesinicial
		diatotal=diaposterior-diainicial
		
		diastotales=mestotal*30+diatotal
		Escribir "Los dias trancurridos son ",diastotales
		
	SiNo
		Si diaposterior<diainicial y mesposterior>mesinicial Entonces
		diaposterior=diaposterior+30
		mesposterior=mesposterior-1
		
		mestotal=mesposterior-mesinicial
		diatotal=diaposterior-diainicial
		
		diastotales=mestotal*30+diatotal
		Escribir "Los dias trancurridos son ",diastotales
		
		SiNo
		Escribir "Los datos ingresados son incorrectos"
		FinSi	
	FinSi
FinAlgoritmo
