#include "../custom.cpp"
#include "../structs.cpp"

// ####################
// ##### MAESTROS #####
// ####################
namespace maestro {
void imprimir(Maestro &maestro) {
  cout << "Nombre:  " << maestro.nombre << endl;
  cout << "Materia: " << maestro.materia << endl;
}

void imprimir_todos(vector<Maestro> &maestros) {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << "Maestros: " << endl;

  for (Maestro i : maestros) {
    cout << custom::thin_separator << endl;
    imprimir(i);
  }
  cout << custom::thin_separator << endl;

  custom::await_enter();
}

Maestro crear_random() {
  Maestro maestro;
  maestro.nombre = []() {
    string x;
    static const string nombres[5] = {
        "Juan", "Pablo", "Lalo", "Jose", "Jorge",
    };
    x.append(nombres[custom::random_raw_number() % size(nombres)]);
    x.append(" ");

    static const string apellidos[6] = {
        "Hernandez", "Castillo", "Guzman", "Perez", "Rodriguez", "Sanchez",
    };
    x.append(apellidos[custom::random_raw_number() % size(apellidos)]);

    return x;
  }();

  maestro.materia = []() {
    static const string x[7] = {"Ing. de Software",  "Ing. en Mecatronica",
                                "Ing. Industrial",   "Administracion",
                                "Cirujano cerebral", "Ing. Civil",
                                "Dentista"};
    return x[custom::random_raw_number() % size(x)];
  }();

  return maestro;
}

Maestro capturar() {
  Maestro maestro;
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  maestro.nombre = custom::get_regexed_input(
      "Entra el nombre del maestro: ", custom::name_regex,
      "Su nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << custom::thick_separator << endl;
  maestro.materia = custom::get_regexed_input(
      "Entra el nombre de la materia que da este maestro: ", custom::name_regex,
      "El nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << custom::thick_separator << endl;
  cout << "Maestro registrado!\n";
  maestro::imprimir(maestro);
  cout << custom::thick_separator << endl;
  custom::await_enter();
  return maestro;
}
} // namespace maestro
