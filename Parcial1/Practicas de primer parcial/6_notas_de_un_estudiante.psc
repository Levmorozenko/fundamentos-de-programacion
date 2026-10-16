Algoritmo notas_de_un_estudiante
	Escribir "Escribe todas tus notas en esta lista. Escribe -67 para terminar"
	reprobadas = 0
	aprobadas = 0
	
	Mientras entrada <> -67 Hacer
		Leer entrada
		Si entrada <> -67 Entonces
			Si entrada >= 6 Entonces
				aprobadas = aprobadas + 1
				suma_de_aprobados = suma_de_aprobados + entrada
			SiNo 
				reprobadas = reprobadas + 1
				suma_de_reprobados = suma_de_reprobados + entrada
			Fin Si	
		Fin Si
	Fin Mientras
	
	Limpiar Pantalla
	
	Si aprobadas = 0 Entonces
		safe_aprobadas = 1
	SiNo 
		safe_aprobadas = aprobadas
	FinSi
	Si reprobadas = 0 Entonces
		safe_reprobadas = 1
	SiNo 
		safe_reprobadas = reprobadas
	FinSi
	
	Escribir "Estadisticas finales: "
	Escribir aprobadas " calificaciones aprobadas con " suma_de_aprobados / safe_aprobadas " de promedio."
	Escribir reprobadas " calificaciones reprobadas con " suma_de_reprobados / safe_reprobadas " de promedio."
	Escribir "El promedio general es: " (suma_de_aprobados + suma_de_reprobados) / (safe_aprobadas + safe_reprobadas)
	
FinAlgoritmo
