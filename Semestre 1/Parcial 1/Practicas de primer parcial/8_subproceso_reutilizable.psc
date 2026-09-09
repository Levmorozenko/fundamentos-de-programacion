Funcion procesar_promedio
	Escribir "Entra las calificaciones en orden: "
	Leer num1
	Leer num2
	Leer num3
	Escribir "El promedio del alumno es: " CalcularPromedio(num1, num2, num3)
Fin Funcion

Funcion promedio <- CalcularPromedio(num1, num2, num3) 
	promedio = (num1 + num2 + num3 ) /3
FinFuncion

Algoritmo subproceso_reutilizable 
	// porque pseint tiene punteros
	// pero no se pueden meter vectores dentro de vectores ni existen tuples? 
	procesar_promedio
	procesar_promedio
FinAlgoritmo
