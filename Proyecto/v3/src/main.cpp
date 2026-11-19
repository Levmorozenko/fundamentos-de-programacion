#include "saving/save.cpp"
#include "structs.cpp"
#include "structs/alumno.cpp"
#include "structs/maestro.cpp"

int main() {
  set_utf8();

  bool modo_aleatorio = false;

  vector<Grupo> grupos;
  vector<Alumno> alumnos;
  vector<Maestro> maestros;

  while (true) {
    clear_terminal();
    cout << thick_separator;
    cout << "Que desee usted hoy del humilde programa?\n";
    cout << "1) Registrar alumno\n";
    cout << "2) Registrar maestro\n";
    cout << "3) Registrar grupo\n\n";

    cout << "4) Imprimir todos datos de alumnos\n";
    cout << "5) Imprimir todos datos de maestros\n";
    cout << "6) Imprimir todos datos de grupos\n\n";

    cout << "7) Imprimir el alumno con promedio mas alto del grupo\n";
    cout << "8) Imprimir alumnos de misma carrera\n\n";

    cout << "9) Salir del programa\n";
    cout << thick_separator;

    string input = get_regexed_input("Seleccione una opcion: ", digit_regex,
                                     "Entra un numero por favor.");

    switch (stoi(input)) {
    case 1:
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
      break;

    case 2:
      if (modo_aleatorio) {
        maestros.push_back(maestro::crear_random());
      } else {
        maestros.push_back(maestro::capturar());
      }

      break;

    case 3:
      if (modo_aleatorio) {
        grupos.push_back(grupo::crear_random());
      } else {
        grupos.push_back(grupo::capturar());
      }
      break;

    case 4:
      if (!alumnos.empty()) {
        alumno::imprimir_todos(alumnos);
      } else {
        cout << "No hay alumnos para imprimir!\n";
        await_enter();
      }
      break;

    case 5:
      if (!maestros.empty()) {
        maestro::imprimir_todos(maestros);
      } else {
        cout << "No hay maestros para imprimir!\n";
        await_enter();
      }
      break;

    case 6:
      if (!grupos.empty()) {
        grupo::imprimir_todos(grupos);
      } else {
        cout << "No hay grupos para imprimir!\n";
        await_enter();
      }
      break;

    case 7:
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_alumno_con_mayor_promedio_del_grupo(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        await_enter();
      }
      break;

    case 8:
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_cantidad_de_alumnos_por_carrera(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        await_enter();
      }
      break;

    case 9:
      return 0;

    case 67:
      modo_aleatorio = !modo_aleatorio;
      if (modo_aleatorio) {
        cout << "Entraste el codigo secreto. Ahora todos registros generan un "
                "objeto con valores aleatorios.\n\n";
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
