#include <iostream>
#include <memory>
using namespace std;

int main() {
  int *puntero = new int(10);
  cout << "Valor: " << *puntero << endl;
  // Si no liberamos el puntero al final con `delete puntero`, es una fuga,
  // ya que el valor se queda en la memoria.

  // la manera facil de evitar el problema consiste en uso de los punteros
  // inteligentes
  unique_ptr<int> puntero2 = make_unique<int>(20);
  cout << *puntero2 << endl;
  // el valor se libera solo.
}
