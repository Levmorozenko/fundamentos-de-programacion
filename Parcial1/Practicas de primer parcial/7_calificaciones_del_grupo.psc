Algoritmo calificaciones_del_grupo
	// no quiero verificar estos bombos en pseint, asumimos que el usuario es un milagro y usa el sistema como se deberia
	Escribir "Bienvendio al registro de calificaciones! Escribe el nombre de la persona y luego sus calificaciones de los 3 parciales. Para terminar, escribe: buh!"
	
	suma_de_calificaciones_final = 0
	cantidad_de_calificaciones_final = 0
	Repetir
		Escribir "Nombre de alumno o buh? (terminar el proceso?)"
		leer entrada
		
		Si entrada <> "buh!" Entonces
			nombre = entrada
			Escribir "Su calificacion del primer parcial: "
			Leer num1
			Escribir "Su calificacion del segundo parcial: "
			Leer num2
			Escribir "Su calificacion del tercer parcial: "
			Leer num3
			Escribir "El promedio de " nombre " es " (num1 + num2 + num3) / 3
			
			suma_de_calificaciones_final = suma_de_calificaciones_final + num1 + num2 + num3
			cantidad_de_calificaciones_final = cantidad_de_calificaciones_final + 3
		FinSi
		
	Hasta Que entrada = "buh!"
	
	Escribir "El promedio general del grupo es: " suma_de_calificaciones_final / cantidad_de_calificaciones_final
	
FinAlgoritmo
