Algoritmo latidosDelCorazon
	
	Definir edad Como Entero ;
	Definir latidos como entero ;
	Definir limiteinf Como real ;
	definir limitemax como real ;
	
	Escribir "Introduzca su edad en años" ;
	Leer edad ;
	
	latidos=220-edad ;
	limiteinf=trunc(((50)/100)*latidos) ;
	limitemax=trunc(((85)/100)*latidos) ;
	
	Escribir "Su rango seguro de latidos por minuto esta entre ",limiteinf " y ",limitemax ;
	
FinAlgoritmo
