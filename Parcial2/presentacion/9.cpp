#include <fstream>
#include <iostream>
using namespace std;

int main() {
  ofstream archivo("datos.txt"); // abre un archivo
  if (archivo.is_open()) {       // se abrió el archivo?
    archivo << "Guardando informacion de forma segura"
            << endl; // entonces lo modificamos
  }

  // otro ejemplo
  int *puntero = new int(10);
  cout << "Valor: " << *puntero << endl; // usamos la variable de alguna manera

  delete puntero;    // removemos el valor asignado al puntero - o sea 10
  puntero = nullptr; // evadimos puntero nulo de manera segura
}
