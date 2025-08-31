Algoritmo areaDeUnTrianguloDadosLosLados
	//Calcula el area y el perimetro de un triangulo con saber el valor de sus lados
	
	Definir ladoA como real;
	Definir ladoB como real;
	Definir ladoc como real;
	Definir perimetro como real;
	Definir semiperimetro Como Real;
	
	Escribir Sin Saltar  "Ingrese el primer lado" ; 
	Leer ladoA ;
	
	Escribir Sin Saltar  "Ingrese el segundo lado" ;
	Leer ladoB ;
	
	Escribir Sin Saltar  "Ingrese el tercer lado" ;
	Leer ladoC ;
		
	perimetro=ladoA+ladoB+ladoC ;
	semiperimetro=perimetro/2 ;
		
	area=raiz(semiperimetro*(semiperimetro-ladoA)*(semiperimetro-ladoB)*(semiperimetro-ladoC)) ;
		
	Escribir "El perimetro es ",perimetro ;
	Escribir "El area es ",area ;
FinAlgoritmo
