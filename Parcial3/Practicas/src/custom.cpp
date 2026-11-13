#include "faker-cxx/number.h"
#include "faker-cxx/person.h"
#include "faker-cxx/string.h"
#include <fstream>
#include <vector>

#include "previous.cpp"

#define fro(i, a) for (auto i : a)

using namespace std;

struct Alumno {
  string nombre;
  string matricula;
  float calif[3];
  int grupo;
};

Alumno crear_alumno() {
  Alumno alumno;
  alumno.nombre = faker::person::fullName(faker::Locale::es_MX);
  alumno.matricula = faker::string::numeric(10);
  fr(i, 3) alumno.calif[i] = round(faker::number::decimal(10.0) * 10.0) / 10.0;
  alumno.grupo = faker::number::integer(1, 5);

  return alumno;
}
