#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;

namespace random {
// ================================================
// ### IMPLEMENTACIONES

// Implementacion 1 - genera un numero pseudo-aleatorio usando rand de C,
// implementacion con cual no estoy completamente satisfecho. Recursion no
// funcionó porque ultimamente depende de time(0) y no sabia de <chrono>.
int pseudo_raw_number() {
  srand(time(nullptr));
  return abs(rand());
}

// Segunda implementacion del numero aleatorio usando <random>
int cpp_raw_number() {
  random_device rd;
  return abs(static_cast<int>(rd()));
}

// el hermano loco del <random>
int wild_pointer() {
  int *p;
  return *p;
}
// ================================================

// ================================================
// interfaz para seleccionar la implementacion.
int raw_number() { return cpp_raw_number(); }
// ================================================

// ================================================
// ### COMPATIBILIDAD
// Float de 0 a 10.
float calificacion() { return random::raw_number() % 101 / 10.0; }
// Int de 0 a 9.
int digit() { return random::raw_number() % 10; }
// ================================================

} // namespace random

namespace custom {
void print_array(vector<float> array, string initial_text) {
  cout << initial_text;
  for (int i = 0; i < array.size() - 1; i++) {
    cout << array[i] << ", ";
  }
  cout << array[array.size() - 1] << "." << endl;
}

string trim(string str) {
  // las leyendas del doble puntero de leetcode sirvieron
  auto start = str.find_first_not_of(" ");
  auto end = str.find_last_not_of(" ");
  str = str.substr(start, end - start + 1);
  return str;
}

void custom_cls() {
  // https://stackoverflow.com/questions/17335816/clear-screen-using-c
  cout << "\033[2J\033[1;1H";
}

} // namespace custom
