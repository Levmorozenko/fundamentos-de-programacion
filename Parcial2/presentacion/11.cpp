#include <iostream>

int main() {
  int *p = new int(10);
  std::cout << p << std::endl;

  delete p; // remueve el valor almacenado en una locacion especifica
  delete p; // remueve el valor en la misma memoria... pero si el valor asignado
            // ya no pertenece al programa... que esta liberando?

  // alternativa: punteros inteligentes.
}
