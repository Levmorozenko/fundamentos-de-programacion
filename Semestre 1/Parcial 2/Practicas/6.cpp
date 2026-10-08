// Struct Alumno. Define struct Alumno { string nombre; string matricula; float
// calif[3]; } y crea un arreglo de 5 alumnos. Captura sus datos y muestra el
// promedio de cada uno.
#include "custom.cpp"
#include <cmath>
#include <string>
#include <vector>
using namespace custom;

struct Alumno {
  string nombre;
  string matricula;
  float calif[3];
};

Alumno crear_alumno_aleatorio() {
  Alumno alumno;
  vector<string> nombres = {"Amanda", "Sofia", "Anastasia", "Mako",
                            "Ryuko",  "Anna",  "Isabella",  "Lisa",
                            "Maria",  "Danna", "Alexandra", "Hannah"};

  // Se me olvido que el siguiente field no es apellido, por eso asumo dos
  // nombres. Sin embargo me gustó la implementación asi que lo voy a dejar.
  //
  // Las closuras y lambdas siempre me parecian interesantes.
  // En rust no se ocupa una closura, solo el scope con {... return x;}
  alumno.nombre = [&](vector<string> a) -> string {
    string s;
    s.append(a[random::raw_number() % (a.size() - 1)]);
    s.append(" ");
    s.append(a[random::raw_number() % (a.size() - 1)]);
    return s;
  }(nombres);

  alumno.matricula = []() {
    string s;
    for (int i = 0; i < 8; i++) {
      s.append(to_string(random::digit()));
    }
    return s;
  }();

  for (int j = 0; j < 3; j++) {
    alumno.calif[j] = random::calificacion();
  }

  return alumno;
}

int main() {
  custom_cls();

  vector<Alumno> alumnos(5);
  for (int i = 0; i < 5; i++) {
    alumnos[i] = crear_alumno_aleatorio();
  }

  for (int i = 0; i < alumnos.size(); i++) {
    cout << "Datos del alumno " << i + 1 << ": " << endl;
    cout << "Nombre:    " << alumnos[i].nombre << endl;
    cout << "Matricula: " << alumnos[i].matricula << endl;

    cout << "Promedio:  ";
    cout << [&](float c[3]) -> float {
      float suma;
      for (int i = 0; i < 3; i++) {
        suma += c[i];
      }
      return round(suma / 3.0 * 10.0) / 10.0;
    }(alumnos[i].calif);

    cout << endl << endl;
  }

  return 0;
}
