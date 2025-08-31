Algoritmo determiarSiFormaUnTriangulo
	//Algoritmo para que dado tres numeros, determine si forman un triangulo, que tipo de triangulo es, y determina su area usando formula de Heron y perimetro
	
	Definir ladoA como Entero
	Definir ladoB como Entero
	Definir ladoc como Entero
	Definir perimetro como Entero
	Definir semiperimetro Como Real
	
	Escribir Sin Saltar  "Ingrese el primer lado"
	Leer ladoA
	
	Escribir Sin Saltar  "Ingrese el segundo lado"
	Leer ladoB
	
	Escribir Sin Saltar  "Ingrese el tercer lado"
	Leer ladoC
	
	Si (ladoA+ladoB>ladoC) o (ladoA+ladoC>ladoB) o (ladoB+ladoC>ladoA) Entonces
		Escribir "Si forman un triangulo"
		
		Si (ladoA=ladoB) y (ladoB=ladoC) y (ladoA=ladoB) Entonces
			
			Escribir "Forman un triangulo equilatero"
			SiNo
			Si(ladoA=ladoB) o (ladoA=ladoC) o (ladoB=ladoC) Entonces
			Escribir "Forman un triangulo isosceles"
				
		SiNo
				Escribir "Forman un tringulo escaleno"
			FinSi
		FinSi
		
	perimetro=ladoA+ladoB+ladoC
	semiperimetro=perimetro/2
		
	area=raiz(semiperimetro*(semiperimetro-ladoA)*(semiperimetro-ladoB)*(semiperimetro-ladoC))
	
	Escribir "El perimetro es ",perimetro
	
	Escribir "El area es ",area
		
		
	Sino
			Escribir "Los numeros ingresados no forman un triangulo"
	FinSi
FinAlgoritmo
