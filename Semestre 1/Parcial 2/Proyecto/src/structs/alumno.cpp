#include "../custom.cpp"
#include "../structs.cpp"

// ##################
// ##### ALUMNO #####
// ##################
namespace alumno {
// Tenemos que usar structs, pero necesito formato en mis funciones, saber a que
// pertenecen, organizarlos. Los namespaces replican como lo haria con metodos,
// sin embargo cumplen con requisitos de la tarea.

void imprimir(Alumno &alumno) {
  cout << "Nombre:         " << alumno.nombre << endl;
  cout << "Matricula:      " << alumno.matricula << endl;
  cout << "Calificaciones: ";
  fr(i, 3) cout << alumno.calif[i] << ", ";
  cout << endl;
  cout << "Promedio:       " << custom::promedio(alumno.calif, 3) << endl;
  cout << "Grupo:          " << alumno.grupo + 1 << endl;
}

void imprimir_todos(vector<Alumno> &alumnos) {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << "Alumnos: " << endl;

  for (Alumno i : alumnos) {
    cout << custom::thin_separator << endl;
    imprimir(i);
  }
  cout << custom::thin_separator << endl;

  custom::await_enter();
}

// Crea alumno con valores aleatorios.
Alumno crear_random(vector<Grupo> &grupos) {
  Alumno alumno;
  const static string nombres[10] = {
      "nombre0", "nombre1", "nombre2", "nombre3", "nombre4",
      "nombre5", "nombre6", "nombre7", "nombre8", "nombre9",
  };
  alumno.nombre = nombres[custom::random_raw_number() % (size(nombres))];
  alumno.matricula = []() -> string {
    string matricula;
    for (int i = 0; i < 9; i++) {
      matricula.append(to_string(custom::random_raw_number() % 10));
    }
    return matricula;
  }();
  fr(i, 3) alumno.calif[i] = ((custom::random_raw_number() % 101) / 10.0);
  alumno.grupo = custom::random_raw_number() % size(grupos);
  return alumno;
}

// Captura el alumno basado en la entrada
Alumno capturar(vector<Grupo> &grupos) {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  Alumno alumno;
  alumno.nombre = custom::get_regexed_input(
      "Entra el nombre del alumno: ", custom::name_regex,
      "El nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");
  cout << custom::thin_separator << endl;

  alumno.matricula = custom::get_regexed_input(
      "Entra la matricula del alumno", custom::digit_regex,
      "La matricula solo puede tener numeros, por favor intente de nuevo.\n");
  cout << custom::thin_separator << endl;

  // hay una mejor manera de hacer esto, lo se, lo siento - pero todavia no se
  // como...
  for (int i = 0; i < 3; i++) {
    // std::string.c_str() = const char *, lo que espera la funcion.
    float x = stof(custom::get_regexed_input(
        ("Entra la calificacion " + to_string(i + 1) + " del alumno: ").c_str(),
        custom::float_regex, "La calificacion debe ser un numero.\n"));
    alumno.calif[i] = abs(round(x * 10.0) / 10.0);
  }
  cout << custom::thin_separator << endl;

  alumno.grupo = [&](vector<Grupo> grupos) -> int {
    if (grupos.empty()) {
      return -1;
    }

    cout << "Selecciona el grupo del alumno" << endl;
    for (int i = 0; i < grupos.size(); i++) {
      cout << i + 1 << ") " << grupos[i].nombre << " - " << grupos[i].carrera
           << endl;
    }

    bool valid;
    int indice;
    do {
      indice = stoi(custom::get_regexed_input(
                   "", custom::digit_regex,
                   "Elige un elemento de la lista de grupos disponibles.\n")) -
               1;
      valid = indice >= 0 && indice < grupos.size();
      if (!valid) {
        cout << "Elige un elemento de la lista de grupos disponibles.\n";
      }
    } while (!valid);
    return indice;
  }(grupos);

  cout << custom::thick_separator << endl;
  cout << "Alumno registrado!\n";
  imprimir(alumno);
  cout << custom::thick_separator << endl;
  custom::await_enter();
  return alumno;
}

} // namespace alumno
