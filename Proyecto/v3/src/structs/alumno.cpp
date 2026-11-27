#include "../saving/alumno.cpp"
#include "../custom.cpp"
#include "../structs.cpp"
#include "grupo.cpp"

namespace alumno {

void imprimir(const Alumno &alumno) {
  cout << "Nombre:         " << alumno.nombre << endl;
  cout << "Matricula:      " << alumno.matricula << endl;
  cout << "Calificaciones: ";
  fr(i, 3) cout << alumno.calif[i] << ", ";
  cout << endl;
  cout << "Promedio:       " << promedio(alumno.calif, 3) << endl;
  cout << "Grupo №:        " << alumno.grupo + 1 << endl;
}

void imprimir_todos(const vector<Alumno> &alumnos,
                    const string msg = "Alumnos: ") {
  cout << thick_separator;
  cout << msg << endl;

  for (Alumno i : alumnos) {
    cout << thin_separator;
    imprimir(i);
  }
  cout << thin_separator;

  await_enter();
}

void imprimir_alumno_con_mayor_promedio_del_grupo(
    const vector<Grupo> &grupos, const vector<Alumno> &alumnos) {
  clear_terminal();
  cout << thick_separator;
  cout << "Grupos registrados: " << endl;
  for (size_t i = 0; i < grupos.size(); i++) {
    cout << i + 1 << ") " << grupos[i].nombre << " - " << grupos[i].carrera
         << endl;
  }

  int input;
  bool valid;
  do {
    input =
        stoi(get_regexed_input("Selecciona el grupo: ", digit_regex,
                               "Por favor selecciona el grupo de la lista."));
    input -= 1;
    valid = input >= 0 && input < grupos.size();
    if (!valid)
      cout << "Por favor selecciona el grupo de la lista.";
  } while (!valid);

  vector<Alumno> alumnos_del_grupo;
  for (Alumno i : alumnos) {
    if (i.grupo == input) {
      alumnos_del_grupo.push_back(i);
    }
  }

  if (alumnos_del_grupo.empty()) {
    cout << "No hay alumnos en ese grupo\n";
    await_enter();
    return;
  }

  float mayor_promedio = alumnos_del_grupo[0].promedio;
  for (Alumno i : alumnos_del_grupo) {
    if (i.promedio > mayor_promedio) {
      mayor_promedio = i.promedio;
    };
  }

  vector<Alumno> nerd_list;
  for (Alumno i : alumnos_del_grupo) {
    if (i.promedio == mayor_promedio) {
      nerd_list.push_back(i);
    }
  }

  string msg = "Alumno" + string(nerd_list.size() > 1 ? "s" : "") +
               " con mayor promedio del grupo: ";
  imprimir_todos(nerd_list, msg);
}

void imprimir_cantidad_de_alumnos_por_carrera(const vector<Grupo> &grupos,
                                              const vector<Alumno> &alumnos) {
  clear_terminal();
  cout << thick_separator;
  cout << "Carreras registradas: " << endl;

  unordered_map<string, vector<int>> carreras;
  for (int i = 0; i < grupos.size(); i++) {
    carreras[grupos[i].carrera].push_back(i);
  }

  int counter = 1;
  vector<string> carreras_keys;
  for (auto [claves, indices] : carreras) {
    cout << counter << ") " << claves << " - ";
    fro(n, indices) cout << grupos[n].nombre << endl;
    carreras_keys.push_back(claves);
    counter += 1;
  }

  int input;
  bool valid;
  do {
    input =
        stoi(get_regexed_input("Selecciona la carrera: ", digit_regex,
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

  clear_terminal();
  cout << thick_separator;
  cout << "La carrera " << carrera_elegida << " tiene " << cantidad
       << " alumnos.\n";
  cout << thin_separator;
  await_enter();
}

Alumno crear_random(const vector<Grupo> &grupos) {
  Alumno alumno;
  alumno.nombre = faker::person::fullName(faker::Locale::es_MX);
  alumno.matricula = faker::string::numeric(10);
  fr(i, 3) alumno.calif[i] =
      round(faker::number::decimal(10.0f) * 10.0f) / 10.0f;
  alumno.promedio = promedio(alumno.calif, 3);
  alumno.grupo =
      faker::number::integer(0, (static_cast<int>(grupos.size()) - 1));
  return alumno;
}

Alumno capturar(const vector<Grupo> &grupos) {
  clear_terminal();
  cout << thick_separator;
  Alumno alumno;
  alumno.nombre = get_regexed_input(
      "Entra el nombre del alumno: ", name_regex,
      "El nombre no puede ser vacio o contener caracteres invalidos.\n"
      "Se permite el uso de letras, numeros y simbolos ASCII\n");
  cout << thin_separator;

  alumno.matricula = get_regexed_input(
      "Entra la matricula del alumno", digit_regex,
      "La matricula solo puede tener numeros, por favor intente de nuevo.\n");
  cout << thin_separator;

  for (int i = 0; i < 3; i++) {
    float x = stof(get_regexed_input(
        ("Entra la calificacion " + to_string(i + 1) + " del alumno: ").c_str(),
        float_regex, "Entra una calificacion por favor.\n"));
    alumno.calif[i] = round(x * 10.0f) / 10.0f;
  }
  alumno.promedio = promedio(alumno.calif, 3);
  cout << thin_separator;

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
      indice = stoi(get_regexed_input(
                   "", digit_regex,
                   "Elige un elemento de la lista de grupos disponibles.\n")) -
               1;
      valid = indice >= 0 && indice < grupos.size();
      if (!valid) {
        cout << "Elige un elemento de la lista de grupos disponibles.\n";
      }
    } while (!valid);
    return indice;
  }(grupos);

  cout << thick_separator;
  cout << "Alumno registrado!\n";
  imprimir(alumno);
  cout << thick_separator;
  await_enter();
  return alumno;
}

// Alas, 'tis true I have gone here and there.
void exportar_reporte_de_texto(const vector<Grupo> &grupos,
                               const vector<Alumno> &alumnos,
                               const string path) {
  // solo puede existir un reporte por archivo binario.
  // El usuario puede ser Jar Jar Binks y llamar un archivo jar.bin.bin
  string txt_path = filesystem::path(path).replace_extension(".txt").string();

  fstream report_file(txt_path, ios::out | ios::trunc);
  if (!report_file.is_open()) {
    cerr << "No se pudo crear el reporte " << txt_path << ".\n";
    return;
  }

  // En vez de sortear el arreglo entero con structs, podemos ordenar sus
  // punteros. Dado que la generacion de un reporte es accion unica, opino que
  // tal implementacion es la mas optima que podria haberme inventado.

  vector<const Alumno *> ordered;
  fror(i, alumnos) ordered.push_back(&i);

  sort(ordered.begin(), ordered.end(),
       [](const Alumno *a, const Alumno *b) -> bool {
         return a->promedio > b->promedio;
       });

  try {
    report_file << thick_separator;
    report_file << "REPORTE DE ALUMNOS:\n";
    for (const Alumno *i : ordered) {
      report_file << thin_separator;
      escribir_alumno_txt(grupos, *i, report_file);
    }
    report_file << thick_separator;
    cout << "El reporte fue generado exitosamente.\n";
  } catch (...) {
    cout << "Error en generacion del reporte.\n";
  }

  await_enter();
}

} // namespace alumno
