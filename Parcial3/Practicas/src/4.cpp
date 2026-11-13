// Versión binaria. Guarda el mismo arreglo en un archivo binario. Compara
// el tamaño del archivo binario contra el de texto y explica por qué son
// distintos.

#include "custom.cpp"
#include <fstream>

// Este es el codigo especificamente de la tarea. 4-2 y 4-3 son exploraciones
// relacionados a misma etapa, pero no a lo requerido.

void almacenar_alumno_bin(ofstream &file, Alumno &i) {
  // yo presenté esto

  size_t nombre_size = i.nombre.length();
  file.write(reinterpret_cast<const char *>(&nombre_size), sizeof(nombre_size));
  file.write(i.nombre.c_str(), nombre_size);

  size_t matricula_size = i.matricula.length();
  file.write(reinterpret_cast<const char *>(&matricula_size),
             sizeof(matricula_size));
  file.write(i.matricula.c_str(), matricula_size);

  // sabemos que el tamaño de int calif[3] y grupo son 12 y 4 bytes
  // respectivamente.
  file.write(reinterpret_cast<const char *>(&i.calif), sizeof(i.calif));
  file.write(reinterpret_cast<const char *>(&i.grupo), sizeof(i.grupo));
}

int main() {
  vector<Alumno> alumnos;
  for (int i = 0; i < 1000000; i++) {
    alumnos.push_back(crear_alumno());
  }

  ofstream file("Alumnos.bin", ios::trunc | ios::binary);

  if (!file.is_open()) {
    cerr << "El archivo no pudo abrirse.\n";
    return 1;
  }

  for (auto i : alumnos) {
    almacenar_alumno_bin(file, i);
  }

  file.close();
  return 0;
}
