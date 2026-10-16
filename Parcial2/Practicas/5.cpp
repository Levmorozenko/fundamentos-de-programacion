// Separar nombre completo. Dado un string con nombre y apellido, sepáralos
// en dos variables. Valida que ninguno de los dos contenga números.
// Nota: multiples horas fueron a este codigo, por lo que es bonito y
// formateado.
#include "custom.cpp"
using namespace custom;
#include <iostream>
#include <regex>
#include <string>
using namespace std;

void print_separator() {
  cout << "===================================================================="
          "===="
       << endl;
}

int main() {
  // ========================================================================
  // MENSAJE Y RECEPCION DE ENTRADA
  custom_cls();

  print_separator();
  cout << "Escribe un nombre y uno de los apellidos de la persona separada con "
          "un ;"
       << endl;
  cout << "De tal manera: { nombres ; apellidos }" << endl;

  string input;
  getline(cin, input);

  cout << endl;
  print_separator();
  // ------------------------------------------------------------------------

  // ========================================================================
  // SEPARACION DE ENTRADA
  // input.find(...) retornaba -1 si habian espacios. El culpable fue el cin,
  // cual corta la entrada si encuentra espacios.
  int split_at = input.find(";");
  if (split_at == -1) {
    cout << "No se encontro un ; en su entrada." << endl;
    return 1;
  }
  string nombre = input.substr(0, split_at);
  string apellido = input.substr(split_at + 1, (input.size() - split_at - 1));
  // ------------------------------------------------------------------------

  // ========================================================================
  // REGEX & TRIM
  regex numeros("[0-9]");
  nombre = trim(nombre);
  if (regex_search(nombre, numeros)) {
    cerr << "El nombre contiene numeros, intente otra vez." << endl;
    cerr << "Nombre: " << nombre << endl << endl;
    return 1;
  }

  apellido = trim(apellido);
  if (regex_search(apellido, numeros)) {
    cerr << "El apellido contiene numeros, intente otra vez." << endl;
    cerr << "Apellido: " << apellido << endl << endl;
    return 1;
  }
  // ------------------------------------------------------------------------

  // ========================================================================
  // SALIDA
  cout << endl;
  cout << "Nombre y apellido pasaron las pruebas!" << endl;
  cout << "Nombre:   " << nombre << endl;
  cout << "Apellido: " << apellido << endl << endl;
  // ------------------------------------------------------------------------
  return 0;
}
