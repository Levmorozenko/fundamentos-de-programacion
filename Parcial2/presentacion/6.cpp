#include <iostream>
using namespace std;

int imprimir(int *x) { cout << "Edad: " << x << endl; }

int main() {
  int edad = 19;
  int *puntero = &edad;
  imprimir(puntero); // uso del puntero con valor - correcto
  free(puntero);     // liberamos el puntero
  imprimir(puntero); // uso del puntero nulo, PROGRAMA ROMPE Y MUERE!!!!
}
