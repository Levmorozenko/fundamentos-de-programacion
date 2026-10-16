#include "../custom.cpp"
#include "../structs.cpp"
#include "grupo.cpp"
#include <unordered_map>
#include <vector>

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

void imprimir_todos(vector<Alumno> &alumnos, string msg = "Alumnos: ") {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << msg << endl;

  for (Alumno i : alumnos) {
    cout << custom::thin_separator << endl;
    imprimir(i);
  }
  cout << custom::thin_separator << endl;

  custom::await_enter();
}

// Abstraccion es posible, mas no es deseada. Ya asbtraí todo lo demas del
// programa. Ademas, conozco la ineficiencia de copiar los Alumno-s enteros a
// los vectores en vez de referencias, pero me faltan 3 horas y media para la.
// Espero implementar eso en Proyecto v3.
void imprimir_alumno_con_mayor_promedio_del_grupo(vector<Grupo> &grupos,
                                                  vector<Alumno> &alumnos) {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << "Grupos registrados: " << endl;
  for (size_t i = 0; i < grupos.size(); i++) {
    cout << i + 1 << ") " << grupos[i].nombre << " - " << grupos[i].carrera
         << endl;
  }

  int input;
  bool valid;
  do {
    input = stoi(custom::get_regexed_input(
        "Selecciona el grupo: ", custom::digit_regex,
        "Por favor selecciona el grupo de la lista."));
    input -= 1;
    valid = input >= 0 && input < grupos.size();
  } while (!valid);

  vector<Alumno> alumnos_del_grupo;
  for (Alumno i : alumnos) {
    if (i.grupo == input) {
      alumnos_del_grupo.push_back(i);
    }
  }

  if (alumnos_del_grupo.empty()) {
    cout << "No hay alumnos en ese grupo\n";
    return;
  }

  // alocar y tirar un vector en cada nuevo alumno con promedio mas alto, es
  // menos eficiente que 2 for loops.
  float mayor_promedio = alumnos_del_grupo[0].promedio;
  for (Alumno i : alumnos_del_grupo) {
    if (i.promedio > mayor_promedio) {
      mayor_promedio = i.promedio;
    };
  }

  // Asi mismo alocar 2 vectores es teoreticamente mas eficiente que una
  // cantidad de vectores entre 1 y alumnos.size().
  vector<Alumno> nerd_list;
  for (Alumno i : alumnos_del_grupo) {
    if (i.promedio == mayor_promedio) {
      nerd_list.push_back(i);
    }
  }

  string msg = "Alumno" + string(nerd_list.size() > 1 ? "" : "s") +
               " con mayor promedio del grupo: ";
  imprimir_todos(nerd_list, msg);
}

// podria ser utilizado mejor, pero es funcional, y es lo mas importante.
void imprimir_cantidad_de_alumnos_por_carrera(vector<Grupo> &grupos,
                                              vector<Alumno> &alumnos) {
  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << "Carreras registradas: " << endl;

  // map<carrera, lista_de_indices_de(grupos)>
  unordered_map<string, vector<int>> carreras;
  for (int i = 0; i < grupos.size(); i++) {
    // porque algunas cosas tienen un monton de comportamiento pre-determinado,
    // pero tantas cosas obvias y faciles de plano no existen? Es esta la
    // filosofia de puristas de c++ en linux kernel? Tener esto pero no tener
    // std::string::trim()?
    carreras[grupos[i].carrera].push_back(i);
  }

  int counter = 1;
  vector<string> carreras_keys; // no encontre una funcion para iterar sobre
                                // cada clave, asi que lo hago manualmente.
  for (auto [claves, indices] : carreras) {
    cout << counter << ") " << claves << " - ";
    for (int n : indices) {
      cout << grupos[n].nombre << ", ";
    }
    cout << endl;
    carreras_keys.push_back(claves);
    counter += 1;
  }

  int input;
  bool valid;
  do {
    input = stoi(custom::get_regexed_input(
        "Selecciona la carrera: ", custom::digit_regex,
        "Por favor selecciona la carrera de la lista."));
    input -= 1;
    valid = input >= 0 && input < carreras_keys.size();
  } while (!valid);

  string carrera_elegida = carreras_keys[input];
  const vector<int> &indices = carreras[carrera_elegida];

  int cantidad = 0;
  for (const Alumno &alumno : alumnos) {
    for (int g : indices) {
      if (alumno.grupo == g) {
        cantidad++;
        break;
      }
    }
  }

  custom::clear_terminal();
  cout << custom::thick_separator << endl;
  cout << "La carrera " << carrera_elegida << " tiene " << cantidad
       << " alumnos.\n";
  cout << custom::thick_separator << endl;
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
  alumno.promedio = custom::promedio(alumno.calif, 3);
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
  alumno.promedio = custom::promedio(alumno.calif, 3);
  cout << custom::thin_separator << endl;

  alumno.grupo = [&](vector<Grupo> grupos) -> int {
    if (grupos.empty()) {
      return -1;
    }

    cout << "Selecciona el grupo del alumno" << endl;
    for (size_t i = 0; i < grupos.size(); i++) {
      cout << i + 1 << ") " << grupos[i].nombre << " - " << grupos[i].carrera
           << endl;
    }

    bool valid;
    size_t indice;
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
