#include "structs.cpp"
#include "structs/alumno.cpp"
#include "structs/grupo.cpp"
#include "structs/maestro.cpp"

// Notas generales:
// - La jierarquia es chueca y no me gusta. Fue desarollada de tal manera
// 	unicamente porque tarea pide que usemos structs especificos.
// - regex que tan maravillosamente he construido no funciona como deberia.

int main() {

  vector<Grupo> grupos;
  vector<Alumno> alumnos;
  vector<Maestro> maestros;

  fr(i, 3) grupos.push_back(grupo::crear_random());
  fr(i, 3) alumnos.push_back(alumno::crear_random(grupos));
  fr(i, 3) maestros.push_back(maestro::crear_random());

  // funcion imprimir_todos puede ser implementada con genericos, pero lo
  // guardaré para cuando podrémos usar clases.
  while (true) {
    custom::clear_terminal();
    cout << custom::thick_separator << endl;
    cout << "Que desee usted hoy del humilde programa?\n";
    cout << "1) Registrar alumno\n";
    cout << "2) Registrar maestro\n";
    cout << "3) Registrar grupo\n";
    cout << "4) Imprimir todos datos de alumnos\n";
    cout << "5) Imprimir todos datos de maestros\n";
    cout << "6) Imprimir todos datos de grupos\n";
    cout << "7) Salir del programa\n\n";

    string input = custom::get_regexed_input(
        "Seleccione una opcion: ", custom::digit_regex,
        "Entra un numero por favor.");
    switch (stoi(input)) {
    case 1:
      if (!grupos.empty()) {
        alumnos.push_back(alumno::capturar(grupos));
      } else {
        cout << "Primero registra un grupo para el alumno." << endl;
        custom::await_enter();
      }
      break;
    case 2:
      maestros.push_back(maestro::capturar());
      break;
    case 3:
      grupos.push_back(grupo::capturar());
      break;
    case 4:
      if (!alumnos.empty()) {
        alumno::imprimir_todos(alumnos);
      } else {
        cout << "No hay alumnos para imprimir!\n";
      }
      break;
    case 5:
      if (!maestros.empty()) {
        maestro::imprimir_todos(maestros);
      } else {
        cout << "No hay maestros para imprimir!\n";
      }
      break;
    case 6:
      if (!grupos.empty()) {
        grupo::imprimir_todos(grupos);
      } else {
        cout << "No hay grupos para imprimir!\n";
      }
      break;
    case 7:
      return 0;
    default:
      cout << "Opcion invalida.\n";
      custom::await_enter();
      break;
    }
  }
}
