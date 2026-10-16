Algoritmo descuento_por_sueldo
	Escribir "Cuenta al algoritmo chismoso, cual es tu sueldo?"
	Leer sueldo
	
	Si sueldo <= 1000 Entonces
		pago = sueldo * 1.1
		descuento = "10%"
	SiNo
		Si sueldo > 2000 Entonces
			pago = sueldo * 1.03
			descuento = "3%"
		Sino 
			pago = sueldo * 1.05
			descuento = "5%"
		FinSi
	FinSi
	
	Escribir "Tu descuento es: " descuento " y tu sueldo final es: " pago
	
FinAlgoritmo
