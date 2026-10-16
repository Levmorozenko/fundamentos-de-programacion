// Crea un subproceso llamado CalcularArea que reciba la base y la altura de un triángulo 
// y regrese su área. Usando ese subproceso, solicita al usuario los datos de 5 triángulos 
// distintos (uno por uno) y, al final, muestra cuál de los 5 triángulos tuvo el área más grande.

Funcion area <- CalcularArea (base, altura) // asumiendo triangulo recto
	area = base * altura 
FinFuncion

Funcion resultado <- is_sorted (array)
	// siempre areas.len() = 5
	resultado = Verdadero
	Para i<-1 Hasta 4 Hacer 
		si array[i] > array[i+1] Entonces
			resultado = falso
		FinSi
	Fin Para
Fin Funcion

Algoritmo problema_3
	debug = falso
	
	si debug = falso 
		Escribir "Bienvenido a calculadora de triangulos rectos"
		Escribir "Entra la base y altura de 5 triangulos rectos"
		Escribir "Presione tecla Enter para continuar"
		leer null
	FinSi
	
	Dimensionar areas[5]
	
	Para i <- 1 Hasta 5 Hacer
		Limpiar Pantalla
		Escribir "Triangulo " i
		Escribir "Entra la base: "
		Leer base
		Escribir "Entra la altura: "
		Leer altura
		
		areas[i] = CalcularArea(base, altura)
	Fin Para
	
	// ############################################
	// ### bi-directional array sorting section ### 
	// ############################################
	
	// No memorizé algoritmos de sorteo de arreglos. Lo haré a como me acordaré. 
	// Es ineficiente y repite instrucciones, pero es mio, y estamos en pseint.
	dimensionar triangulos[5]
	Para i <- 1 hasta 5 hacer
		triangulos[i] = i
	FinPara
	
	Repetir
		Para i<-1 Hasta 4 Hacer 
			si areas[i] > areas[i+1] Entonces
				tmp = areas[i+1]
				areas[i+1] = areas[i]
				areas[i] = tmp
			
				tmp = triangulos[i+1]
				triangulos[i+1] = triangulos[i]
				triangulos[i] = tmp
			FinSi
		Fin Para
	Hasta Que is_sorted(areas)
	
	// --------------------------------------------
	
	Escribir "El triangulo mas grande es triangulo " triangulos[5] " con area de " areas[5] " unidades!"
	
FinAlgoritmo
