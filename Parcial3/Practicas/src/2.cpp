// Leer y reconstruir. Lee ese archivo y reconstruye el arreglo de Alumno en
// memoria. Muestra los datos leídos para confirmar que coinciden.

#include "custom.cpp"

// Dado que los datos son creados en una forma predecible y entera, no tenemos
// que preocuparnos por validacion extensa. Debido a eso no habrá verificacion
// en esta o siguientes practicas.

int main() {
  set_utf8();

  fstream file("Alumnos.txt", ios::in);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  vector<Alumno> alumnos;
  string line;
  while (getline(file, line)) {
    if (line.empty())
      continue;
    Alumno alumno = parsear_alumno_txt(line);
    alumnos.push_back(alumno);
  }

  imprimir_alumnos(alumnos);

  return 0;
}
