// Se tiene un arreglo de 15 números que representan las ventas diarias de una
// tienda durante medio mes. Calcula e imprime: el total de ventas, el promedio
// diario, y cuántos días la venta fue superior al promedio.

#include <iostream>
using namespace std;

int main() {
  const static int arreglo[15] = {12, 43, 23, 6, 7,  15, 16, 84,
                                  56, 72, 0,  0, 14, 24, 52};

  int total, huh;
  for (int i : arreglo) {
    total += i;
  }

  float promedio = static_cast<float>(total) / 15.0;

  for (int i : arreglo)
    if (i > promedio)
      huh++;

  cout << "Se vendio el total de: " << total << " productos\n";
  cout << "El promedio diario es: " << promedio << " ventas\n";
  cout << "En " << huh
       << " dias la cantidad de ventas fue superior al promedio";
}
