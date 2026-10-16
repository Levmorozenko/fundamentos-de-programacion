// Promedios. Usa un arreglo de 6 posiciones para almacenar 5 calificaciones
// parciales de un alumno y guarda su promedio en la última posición. Muestra
// todas las calificaciones y el promedio.
#include "custom.cpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace custom;

int main() {
  custom_cls();

  vector<int> arreglo(6);

  for (int i = 0; i < 5; i++) {
    arreglo[i] = random::calificacion();
    arreglo[5] += arreglo[i];
  }

  arreglo[5] /= 5;

  cout << "Las 5 calificaciones son: ";
  for (int i = 0; i < arreglo.size() - 1; i++) {
    cout << arreglo[i] << " ";
  }
  cout << "y el promedio es: " << arreglo[5] << endl << endl;

  return 0;
}
