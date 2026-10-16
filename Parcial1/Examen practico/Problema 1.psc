// Una tienda de abarrotes vende un producto a cierto precio unitario.
// Solicita al usuario:
// el precio unitario y la cantidad de piezas compradas,
// calcula el total a pagar, y si el total supera $300, aplica un descuento del 8% sobre el total.
// Muestra el total final a pagar.

Algoritmo problema_1
	Escribir "Bienvenido al programa de abarrotes"
	Escribir "Entra el precio unitario de tu producto: "
	Leer precio
	Escribir "Entra la cantidad de piezas compradas: "
	leer cantidad
	
	total = precio * cantidad
	
	si total > 300 Entonces
		total = total * 0.92
	FinSi
	
	Escribir "Tu total es: " total
FinAlgoritmo
