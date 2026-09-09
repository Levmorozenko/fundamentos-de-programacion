Funcion opcion_elegida <- elegir_opcion
	done = Falso
	Repetir
		Escribir "1 - Capturar datos de los 3 alumnos."
		Escribir "2 - Mostrar promedios de cada de los alumnos"
		Escribir "3 - Mostrar el mejor promedio"
		Escribir "4 - Salir."
		Leer entrada
		Si entrada = "1" o entrada = "2" o entrada = "3" o entrada = "4" Entonces
			opcion_elegida = entrada
			done = Verdadero
		SiNo
			Escribir "Opcion invalida, intenta una de las opciones dadas."
		Fin Si
	Hasta Que done = Verdadero
FinFuncion

Funcion escribir_promedios(n1, p1, n2, p2, n3, p3) 
	Limpiar Pantalla
	Escribir "El alumno " n1 " tiene el promedio de " p1
	Escribir "El alumno " n2 " tiene el promedio de " p2
	Escribir "El alumno " n3 " tiene el promedio de " p3
FinFuncion

Funcion escribir_promedio_mayor(alumno1_nombre, promedio1, alumno2_nombre, promedio2, alumno3_nombre, promedio3)
	
	si promedio1 > promedio2 y promedio1 > promedio3 Entonces
		nerd = alumno1_nombre
		mejor_promedio = promedio1
	FinSi
	si promedio2 > promedio1 y promedio2 > promedio3 Entonces
		nerd = alumno2_nombre
		mejor_promedio = promedio2
	FinSi
	si promedio3 > promedio2 y promedio3 > promedio1 Entonces
		nerd = alumno3_nombre
		mejor_promedio = promedio3
	FinSi
	
	Escribir "La mayor calificacion de " mejor_promedio " pertenece a " nerd
FinFuncion

	
Algoritmo main
    hay_datos = Falso
	Dimensionar datos[12]
	Repetir
	    opcion_elegida = ConvertirANumero(elegir_opcion)
		Segun opcion_elegida Hacer
		    1:
				// alumno 1
				Escribir "Escribe el nombre del alumno 1: "
				Leer alumno1_nombre
				Escribir "Su calificacion de primer parcial: "
				Leer alumno1_parcial1
				Escribir "Su calificacion de segundo parcial: "
				Leer alumno1_parcial2
				Escribir "Su calificacion de tercer parcial: "
				Leer alumno1_parcial3
				alumno1_promedio = (alumno1_parcial1 + alumno1_parcial2 + alumno1_parcial3)/3
				
				// alumno 2
				Escribir "Escribe el nombre del alumno 2: "
				Leer alumno2_nombre
				Escribir "Su calificacion de primer parcial: "
				Leer alumno2_parcial1
				Escribir "Su calificacion de segundo parcial: "
				Leer alumno2_parcial2
				Escribir "Su calificacion de tercer parcial: "
				Leer alumno2_parcial3
				alumno2_promedio = (alumno2_parcial1 + alumno2_parcial2 + alumno2_parcial3)/3
				
				// alumno 3 
				Escribir "Escribe el nombre del alumno 3: "
				Leer alumno3_nombre
				Escribir "Su calificacion de primer parcial: "
				Leer alumno3_parcial1
				Escribir "Su calificacion de segundo parcial: "
				Leer alumno3_parcial2
				Escribir "Su calificacion de tercer parcial: "
				Leer alumno3_parcial3
				alumno3_promedio = (alumno3_parcial1 + alumno3_parcial2 + alumno3_parcial3)/3
				
				hay_datos = Verdadero
		    2:
			    Si hay_datos == Verdadero Entonces
				    escribir_promedios(alumno1_nombre, alumno1_promedio, alumno2_nombre, alumno2_promedio, alumno3_nombre, alumno3_promedio)
			    SiNo
				    Escribir "No hay datos para procesar"
			    Fin Si
		    3:
			    Si hay_datos == Verdadero Entonces
					escribir_promedio_mayor(alumno1_nombre, alumno1_promedio, alumno2_nombre, alumno2_promedio, alumno3_nombre, alumno3_promedio)
			    SiNo
				    Escribir "No hay datos para procesar"
			    Fin Si
		    4: 
			    terminar_algoritmo = Verdadero
		    De Otro Modo:
			    Escribir "Tecnicamente no es posible llegar a este caso."
	    Fin Segun
		
	Hasta Que terminar_algoritmo = Verdadero
FinAlgoritmo
