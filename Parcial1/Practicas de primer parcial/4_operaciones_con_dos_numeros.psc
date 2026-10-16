Algoritmo operaciones_con_dos_numeros
	Escribir "Tu numero 1: "
	Leer num1
	Escribir "Tu numero 2: "
	leer num2
	
	Si num1 = num2 Entonces
		resultado = num1 * num2
	SiNo
		Si num1 > num2 Entonces
			resultado = num1 - num2
		SiNo
			Si num1 < num2 Entonces
				resultado = num1 + num2
				
			FinSi
		FinSi
	FinSi
	
	Escribir "Tu resultado es: " resultado
	
FinAlgoritmo
