#include "base.cpp"

// Podria usar un archivo separado para cada vector, pero eso seria impractico.
// Debido a tal, en lugar de usar EOF como separador, escribimos el tamaño de
// cada objeto. Excepto:
// - El tamaño del struct, porque estan en una consecuencia
//   cuantificable, y cada uno de sus elementos internos anota su tamaño.
// - Los tamaños de numeros y sus listas, ya que pesan una cantidad statica.

void escribir_alumno(fstream &file, const Alumno &alumno) {
  write_string(file, alumno.nombre);
  write_string(file, alumno.matricula);
  file.write(reinterpret_cast<const char *>(alumno.calif),
             sizeof(alumno.calif));
  file.write(reinterpret_cast<const char *>(&alumno.grupo),
             sizeof(alumno.grupo));
}

Alumno leer_alumno(fstream &file) {
  Alumno alumno;
  alumno.nombre = read_string(file);
  alumno.matricula = read_string(file);
  file.read(reinterpret_cast<char *>(&alumno.calif), sizeof(alumno.calif));
  file.read(reinterpret_cast<char *>(&alumno.grupo), sizeof(alumno.grupo));
  alumno.promedio = promedio(alumno.calif, 3);
  return alumno;
}

void escribir_alumnos(fstream &file, const vector<Alumno> &alumnos) {
  size_t n = alumnos.size();
  file.write(reinterpret_cast<const char *>(&n), sizeof(n));
  fror(alumno, alumnos) escribir_alumno(file, alumno);
}

vector<Alumno> leer_alumnos(fstream &file) {
  size_t n = 0;
  file.read(reinterpret_cast<char *>(&n), sizeof(n));
  vector<Alumno> alumnos;
  if (!file)
    return alumnos;
  alumnos.reserve(n); // en Rust es buena practica reservar el vector antes de
                      // llenarlo, para evitar que se mueve vector.size() veces.
  fr(i, n) alumnos.push_back(leer_alumno(file));
  return alumnos;
}
