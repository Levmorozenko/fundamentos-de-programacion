// Guardar alumnos en texto. Escribe el arreglo de struct Alumno del Segundo
// Parcial en un archivo de texto, un alumno por línea.

#include "custom.cpp"
#include <algorithm>

// Porque sin namespaces?
// Las 6 practicas reusan codigo identico, pensaba en construirlos en hierarquia
// ascendente, pero se siente como un crimen.

int main() {
  set_utf8();

  // creamos el arreglo
  vector<Alumno> alumnos;
  for (int i = 0; i < faker::number::integer(4, 8); i++) {
    alumnos.push_back(crear_alumno());
  }

  // y lo mandamos a archivo de texto.
  // Se re-crea cada ejecucion del 1.cpp, porque no quiero hacer un programa 0
  // para truncarlo.
  ofstream file("Alumnos.txt", ios::trunc);

  if (file.is_open()) {
    for (auto i : alumnos) {
      almacenar_alumno_texto(file, i);
    }
    // mejor solucion seria hacerlo in-place, pero la tarea pide un arreglo.
  } else {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  file.close();
  return 0;
}
