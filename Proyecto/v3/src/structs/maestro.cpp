#include "../custom.cpp"
#include "../structs.cpp"

namespace maestro {
void imprimir(const Maestro &maestro) {
  cout << "Nombre:  " << maestro.nombre << endl;
  cout << "Materia: " << maestro.materia << endl;
}

void imprimir_todos(const vector<Maestro> &maestros) {
  cout << thick_separator;
  cout << "Maestros: " << endl;

  for (Maestro i : maestros) {
    cout << thin_separator;
    imprimir(i);
  }
  cout << thin_separator;

  await_enter();
}

Maestro crear_random() {
  Maestro maestro;
  maestro.nombre = faker::person::fullName(faker::Locale::es_MX);
  maestro.materia = faker::company::industry();
  return maestro;
}

Maestro capturar() {
  Maestro maestro;
  clear_terminal();
  cout << thick_separator;
  maestro.nombre = get_regexed_input(
      "Entra el nombre del maestro: ", name_regex,
      "Su nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator;
  maestro.materia = get_regexed_input(
      "Entra el nombre de la materia que da este maestro: ", name_regex,
      "El nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator;
  cout << "Maestro registrado!\n";
  maestro::imprimir(maestro);
  cout << thick_separator;
  await_enter();
  return maestro;
}
} // namespace maestro
