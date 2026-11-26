#include "../custom.cpp"
#include "../structs.cpp"
#include "faker-cxx/book.h"

namespace grupo {

void imprimir(const Grupo &grupo) {
  cout << "Nombre:  " << grupo.nombre << endl;
  cout << "Carrera: " << grupo.carrera << endl;
}

void imprimir_todos(const vector<Grupo> &grupos) {
  cout << thick_separator;
  cout << "Grupos: " << endl;

  for (const Grupo i : grupos) {
    cout << thin_separator;
    imprimir(i);
  }
  cout << thin_separator;

  await_enter();
}

Grupo crear_random() {
  Grupo grupo;
  grupo.carrera = faker::company::industry();
  grupo.nombre =
      faker::book::title(); // pinche biblioteca faker no se compila el modulo
                            // `education` asi que sera nombre de un libro
  return grupo;
}

Grupo capturar() {
  Grupo grupo;
  clear_terminal();
  cout << thick_separator;
  grupo.nombre = get_regexed_input(
      "Entra el nombre del grupo", name_regex,
      "El nombre del grupo no puede ser vacio o contener caracteres "
      "invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator;
  grupo.carrera = get_regexed_input(
      "Entra el nombre de la carrera: ", name_regex,
      "El nombre de la carrera no puede ser vacio o contener caracteres "
      "invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator;
  cout << "Grupo registrado!\n";
  grupo::imprimir(grupo);
  cout << thick_separator;
  await_enter();
  return grupo;
}
} // namespace grupo
