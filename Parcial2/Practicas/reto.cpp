// Te dejo un reto, por si te da curiosidad: llena una matriz de 3 x 1,000,000 y
// otra de 1,000,000 x 3, mide con <chrono> cuánto tarda recorrer cada una por
// grupo y por alumno, y cuéntame qué encontraste. Con 30 datos no hay
// diferencia medible, pero a esa escala vas a ver por qué el orden de los datos
// depende de cómo los vas a recorrer.

#include "custom.cpp"
#include <chrono>

int main() {
  // sin static el programa no hace nada?
  auto start_v1 = chrono::high_resolution_clock::now();
  static int matriz1[3][1000000];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 1000000; j++) {
      matriz1[i][j] = 28;
    }
  }

  auto end_v1 = chrono::high_resolution_clock::now();

  auto start_v2 = chrono::high_resolution_clock::now();
  static int matriz2[1000000][3];
  for (int i = 0; i < 1000000; i++) {
    for (int j = 0; j < 3; j++) {
      matriz2[i][j] = 28;
    }
  }
  auto end_v2 = chrono::high_resolution_clock::now();

  auto time_1 = chrono::duration_cast<chrono::microseconds>(end_v1 - start_v1);
  auto time_2 = chrono::duration_cast<chrono::microseconds>(end_v2 - start_v2);

  cout << "Matriz 1 de 3 x 1,000,000 termino de rellenarse en: "
       << time_1.count() << " microsegundos." << endl;
  cout << "Matriz 2 de 1,000,000 x 3 termino de rellenarse en: "
       << time_2.count() << " microsegundos." << endl;

  return 0;
}

// Resultado:
// Matriz 1 de 3 x 1,000,000 termino de rellenarse en: 5605 microsegundos.
// Matriz 2 de 1,000,000 x 3 termino de rellenarse en: 4532 microsegundos.
//
// La matriz de 3 x 1,000,000 crea 3 arreglos con 1,000,000 objetos en cada
// arreglo y tarda mas. Crear 1,000,000 arreglos con 3 objetos en cada uno es
// mas rapido. Mi conclusion es que la segunda version es mas barata por memoria
// y tiempo debido a la alocacion de memoria. Matriz 2 crea un millon de
// arreglos pequeños, lo cual al parecer es mas eficiente.
