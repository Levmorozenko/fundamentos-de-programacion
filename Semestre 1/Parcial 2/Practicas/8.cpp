// Provoca y corrige un error de memoria. Escribe intencionalmente una función
// con un error de memoria (por ejemplo, accede a una posición fuera de rango de
// un arreglo, o usa un puntero sin inicializar). Ejecútala y documenta qué
// pasó. Después corrígela y explica, en tus propias palabras, por qué fallaba.
#include "custom.cpp"
#include <vector>
using namespace custom;

int main() {
  vector<int> arreglo = {1, 2, 3, 4, 5};

  int indice_malvado = 10;
  // Tras correr:
  // cout << arreglo[indice_malvado] << endl;
  // El programa escribió:
  // 1431760041
  //
  // Evidentemente no es un numero que esta presente en el programa. Es decir,
  // que el programa obtuvo un numero desde alguna otra parte de la RAM,
  // probablemente de otro proceso. Es un comportamiento indefinido cual puede
  // ser evitado de la siguiente manera:

  if (indice_malvado >= 0 && indice_malvado < arreglo.size()) {
    cout << arreglo[indice_malvado] << endl;
  } else {
    cout << "Indice indicado es fuera del rango" << endl;
  }

  // Tras verificar que el indice es en el rango del vector, no accedemos una
  // memoria que no nos pertenece.

  return 0;
}
