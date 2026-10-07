// Matriz de alumnos. Usa una matriz de 10x3: las primeras dos columnas son los
// promedios de 10 alumnos de dos grupos (A y B), la tercera almacena el
// promedio más alto de cada fila.
#include "custom.cpp"
using namespace custom;

int main() {
  // ===========================================================================
  // llena los promedios de alumnos
  int matriz[3][10]; // 3 arrays, 10 items in each array
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      matriz[i][j] = random::calificacion();
    }
  }
  // ===========================================================================
  for (int i = 0; i < 10; i++) {
    matriz[2][i] =
        ((matriz[0][i] > matriz[1][i]) ? matriz[0][i] : matriz[1][i]);
  }

  cout << "Las calificaciones de grupo 1: ";
  for (float i : matriz[0]) {
    cout << i << " ";
  }
  cout << endl;

  cout << "Las calificaciones de grupo 2: ";
  for (float i : matriz[1]) {
    cout << i << " ";
  }
  cout << endl;

  cout << "El promedio mas alto de la fila: ";
  for (float i : matriz[2]) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}
