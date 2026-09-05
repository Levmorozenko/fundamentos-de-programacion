Algoritmo promedio_y_estatus
	Definir cal1, cal2, cal3, promedio Como Real
	Escribir "Cuanto sacaste en primer parcial?"
	Leer cal1
	Escribir "Cuanto sacaste en segundo parcial?"
	Leer cal2
	Escribir "Cuanto sacaste en tercer parcial?"
	Leer cal3
	
	promedio <- (cal1+cal2+cal3)/3
	Escribir "Tu promedio es: " promedio
	Si promedio >= 6 Entonces
		Escribir "Aprobaste!"
	SiNo
		Escribir "como reprobaste chamaco..."
	Fin Si
FinAlgoritmo
