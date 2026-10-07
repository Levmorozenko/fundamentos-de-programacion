// Intercambio por referencia. Escribe una función que reciba dos variables por
// referencia (o por puntero) y las intercambie. Demuestra que el cambio
// persiste fuera de la función.
#include "custom.cpp"
using namespace custom;

void intercambiar(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
  cout << "num1 dentro de la funcion es: " << *a << endl;
  cout << "num2 dentro de la funcion es: " << *b << endl;
  cout << "Y el resultado de num1 / num2 es: "
       << static_cast<float>(*a) / static_cast<float>(*b) << endl
       << endl;
}

int main() {
  custom_cls();

  int num1 = 2;
  int num2 = 5;
  cout << "num1 es: " << num1 << endl;
  cout << "num2 es: " << num2 << endl;
  cout << "Y el resultado de num1 / num2 es: "
       << static_cast<float>(num1) / static_cast<float>(num2) << endl
       << endl;

  intercambiar(&num1, &num2);

  cout << "Dado que modificamos la memoria directamente," << endl
       << "el cambio persiste fuera de la funcion, por lo que: " << endl;
  cout << "num1 afuera de la funcion tambien es: " << num1 << endl;
  cout << "num2 afuera de la funcion tambien es: " << num2 << endl;
  cout << "Y el resultado de num1 / num2 tambien es: "
       << static_cast<float>(num1) / static_cast<float>(num2) << endl
       << endl;

  return 0;
}
