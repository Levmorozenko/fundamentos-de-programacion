#include "../custom.cpp"
#include "../structs.cpp"

namespace maestro {
void imprimir(Maestro &maestro) {
  cout << "Nombre:  " << maestro.nombre << endl;
  cout << "Materia: " << maestro.materia << endl;
}

void imprimir_todos(vector<Maestro> &maestros) {
  clear_terminal();
  cout << thick_separator << endl;
  cout << "Maestros: " << endl;

  for (Maestro i : maestros) {
    cout << thin_separator << endl;
    imprimir(i);
  }
  cout << thin_separator << endl;

  await_enter();
}

Maestro crear_random() {
  Maestro maestro;
  maestro.nombre = []() {
    string x;
    static const string nombres[5] = {
        "Juan", "Pablo", "Lalo", "Jose", "Jorge",
    };
    x.append(nombres[random_raw_number() % size(nombres)]);
    x.append(" ");

    static const string apellidos[6] = {
        "Hernandez", "Castillo", "Guzman", "Perez", "Rodriguez", "Sanchez",
    };
    x.append(apellidos[random_raw_number() % size(apellidos)]);

    return x;
  }();

  maestro.materia = []() {
    static const string x[7] = {"Ing. de Software",  "Ing. en Mecatronica",
                                "Ing. Industrial",   "Administracion",
                                "Cirujano cerebral", "Ing. Civil",
                                "Dentista"};
    return x[random_raw_number() % size(x)];
  }();

  return maestro;
}

Maestro capturar() {
  Maestro maestro;
  clear_terminal();
  cout << thick_separator << endl;
  maestro.nombre = get_regexed_input(
      "Entra el nombre del maestro: ", name_regex,
      "Su nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator << endl;
  maestro.materia = get_regexed_input(
      "Entra el nombre de la materia que da este maestro: ", name_regex,
      "El nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator << endl;
  cout << "Maestro registrado!\n";
  maestro::imprimir(maestro);
  cout << thick_separator << endl;
  await_enter();
  return maestro;
}
} // namespace maestro
