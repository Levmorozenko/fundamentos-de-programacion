#include "../custom.cpp"
#include "../structs.cpp"

// #################
// ##### GRUPO #####
// #################
namespace grupo {

void imprimir(Grupo &grupo) {
  cout << "Nombre:  " << grupo.nombre << endl;
  cout << "Carrera: " << grupo.carrera << endl;
}

void imprimir_todos(vector<Grupo> &grupos) {
  clear_terminal();
  cout << thick_separator << endl;
  cout << "Grupos: " << endl;

  for (Grupo i : grupos) {
    cout << thin_separator << endl;
    imprimir(i);
  }
  cout << thin_separator << endl;

  await_enter();
}

// Crea un grupo con carrera y nombre aleatorio
Grupo crear_random() {
  Grupo grupo;
  grupo.carrera = []() {
    static const string x[7] = {"Ing. de Software",  "Ing. en Mecatronica",
                                "Ing. Industrial",   "Administracion",
                                "Cirujano cerebral", "Ing. Civil",
                                "Dentista"};
    return x[random_raw_number() % size(x)];
  }();

  grupo.nombre = []() {
    static const string x[6] = {
        "Los regulares",
        "Los electrodomesticos",
        "Los brillantes y filosos",
        "Los administrados",
        "Los buhos",
        "Las ranas electricas",
    };
    return x[random_raw_number() % size(x)];
  }();

  return grupo;
}

Grupo capturar() {
  Grupo grupo;
  clear_terminal();
  cout << thick_separator << endl;
  grupo.nombre = get_regexed_input(
      "Entra el nombre del grupo", name_regex,
      "El nombre del grupo no puede ser vacio o contener caracteres "
      "invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator << endl;
  grupo.carrera = get_regexed_input(
      "Entra el nombre de la carrera: ", name_regex,
      "El nombre de la carrera no puede ser vacio o contener caracteres "
      "invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");

  cout << thick_separator << endl;
  cout << "Grupo registrado!\n";
  grupo::imprimir(grupo);
  cout << thick_separator << endl;
  await_enter();
  return grupo;
}
} // namespace grupo
