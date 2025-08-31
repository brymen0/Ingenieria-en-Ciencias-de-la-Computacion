Algoritmo calculaAreayPerimetroDeUnaFigura
	
	Definir numlados Como Entero //numeros de lados de la figura
	Definir perimetro Como Real //valor del perimetro de las figuras
	Definir area como real //valor del area de las figuras
	Definir opcion como entero //opcion que escoge el usuario en el menu 
	Definir i como entero //contador de los lados para calcular el perimetro 
	Definir longlado como entero //longitud de los lados de las figuras
	Definir bandera como entero //contador para evaluar si se realiza las acciones de calculo de perimetro y area
	Definir radio como real //valor del radio, en caso de ser la figura de un lado
	
	Escribir "======================================================================"
	Escribir "    Algoritmo que mediante un menu calcula el perimetro y area"
	Escribir "======================================================================"
	Escribir "AUTOR: BRYAN MENDOZA"
	Escribir ""
	
	bandera=-1
	Repetir //Indica al ususario que opcion necesita
		Escribir "                    M E N Ú   D E   O P C I O N E S" ;
		Escribir ""
		Escribir "1. Ingresar numero de lados" ;
		Escribir "2. Calcular el perimetro" ;
		Escribir "3. Calcular el area"
		Escribir "4. Salir del algoritmo" ;
		Escribir sin saltar "Ingrese una opcion" ;
		Leer opcion
		
		Segun opcion Hacer //Indica la opcion que debe realizar segun lo indicado por el usuario
			1: //Ingresar datos
				Repetir //Valida el numero de lados a ingresar 
					Escribir sin saltar "Ingrese el numero de lados" ;
					leer numlados ;
					Si numlados<1 o numlados>20 Entonces
						Escribir "ERROR: El numero de lados debe estar entre 1 y 20" ;
					FinSi
				Hasta Que numlados>=1 y numlados<=20
				
				Repetir //Valida la longitud de los lados de la figura
					Escribir sin saltar "Ingrese la longitud del lado de la figura"
					Leer longlado
					Si longlado<=0 Entonces
						Escribir "ERROR: El lado debe ser positivo"
					FinSi
				Hasta Que longlado>0
				bandera=1
			2: //Calcula el perimetro
				Si bandera=1 entonces
					Para i=1 Hasta numlados con paso 1 Hacer //calcula el valor del perimetro
						perimetro=perimetro+longlado
					FinPara
					Escribir "El perimetro de la figura es: ",perimetro " unidades"
				SiNo
					Escribir "ERROR: Primero debe ingresar el numero de lados y su longitud"
				Finsi
			3://Calcular el area
				Si bandera=1 Entonces
					Si numlados=1 Entonces
						Escribir "Ingrese el radio"
						Leer radio
						area=PI*radio^2
						Escribir "El area de la figura es: ",area " unidades cuadradas"
					SiNo
						Si numlados=2 Entonces
							Escribir "No se puede calcular el area"
						SiNo
							Si numlados=3 Entonces
								area=(raiz(3)*longlado^2)/4
								Escribir "El area de la figura es: ",area " unidades cuadradas"
							SiNo
								Si numlados=4 Entonces
									area=longlado^2
									Escribir "El area de la figura es: ",area " unidades cuadradas"
								SiNo
									area=(numlados*longlado^2)/(4*tan(PI/numlados))
									Escribir "El area de la figura es: ",area " unidades cuadradas"
								FinSi
							FinSi
						FinSi
					FinSi
				SiNo
					Escribir "ERROR: Primero debe ingresar el numero de lados y su longitud"
				FinSi
			4://Salir
				Escribir "Gracias"
		FinSegun
	Hasta Que opcion=4
FinAlgoritmo
