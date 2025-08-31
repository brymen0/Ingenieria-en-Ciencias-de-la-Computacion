Algoritmo estimacionDeLaPoblacion
	
	Definir poblacion Como Real ;
	Definir tasa Como Real ;
	Definir año1 Como Real ;
	Definir año2 Como Real ;
	Definir año3 Como Real ;
	
	Escribir "Ingrese la poblacion del pais" ;
	Leer poblacion ; 
	
	Escribir "Ingrese la tasa de crecimiento anual de la poblacion del pais en porcentaje" ;
	Leer tasa ;
	
	año1=poblacion+((tasa)/100)*poblacion ;
	Escribir "La poblacion luego de un año es de:",año1 ;
	año2=año1+((tasa)/100)*año1 ;
	Escribir "La poblacion luego de un año es de:",año2 ;
	año3=año2+((tasa)/100)*año2 ;
	Escribir "La poblacion luego de un año es de:",año3 ;
	
FinAlgoritmo
