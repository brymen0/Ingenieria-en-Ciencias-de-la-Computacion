Algoritmo respaldoDeInformacion
	
	Definir Cd Como Real ;
	Definir discoduro Como Real ;
	
	Escribir "Introduzca el tamaño de informacion que contiene el disco duro en GB";
	Leer discoduro ;
	
	Cd=discoduro/0.68 ;
	
	Si discoduro<0 Entonces ;
		Escribir "El dato ingresado es incorrecto" ;
	Sino ;
		Si Cd es entero Entonces
			Escribir "El numero de CDs necesarios para realizar la copia de seguridad de su disco duro es de: ",Cd ;
		SiNo
			Cd=trunc(Cd)+1
			Escribir "El numero de CDs necesarios para realizar la copia de seguridad de su disco duro es de: ",Cd ;
		FinSi
	FinSi ;
FinAlgoritmo
