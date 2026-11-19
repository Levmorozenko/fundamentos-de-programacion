#ifndef STRUCTS_CPP
#define STRUCTS_CPP

#include <string>
using namespace std;

struct Alumno {
  string nombre;
  string matricula;
  float calif[3];
  float promedio;
  int grupo; // ...int?
};
struct Maestro {
  string nombre;
  string materia;
};
struct Grupo {
  string nombre;
  string carrera;
};

#endif
