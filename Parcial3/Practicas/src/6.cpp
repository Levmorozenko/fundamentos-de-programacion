// Reporte generado. A partir del archivo, genera un reporte de texto nuevo: los
// alumnos ordenados por promedio (de mayor a menor) o agrupados por
// carrera/grupo.

// Esta practica depende en archivo binario generado por 4.cpp.

#include "custom.cpp"
#include <algorithm>

int main() {
  set_utf8();

  fstream file("Alumnos.bin", ios::in | ios::binary);
  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    file.close();
    exit(1);
  }

  // mientras hay menos de 141,000,000 structs a la vez (8gb de ram), estamos
  // bien con vector sin limites.
  vector<Alumno> alumnos;
  while (file.peek() != EOF) {
    Alumno alumno;
    alumno = leer_alumno_bin(file);
    float x = 0;
    fr(i, 3) x += alumno.calif[i];
    alumno.promedio = round(x / 3.0 * 10.0) / 10.0;
    alumnos.push_back(alumno);
  }

  sort(alumnos.begin(), alumnos.end(),
       [](Alumno &a, Alumno &b) -> bool { return a.promedio > b.promedio; });

  imprimir_alumnos(alumnos);

  return 0;
}
