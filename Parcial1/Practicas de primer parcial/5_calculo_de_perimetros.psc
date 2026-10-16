Algoritmo calculo_de_perimetros
	Escribir "Selecciona tu figura: "
	Escribir "1 - Cuadrado"
	Escribir "2 - Triangulo equilatero"
	Escribir "3 - Circulo"
	Leer figura
	
	Escribir "Entra tu medida del lado o radio: "
	Leer lado
	
	Segun figura Hacer
		"1":
			Escribir "El perimetro de tu cuadrado es: " lado * 4 " unidades"
		"2":
			Escribir "El perimetro de tu triangulo equilatero es: " lado * 3 " unidades"
		"3":
			Escribir "El perimetro de tu circulo es aproximadamente: " lado * 3.1416 * 2 " unidades"
		De Otro Modo:
			Escribir "Esta opcion todavia no es soportada por esta calculadora, soporta el desarollador a traves de suscripcion premium para mas opciones!"
	Fin Segun
	
FinAlgoritmo
