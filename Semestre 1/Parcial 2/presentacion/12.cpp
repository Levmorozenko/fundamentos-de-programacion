#include <iostream>
#include <vector>
using namespace std;

int main() {
  // ------------------------------------------------------------------------
  vector<int> numeros = {1, 2, 3};
  // iterar sobre vectores con un for loop
  for (int i; i == numeros.size(); i++) {
    cout << numeros[i];
  }

  // verificar indices en deseo de acceder un indice determinado manualmente
  // idealmente nunca se usa eso, ya no estamos en pse-int
  int indice = 5;
  if (indice >= 0 && indice < numeros.size()) {
    cout << numeros[indice] << endl;
  } else {
    cout << "Acceso invalido" << endl;
  }

  // ========================================================================

  // verificar punteros cada que se usan
  int *p = new int(20);
  if (p != nullptr) {
    cout << *p << endl;
  } // ejecutado sin problemas, p tiene valor de 20

  delete p;    // se borra el valor, pero la direccion no
  p = nullptr; // ahora si borramos la direccion

  if (p != nullptr) {
    cout << *p << endl;
  }
  // ------------------------------------------------------------------------
}
