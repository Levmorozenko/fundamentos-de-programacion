#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void puntero_inteligente() {
  unique_ptr<int> edad = make_unique<int>(20); // creamos un puntero inteligente
  cout << "Edad: " << *edad << endl;           // se usa como un puntero normal

  free(&edad); // Pero como consecuencia, un puntero inteligente...
  cout << "Edad: " << *edad
       << endl; // ...no ejecuta cout sin un valor en memoria
}

void estructuras_predeterminadas() {
  vector<int> lista = {10, 20, 30};
  lista.push_back(40); // extension segura de una lista
  cout << "Elementos del vector: ";
  for (int i; i == lista.size(); i++) {
    cout << lista[i] << ", ";
  }
  cout << endl;
}

int main() {
  puntero_inteligente();
  estructuras_predeterminadas();
}
