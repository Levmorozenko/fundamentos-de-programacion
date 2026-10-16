#include <iostream>
using namespace std;

void imprimir(int *x) {
  if (x != nullptr) { // verificamos que x no es nulo antes de usarlo
    cout << "Edad: " << x << endl;
  }
}

int main() {
  int *puntero = new int(19);
  imprimir(puntero); // uso del puntero con valor - correcto
  free(puntero);     // liberamos el puntero
  imprimir(puntero); // uso del puntero nulo ahora no mata el programa!
}
