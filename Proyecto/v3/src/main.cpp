#include "custom.cpp"
#include "structs.cpp"
#include "structs/alumno.cpp"
#include "structs/maestro.cpp"

#include "file_picking.cpp"
#include "saving/save.cpp"
#include <string>

int main() {
  set_utf8();

  bool modo_aleatorio = false;

  vector<Grupo> grupos;
  vector<Alumno> alumnos;
  vector<Maestro> maestros;

  clear_terminal();
  cout << thick_separator;
  string path = pick_file("datos.bin");
  cout << "Cargando el archivo " << path << "...\n";
  bool is_file_loaded = load_file(grupos, alumnos, maestros, path);
  if (is_file_loaded) {
    cout << "El archivo " << path << " was successfully loaded.\n"
         << thin_separator;
    await_enter();
  } else {
    cout << "No se pudo cargar el archivo.\n";
    return 0;
  }

  bool is_program_saved = true;

  while (true) {
    clear_terminal();
    cout << thick_separator;
    cout << "Que desee usted hoy del humilde programa?\n";
    cout << "1) Registrar grupos\n";
    cout << "2) Registrar alumnos\n";
    cout << "3) Registrar maestros\n\n";

    cout << "4) Imprimir todos datos de alumnos\n";
    cout << "5) Imprimir todos datos de maestros\n";
    cout << "6) Imprimir todos datos de grupos\n\n";

    cout << "7) Imprimir el alumno con promedio mas alto del grupo\n";
    cout << "8) Imprimir alumnos de misma carrera\n\n";

    cout << "9) Guardar el estado del programa\n";
    cout << "10) Salir del programa\n";
    cout << thick_separator;

    string input = get_regexed_input("Seleccione una opcion: ", digit_regex,
                                     "Entra un numero por favor.");

    switch (stoi(input)) {
    case 1: // registrar grupo
      if (modo_aleatorio) {
        grupos.push_back(grupo::crear_random());
      } else {
        grupos.push_back(grupo::capturar());
      }
      is_program_saved = false;
      break;

    case 2: // registrar alumno
      if (!grupos.empty()) {
        if (modo_aleatorio) {
          alumnos.push_back(alumno::crear_random(grupos));
        } else {
          alumnos.push_back(alumno::capturar(grupos));
        }
      } else {
        cout << "Primero registra un grupo para el alumno." << endl;
        await_enter();
      }
      is_program_saved = false;
      break;

    case 3: // registrar maestro
      if (modo_aleatorio) {
        maestros.push_back(maestro::crear_random());
      } else {
        maestros.push_back(maestro::capturar());
      }
      is_program_saved = false;
      break;

    case 4: // imprimir alumnos
      if (!alumnos.empty()) {
        alumno::imprimir_todos(alumnos);
      } else {
        cout << "No hay alumnos para imprimir!\n";
        await_enter();
      }
      break;

    case 5: // imprimir maestros
      if (!maestros.empty()) {
        maestro::imprimir_todos(maestros);
      } else {
        cout << "No hay maestros para imprimir!\n";
        await_enter();
      }
      break;

    case 6: // imprimir grupos
      if (!grupos.empty()) {
        grupo::imprimir_todos(grupos);
      } else {
        cout << "No hay grupos para imprimir!\n";
        await_enter();
      }
      break;

    case 7: // Imprimir el alumno con promedio mas alto del grupo
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_alumno_con_mayor_promedio_del_grupo(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        await_enter();
      }
      break;

    case 8: // Imprimir alumnos de misma carrera
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_cantidad_de_alumnos_por_carrera(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        await_enter();
      }
      break;

    case 9: // Solo guardar
      is_program_saved = handle_user_save(grupos, alumnos, maestros, path);
      break;

    case 10: // salir sin guardar
      if (!is_program_saved) {
        string emergency_input = get_regexed_input(
            "El programa no fue guardado. Desea guardarlo ahora? (Y/n)\n",
            name_regex, "");
      }
      return 0;

    case 67:
      modo_aleatorio = !modo_aleatorio;
      if (modo_aleatorio) {
        cout << "Entraste el codigo secreto. Ahora todos registros generan "
                "valores aleatorios.\n\n";
      } else {
        cout << "Entraste el codigo secreto por la segunda vez. Modo manual "
                "es "
                "reactivado.\n\n";
      }
      await_enter();
      break;

    default:
      cout << "Opcion invalida.\n";
      await_enter();
      break;
    }
  }
}
