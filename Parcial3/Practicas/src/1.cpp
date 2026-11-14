// Guardar alumnos en texto. Escribe el arreglo de struct Alumno del Segundo
// Parcial en un archivo de texto, un alumno por línea.

#include "custom.cpp"

int main() {
  set_utf8();

  // En caso de desear correr las pruebas de 4-3 cambielo a 1000000.
  int cantidad_de_alumnos = faker::number::integer(4, 8);

  vector<Alumno> alumnos;
  fr(i, cantidad_de_alumnos) alumnos.push_back(crear_alumno());

  fstream file("Alumnos.txt", ios::out | ios::trunc);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    file.close();
    exit(1);
  }

  fro(i, alumnos) almacenar_alumno_texto(file, i);

  return 0;
}
