#include "structs.cpp"
#include "structs/alumno.cpp" // tambien incluye grupo.cpp
#include "structs/maestro.cpp"

// Notas generales:
// - La jierarquia es chueca y no me gusta. Fue desarollada de tal manera
// unicamente porque tarea pide que usemos structs especificos.
// - regex.
// - Se me dificulta la diferencia entre referencia y puntero, porque una
// referencia de Rust es un puntero en C++. En vez de eso, las * son
// dereferencias para referencias en Rust.
// - No hay ni una fuga de memoria porque todos datos son liberados en un
// return. En main() solo se guardan valores importantes. A base de esto fue
// creada la arquitectura del proyecto.

int main() {
  bool modo_aleatorio = false;

  vector<Grupo> grupos;
  vector<Alumno> alumnos;
  vector<Maestro> maestros;

  // Varias funciones pueden ser implementados con genericos, pero lo
  // guardaré para cuando podrémos usar clases.
  // Tuve luz verde para usar clases, sin embargo el tiempo no es suficiente
  // para refactorizar todo el programa.
  while (true) {
    custom::clear_terminal();
    cout << custom::thick_separator << endl;
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
    cout << custom::thick_separator << endl;

    string input = custom::get_regexed_input(
        "Seleccione una opcion: ", custom::digit_regex,
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
        custom::await_enter();
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
        custom::await_enter();
      }
      break;

    case 5:
      if (!maestros.empty()) {
        maestro::imprimir_todos(maestros);
      } else {
        cout << "No hay maestros para imprimir!\n";
        custom::await_enter();
      }
      break;

    case 6:
      if (!grupos.empty()) {
        grupo::imprimir_todos(grupos);
      } else {
        cout << "No hay grupos para imprimir!\n";
        custom::await_enter();
      }
      break;

    case 7:
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_alumno_con_mayor_promedio_del_grupo(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        custom::await_enter();
      }
      break;

    case 8:
      if (!grupos.empty() && !alumnos.empty()) {
        alumno::imprimir_cantidad_de_alumnos_por_carrera(grupos, alumnos);
      } else {
        cout << "Se deben registrar minimo un grupo y un alumno primero.\n";
        custom::await_enter();
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
      custom::await_enter();
      break;

    default:
      cout << "Opcion invalida.\n";
      custom::await_enter();
      break;
    }
  }
}
