Algoritmo estimacionDeLaPoblacion
	
	Definir poblacion Como Real ;
	Definir tasa Como Real ;
	Definir a�o1 Como Real ;
	Definir a�o2 Como Real ;
	Definir a�o3 Como Real ;
	
	Escribir "Ingrese la poblacion del pais" ;
	Leer poblacion ; 
	
	Escribir "Ingrese la tasa de crecimiento anual de la poblacion del pais en porcentaje" ;
	Leer tasa ;
	
	a�o1=poblacion+((tasa)/100)*poblacion ;
	Escribir "La poblacion luego de un a�o es de:",a�o1 ;
	a�o2=a�o1+((tasa)/100)*a�o1 ;
	Escribir "La poblacion luego de un a�o es de:",a�o2 ;
	a�o3=a�o2+((tasa)/100)*a�o2 ;
	Escribir "La poblacion luego de un a�o es de:",a�o3 ;
	
FinAlgoritmo
