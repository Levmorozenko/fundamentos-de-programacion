// Una escuela clasifica a sus alumnos según su promedio final usando la siguiente tabla:
//  9.0 a 10 ? "Excelencia"
// 	8.0 a 8.9 ? "Muy bien"/
//  7.0 a 7.9 ? "Bien"
//  6.0 a 6.9 ? "Suficiente"
//  Menor a 6.0 ? "No aprobado"
//	Solicita el promedio de un alumno y muestra la clasificación correspondiente.

Algoritmo problema_2
	Escribir "Bienvenido al programa de como-saber-si-aprobaste."
	Escribir "Entra tu promedio"
	Leer promedio
	
	Si promedio > 9.0 Entonces
		Escribir "Excelencia"
	SiNo
		Si promedio < 9 y promedio >= 8 Entonces
			Escribir "Muy bien"
		SiNo
			Si promedio < 8 y promedio >= 7 Entonces
				Escribir "Bien"
			SiNo
				Si promedio < 7 y promedio >= 6 Entonces
					Escribir "Suficiente"
				SiNo
					Escribir "No aprobado"
				Fin Si
			Fin Si
		Fin Si
	Fin Si
FinAlgoritmo
